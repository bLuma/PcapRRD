/* 
 * File:   PacketAnalyzer.cpp
 * Author: roman
 * 
 * Created on 18. říjen 2011, 8:58
 */

#include "PacketAnalyzer.h"
#include "netstruct.h"
//#include <netinet/in.h>
//#include <arpa/inet.h>

PacketAnalyzer::PacketAnalyzer(pcap_pkthdr* header, const unsigned char* data) 
    : m_header(header), m_data(data) {
    m_dataL3 = NULL;
    m_dataL4 = NULL;
}

PacketAnalyzer::PacketAnalyzer(const PacketAnalyzer& orig) {
}

PacketAnalyzer::~PacketAnalyzer() {
}

void PacketAnalyzer::analyze() {
    doL2();
}

void PacketAnalyzer::doL2() {
    DEBUGLOG("==== Ethernet ====");
    const EthernetHeader* ethernet = reinterpret_cast<const EthernetHeader*>(m_data);
    m_protoL3 = ntohs(ethernet->typeOrLen);
    
    m_source = &ethernet->source;
    m_destination = &ethernet->destination;
    
    if (m_protoL3 < 0x0600) { // Ethernet II
        return;
    }
    
    m_dataL3 = ethernet->getNextLayer();
    doL3();
}

void PacketAnalyzer::doL3() {
    if (!m_dataL3)
        return;
    
    switch (m_protoL3) {
        // IPv4
        case PROTO_L2_IPV4: {
            DEBUGLOG("=== Ipv4 ===");
            const Ipv4Header* ip = reinterpret_cast<const Ipv4Header*>(m_dataL3);
    
            m_source = &ip->source;
            m_destination = &ip->destination;

            m_protoL4 = ip->protocol;
            m_dataL4 = ip->getNextLayer();
            break;
        }
        
        // Others...
    }
    
    doL4();
}

void PacketAnalyzer::doL4() {
    if (!m_dataL4)
        return;

    switch (m_protoL4) {
        // TCP
        case PROTO_L3_TCP: {
            DEBUGLOG("== TCP ==");
            break;
        }
    }
}
