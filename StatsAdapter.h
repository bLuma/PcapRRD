/* 
 * File:   StatsAdapter.h
 * Author: roman
 *
 * Created on 20. říjen 2011, 10:36
 */

#ifndef STATSADAPTER_H
#define	STATSADAPTER_H

#include "common.h"
#include "Stats.h"
#include "PacketAnalyzer.h"

/**
 * Adapter tvori rozhrani mezi analyzou paketu a statistikami. Zajistuje
 * filtrovani a konverzi na vhodny format.
 */
class StatsAdapter {
public:   
    static void callHostStat(const IpAddrBinary addr, StatType type, unsigned int value);
    static void callServiceStat(const IpAddrBinary addr, const L3Proto protocol, unsigned short localPort, unsigned short remotePort, StatType type, unsigned int value);
       
    static void addServicePort(unsigned short port);
    static void loadRules();
    
private:
    StatsAdapter();
    StatsAdapter(const StatsAdapter& orig);
    virtual ~StatsAdapter();

    static bool isService(unsigned short port);
    static unsigned short findServicePort(unsigned short localPort, unsigned short remotePort);
    
    static set<unsigned short> m_servicePorts;
    
    static set<IpAddrBinary> m_hostFilter;
    static set<uint64> m_serviceFilter;
};

#endif	/* STATSADAPTER_H */
