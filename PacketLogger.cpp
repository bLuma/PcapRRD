/* 
 * File:   PacketLogger.cpp
 * Author: roman
 * 
 * Created on 15. říjen 2011, 19:58
 */

#include <pcap.h>
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

void PacketLogger::setInterface(int interface) {
    pcap_if_t* devs;
    pcap_if_t* dev;
    char errbuf[PCAP_ERRBUF_SIZE];
    
    pcap_findalldevs(&devs, errbuf);
    for (dev = devs; dev != NULL; dev = dev->next) {
        cout << dev->name << " # " << dev->description << endl; 
    }
    pcap_freealldevs(devs);
}

/**
 * Nastavi zachytavaci filtr.
 * 
 * @param filter vyraz pro filtrovani
 * @return true pri uspesne kompilaci a aplikaci filtru
 */
bool PacketLogger::setFilter(string filter) {
    bpf_program bpf;
    
    if (pcap_compile(m_device, &bpf, filter.c_str(), 1, 0xFFFFFF) < 0)
        return false;
    
    if (pcap_setfilter(m_device, &bpf) < 0)
        return false;
    
    return true;
}