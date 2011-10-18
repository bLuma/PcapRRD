/* 
 * File:   PacketAnalyzer.h
 * Author: roman
 *
 * Created on 18. říjen 2011, 8:58
 */

#ifndef PACKETANALYZER_H
#define	PACKETANALYZER_H

#include <pcap.h>
#include "common.h"

// 0x0800 	Internet Protocol, Version 4 (IPv4)
// 0x0806 	Address Resolution Protocol (ARP)
// 0x8035 	Reverse Address Resolution Protocol (RARP)
// 0x86DD 	Internet Protocol, Version 6 (IPv6)

#define PROTO_L2_IPV4 0x0800
#define PROTO_L2_IPV6 0x86DD
#define PROTO_L2_ARP  0x0806
#define PROTO_L2_RARP 0x8035

#define PROTO_L3_TCP  0x06
#define PROTO_L3_UDP  0x11
#define PROTO_L3_ICMP 0x01

class PacketAnalyzer {
public:
    PacketAnalyzer(pcap_pkthdr* header, const unsigned char* data);
    PacketAnalyzer(const PacketAnalyzer& orig);
    virtual ~PacketAnalyzer();
    
    void analyze();
    
private:
    inline void doL2();
    inline void doL3();
    inline void doL4();
    
    inline bool isIpv4() {
        return m_protoL3 == PROTO_L2_IPV4 && m_dataL3;
    }

    pcap_pkthdr* m_header;
    const unsigned char* m_data;
    
    unsigned short m_protoL3;
    const unsigned char* m_dataL3;
    
    unsigned short m_protoL4;
    const unsigned char* m_dataL4;
    
    const unsigned char* m_source;
    const unsigned char* m_destination;
};

#endif	/* PACKETANALYZER_H */
