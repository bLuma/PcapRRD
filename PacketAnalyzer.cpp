/* 
 * File:   PacketAnalyzer.cpp
 * Author: roman
 * 
 * Created on 18. říjen 2011, 8:58
 */

#include "PacketAnalyzer.h"
#include "netstruct.h"
//#include <netinet/in.h>
#include <arpa/inet.h>

template<typename T>
string convertPointerToStr(const T* ptr) {
    ostringstream os;
    os << hex << reinterpret_cast<unsigned int>(ptr);
    return os.str();
}

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
    if (!m_data)
        return;
    
    doL2();
}

void PacketAnalyzer::doL2() {
    DEBUGLOG("==== Ethernet ==== ");
    const EthernetHeader* ethernet = reinterpret_cast<const EthernetHeader*>(m_data);
    m_protoL3 = ntohs(ethernet->typeOrLen);
    
    m_source = reinterpret_cast<const unsigned char*>(&ethernet->source);
    m_destination = reinterpret_cast<const unsigned char*>(&ethernet->destination);
    
    if (m_protoL3 < 0x0600) { // !Ethernet II
        DEBUGLOG("not Ethernet II");
        return;
    }
    
    DEBUGLOG("Proto: 0x" << hex << m_protoL3 << dec << " Src: " << ethernet->source << " Dst: " << ethernet->destination);
    //DEBUGLOG("m_data: " << convertPointerToStr(m_data).c_str());
    m_dataL3 = ethernet->getNextLayer();
    //DEBUGLOG("m_dataL3: " << convertPointerToStr(m_dataL3).c_str());
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
    
            m_source = reinterpret_cast<const unsigned char*>(&ip->source);
            m_destination = reinterpret_cast<const unsigned char*>(&ip->destination);

            m_protoL4 = ip->protocol;
            
            DEBUGLOG("Proto: 0x" << hex << m_protoL4 << dec << " Src: " << ip->source << " Dst: " << ip->destination);
            
            m_dataL4 = ip->getNextLayer();
            break;
        }
        
        
        case PROTO_L2_IPV6: {
            DEBUGLOG("=== Ipv6 ===");
            break;
        }
        
        // Others...
        default:
            return;
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
