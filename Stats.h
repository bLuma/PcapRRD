/* 
 * File:   Stats.h
 * Author: roman
 *
 * Created on 15. říjen 2011, 20:07
 */

#ifndef STATS_H
#define	STATS_H

#include "common.h"

enum StatType {
    ST_DOWNLOAD,
    ST_UPLOAD,
    ST_MAX
};

enum ServiceType {
    SRT_TCP,
    SRT_UDP,
    SRT_MAX
            
};

typedef unsigned long IpAddrBinary;

typedef unordered_map<IpAddrBinary, StatsHolder> HostMap;
typedef unordered_map<ServiceAddrBinary, StatsHolder> ServiceMap;


struct StatsHolder {
    unsigned long int statistics[ST_MAX];
};

struct ServiceAddrBinary {
    IpAddrBinary host;
    ServiceType stype;
    unsigned short port;
};


/**
 * Stats uchovava souhrnne informace ze zachycenych paketu.
 */
class Stats {
public:
    Stats();
    Stats(const Stats& orig);
    virtual ~Stats();
    
    // push
    void AddCounter(IpAddrBinary host, StatType type, unsigned int value);
    //void AddCounterService(IpAddrBinary host, ServiceType stype, unsigned short port, StatType type, unsigned int value);
    
    // pull
    
private:
    HostMap m_hosts;
    ServiceMap m_services;
};

#endif	/* STATS_H */

