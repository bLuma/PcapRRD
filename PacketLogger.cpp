/* 
 * File:   PacketLogger.cpp
 * Author: roman
 * 
 * Created on 15. říjen 2011, 19:58
 */

#include "PacketLogger.h"

/**
 * Konstruktor
 */
PacketLogger::PacketLogger() {
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
}

/**
 * Nastavi zachytavaci zarizeni podle zvoleneho jmena.
 * 
 * @param interface nazev zarizeni
 * @return true pri uspesnem nalezeni zarizeni
 */
bool PacketLogger::setInterface(string interface) {
    pcap_if_t* dev;
    char errbuf[PCAP_ERRBUF_SIZE];
    
    if (pcap_findalldevs(&m_devices, errbuf) < 0)
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
 * Nastavi zachytavaci filtr.
 * 
 * @param filter vyraz pro filtrovani
 * @return true pri uspesne kompilaci a aplikaci filtru
 */
bool PacketLogger::setFilter(string filter) {
    bpf_program bpf;
    
    if (pcap_compile((pcap_t*)m_device, &bpf, filter.c_str(), 1, 0xFFFFFF) < 0)
        return false;
    
    if (pcap_setfilter((pcap_t*)m_device, &bpf) < 0)
        return false;
    
    return true;
}