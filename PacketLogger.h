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

// windows fix
#ifndef PCAP_OPENFLAG_PROMISCUOUS
#define PCAP_OPENFLAG_PROMISCUOUS 1
#endif

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
    bool startCapture();
    
private:
    static void captureThread(void* packetLogger);
    
    /**
     * Zachytavaci zarizeni.
     */
    pcap_if_t* m_device;
    
    /**
     * Seznam vsech zarizeni.
     */
    pcap_if_t* m_devices;
    
    /**
     * Handle zachytavaciho zarizeni.
     */
    pcap_t* m_handle;
    
    /**
     * Zachytavaci filtr.
     */
    string m_filter;
    
    /**
     * Zachytavaci vlakno.
     */
    pthread_t* m_thread;
    
    /**
     * Buffer na chybova hlaseni.
     */
    char m_errbuf[PCAP_ERRBUF_SIZE];
};

#endif	/* PACKETLOGGER_H */
