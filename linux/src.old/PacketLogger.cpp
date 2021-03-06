/* 
 * File:   PacketLogger.cpp
 * Author: roman
 * 
 * Created on 15. říjen 2011, 19:58
 */

#include "PacketLogger.h"
#include "PacketAnalyzer.h"

/**
 * Konstruktor
 */
PacketLogger::PacketLogger() {
    m_device = NULL;
    m_devices = NULL;
    m_handle = NULL;
}

/**
 * Kopirovaci konstruktor.
 * 
 * @param orig reference
 */
PacketLogger::PacketLogger(const PacketLogger& orig) {
}

/**
 * Destruktor.
 */
PacketLogger::~PacketLogger() {
    //pcap_close(m_handle);
    m_device = NULL;
    
    if (m_devices)
        pcap_freealldevs(m_devices);
}

/**
 * Nastavi zachytavaci zarizeni podle zvoleneho jmena.
 * 
 * @param interface nazev zarizeni
 * @return true pri uspesnem nalezeni zarizeni
 */
bool PacketLogger::setInterface(string interface) {
    pcap_if_t* dev;
    
    if (pcap_findalldevs(&m_devices, m_errbuf) < 0)
        return false;
    
    for (dev = m_devices; dev != NULL; dev = dev->next) {
        if (interface == dev->name) {
            m_device = dev;
            return true;
        }
    }
    
    pcap_freealldevs(m_devices);
    return false;
}

/**
 * Nastavi jako zachytavaci zarizeni prvni dostupny interface.
 */
void PacketLogger::setFirstAvailableInterface() {
    pcap_if_t* dev;
    
    if (pcap_findalldevs(&m_devices, m_errbuf) < 0)
        return;
    
    for (dev = m_devices; dev != NULL; dev = dev->next) {
        m_device = dev;
        return;
    }
    
    pcap_freealldevs(m_devices);
}

/**
 * Vypise vsechny dostupne zarizeni na obrazovku nebo do zadaneho vektoru.
 * 
 * @param output vystupni vektor
 */
void PacketLogger::listInterfaces(vector<string>* output = NULL) {
    pcap_if_t* devices;
    pcap_if_t* dev;
    
    if (pcap_findalldevs(&devices, m_errbuf) < 0)
        return;
    
    for (dev = devices; dev != NULL; dev = dev->next) {
        if (output)
            output->push_back(dev->name);
        else
            cout << dev->name << ": " << dev->description << endl;
    }
    
    pcap_freealldevs(devices);
}

/**
 * Nastavi zachytavaci filtr.
 * 
 * @param filter vyraz pro filtrovani
 * @return true pri uspesne kompilaci a aplikaci filtru
 */
bool PacketLogger::setFilter(string filter) {
    m_filter = filter;   
    return true;
}

/**
 * Zahaji zachytavani na zarizeni.
 * 
 * @return true pri uspechu
 */
bool PacketLogger::startCapture() {
    m_handle = pcap_open_live(m_device->name, 65536, PCAP_OPENFLAG_PROMISCUOUS, 1000, m_errbuf);
    if (m_handle == NULL) {
        cerr << m_errbuf << endl;
        return false;
    }

    if (!m_filter.empty()) {
        // TODO: bpf resource release?
        bpf_program bpf;
    
        if (pcap_compile(m_handle, &bpf, m_filter.c_str(), 1, 0xFFFFFF) < 0)
            return false;
    
        if (pcap_setfilter(m_handle, &bpf) < 0)
            return false;        
    }

    if (pthread_create(&m_thread, NULL, &PacketLogger::captureThread, reinterpret_cast<void*>(this)) != 0)
        return false;

    return true;
}

/**
 * Metoda ve ktere bezi zachytavaci vlakno.
 * 
 * @param packetLogger instance packet loggeru
 */
void* PacketLogger::captureThread(void* packetLogger) {
    DEBUG_OUTPUT("PacketLogger thread ready.");
    PacketLogger* instance = reinterpret_cast<PacketLogger*>(packetLogger);
    int res;
    pcap_pkthdr* header;
    const unsigned char* data;
    
    while (!App::exit && (res = pcap_next_ex(instance->m_handle, &header, &data)) >= 0) {
        // timeout
        if (res == 0)
            continue;
        
        DEBUG_PACKET("@" << header->ts.tv_sec);
        PacketAnalyzer(header, data).analyze();
        DEBUG_PACKET("");
    }
    
    if (res < 0 && !App::exit) {
        DEBUG_OUTPUT("captureThread: crash? res=" << res);
        App::exit = true;
    }
    
    return NULL;
}
