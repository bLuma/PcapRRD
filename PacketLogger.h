/* 
 * File:   PacketLogger.h
 * Author: roman
 *
 * Created on 15. říjen 2011, 19:58
 */

#ifndef PACKETLOGGER_H
#define	PACKETLOGGER_H

#include <pcap.h>
#include "common.h"

/**
 * Trida slouzici pro zachytavani a analyzu paketu. Trida automaticky
 * vytvari nove zachytavaci vlakno, ve kterm nasledne bezi i analyza.
 */
class PacketLogger {
public:
    PacketLogger();
    PacketLogger(const PacketLogger& orig);
    virtual ~PacketLogger();
    
    bool setFilter(string filter);
    bool setInterface(string interface);
    //void startCapture();
    
private:

    // static void processPacket();
    // static void analyzeL2();
    // static void analyzeL3();
    // static void analyzeL4();
    
    /**
     * Zachytavaci zarizeni.
     */
    pcap_if_t* m_device;
    
    /**
     * Seznam vsech zarizeni.
     */
    pcap_if_t* m_devices;
};

#endif	/* PACKETLOGGER_H */

