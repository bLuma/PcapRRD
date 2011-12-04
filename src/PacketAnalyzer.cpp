/* 
 * File:   PacketAnalyzer.cpp
 * Author: roman
 * 
 * Created on 18. říjen 2011, 8:58
 */

#include "PacketAnalyzer.h"
#include "netstruct.h"
#include "StatsAdapter.h"
//#include <netinet/in.h>
#include <arpa/inet.h>

/**
 * Pomocna funkce na konverzi libovolneho ukazatele na string obsahujici jeho 
 * adresu.
 * 
 * @param ptr ukazatel
 * @return adresa ukazatele
 */
template<typename T>
string convertPointerToStr(const T* ptr) {
    ostringstream os;
    os << hex << reinterpret_cast<unsigned int>(ptr);
    return os.str();
}

/**
 * Konstruktor.
 * 
 * @param header metainformace o paketu
 * @param data data paketu
 */
PacketAnalyzer::PacketAnalyzer(pcap_pkthdr* header, const unsigned char* data) 
    : m_reqSize(0), m_header(header), m_data(data), m_dataL3(NULL), m_dataL4(NULL) {
}

/**
 * Kopy konstruktor.
 * 
 * @param orig reference
 */
PacketAnalyzer::PacketAnalyzer(const PacketAnalyzer& orig) {
}

/**
 * Destruktor
 */
PacketAnalyzer::~PacketAnalyzer() {
}

/**
 * Spusti proces analyzy paketu.
 */
void PacketAnalyzer::analyze() {
    if (!m_data)
        return;
    
    doL2();
}

/**
 * Analyza na druhe vrstve.
 */
void PacketAnalyzer::doL2() {
    DEBUG_PACKET("==== Ethernet ==== ");
    
    if (!checkSize(14)) return;
    const EthernetHeader* ethernet = reinterpret_cast<const EthernetHeader*>(m_data);
    m_protoL3 = ntohs(ethernet->typeOrLen);
    
    m_source = reinterpret_cast<const unsigned char*>(&ethernet->source);
    m_destination = reinterpret_cast<const unsigned char*>(&ethernet->destination);
    
    if (m_protoL3 < 0x0600) { // !Ethernet II
        DEBUG_PACKET("not Ethernet II");
        return;
    }
    
    DEBUG_PACKET("Proto: 0x" << hex << m_protoL3 << dec << " Src: " << ethernet->source << " Dst: " << ethernet->destination);
    
    m_dataL3 = ethernet->getNextLayer();
    doL3();
}

/**
 * Analyza na treti vrstve.
 */
void PacketAnalyzer::doL3() {
    if (!m_dataL3)
        return;
    
    switch (m_protoL3) {
        
        // IPv4
        case PROTO_L2_IPV4: {
            DEBUG_PACKET("=== Ipv4 ===");
            if (!checkSize(20)) return;
            const Ipv4Header* ip = reinterpret_cast<const Ipv4Header*>(m_dataL3);
    
            m_source = reinterpret_cast<const unsigned char*>(&ip->source);
            m_destination = reinterpret_cast<const unsigned char*>(&ip->destination);

            m_protoL4 = ip->protocol;
            
            DEBUG_PACKET("Proto: 0x" << hex << m_protoL4 << dec << " Src: " << ip->source << " Dst: " << ip->destination);
            
            StatsAdapter::callHostStat(*reinterpret_cast<const IpAddrBinary*>(m_source), ST_UPLOAD, getPacketLen());
            StatsAdapter::callHostStat(*reinterpret_cast<const IpAddrBinary*>(m_destination), ST_DOWNLOAD, getPacketLen());
            
            if (!checkSize(ip->getLength() - 20)) return;
            m_dataL4 = ip->getNextLayer();
            break;
        }
        
        // IPv6
        case PROTO_L2_IPV6: {
            DEBUG_PACKET("=== Ipv6 ===");
            return;
        }
        
        // Others...
        default:
            return;
    }
    
    doL4();
}

/**
 * Analyza na ctvrte vrstve.
 */
void PacketAnalyzer::doL4() {
    if (!m_dataL4)
        return;

    switch (m_protoL4) {
        // TCP
        case PROTO_L3_TCP: {
            DEBUG_PACKET("== TCP ==");
            if (!checkSize(16)) return;
            const TcpHeader* tcp = reinterpret_cast<const TcpHeader*>(m_dataL4);
            
            DEBUG_PACKET("srcPort: " << tcp->getSourcePort() << " dstPort: " << tcp->getDestinationPort());
            
            StatsAdapter::callServiceStat((*reinterpret_cast<const IpAddrBinary*>(m_source)), PROTO_L3_TCP, tcp->getSourcePort(), tcp->getDestinationPort(), ST_UPLOAD, getPacketLen());
            StatsAdapter::callServiceStat((*reinterpret_cast<const IpAddrBinary*>(m_destination)), PROTO_L3_TCP, tcp->getDestinationPort(), tcp->getSourcePort(), ST_DOWNLOAD, getPacketLen());
            
            break;
        }
        
        // UDP
        case PROTO_L3_UDP: {
            DEBUG_PACKET("== UDP ==");
            if (!checkSize(8)) return;
            const UdpHeader* udp = reinterpret_cast<const UdpHeader*>(m_dataL4);
            
            DEBUG_PACKET("srcPort: " << udp->getSourcePort() << " dstPort: " << udp->getDestinationPort());
            
            StatsAdapter::callServiceStat((*reinterpret_cast<const IpAddrBinary*>(m_source)), PROTO_L3_UDP, udp->getSourcePort(), udp->getDestinationPort(), ST_UPLOAD, getPacketLen());
            StatsAdapter::callServiceStat((*reinterpret_cast<const IpAddrBinary*>(m_destination)), PROTO_L3_UDP, udp->getDestinationPort(), udp->getSourcePort(), ST_DOWNLOAD, getPacketLen());
            break;
        }
    }
}
