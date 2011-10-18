/* 
 * File:   netstruct.h
 * Author: roman
 *
 * Created on 18. říjen 2011, 9:39
 */

#ifndef NETSTRUCT_H
#define	NETSTRUCT_H


#pragma pack(push,1)

struct MacAddress {
    unsigned char addr[6];
};

struct Ipv4Address {
    unsigned char addr[4];
};

struct LayerFrameOrPacket {
    const unsigned char* getNextLayer() const = 0;
};

/*Preamble 	Start of frame delimiter 	MAC destination 	MAC source 	802.1Q tag (optional) 	Ethertype or length 	Payload 	Frame check sequence (32-bit CRC) 	Interframe gap
7 octets of 10101010 	1 octet of 10101011 	6 octets 	6 octets 	(4 octets) 	2 octets 	46–1500 octets 	4 octets 	12 octets
	64–1522 octets 	
72–1530 octets 	*/

struct EthernetFrame : public LayerFrameOrPacket {
    MacAddress destination;
    MacAddress source;
    unsigned short typeOrLen;
    
    const unsigned char* getNextLayer() const {
        return reinterpret_cast<const unsigned char*>(this) + (6+6+2);
    }
};

/*bit offset 	0–3 	4–7 	8–13 	14-15 	16–18 	19–31
0 	Version 	Header Length 	Differentiated Services Code Point 	Explicit Congestion Notification 	Total Length
32 	Identification 	Flags 	Fragment Offset
64 	Time to Live 	Protocol 	Header Checksum
96 	Source IP Address
128 	Destination IP Address
160 	Options ( if Header Length > 5 )
160
or
192+ 	 
Data*/

struct Ipv4Packet : public LayerFrameOrPacket {
    unsigned char verLen;
    unsigned char DSCP;
    unsigned short length;
    unsigned short id;
    unsigned short flagsFragmentOffset;
    unsigned char ttl;
    unsigned char protocol;
    unsigned short checksum;
    Ipv4Address source;
    Ipv4Address destination;
    
    const unsigned char* getNextLayer() const {
        return reinterpret_cast<const unsigned char*>(this) + ((verLen & 0x0F) * 4);
    }
};

#pragma pack(pop)

#endif	/* NETSTRUCT_H */

