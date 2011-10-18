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
}

PacketAnalyzer::PacketAnalyzer(const PacketAnalyzer& orig) {
}

PacketAnalyzer::~PacketAnalyzer() {
}

void PacketAnalyzer::analyze() {
    doL2();
}

void PacketAnalyzer::doL2() {
    const EthernetFrame* ethernet = reinterpret_cast<const EthernetFrame*>(m_data);
    m_protoL3 = ntohs(ethernet->typeOrLen);
    
    if (m_protoL3 < 0x0600) { // Ethernet II
        return;
    }
    
    m_dataL3 = ethernet->getNextLayer();
    doL3();
}

void PacketAnalyzer::doL3() {
    switch (m_protoL3) {
        // IPv4
        case PROTO_L2_IPV4: {
        
            break;
        }
        
        // Others...
    }
}

void PacketAnalyzer::doL4() {
    
}
