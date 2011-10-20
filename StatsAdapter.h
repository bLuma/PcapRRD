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

class StatsAdapter {
public:
    StatsAdapter();
    StatsAdapter(const StatsAdapter& orig);
    virtual ~StatsAdapter();
    
    static void callHostStat(const IpAddrBinary addr, StatType type, unsigned int value);
    static void callServiceStat(const IpAddrBinary addr, const L3Proto protocol, unsigned short localPort, unsigned short remotePort, StatType type, unsigned int value);
    
    static set<unsigned short> servicePorts;
private:

};

#endif	/* STATSADAPTER_H */
