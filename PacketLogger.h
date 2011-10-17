/* 
 * File:   PacketLogger.h
 * Author: roman
 *
 * Created on 15. říjen 2011, 19:58
 */

#ifndef PACKETLOGGER_H
#define	PACKETLOGGER_H

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
    void setInterface(int interface);
    //void startCapture();
    
private:

    // static void processPacket();
    // static void analyzeL2();
    // static void analyzeL3();
    // static void analyzeL4();
    
    /**
     * Zachytavaci zarizeni.
     */
    pcap_t* m_device;
    
};

#endif	/* PACKETLOGGER_H */

