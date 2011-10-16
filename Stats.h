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
    SR_TCP,
    SR_UDP,
    SR_MAX
};

struct StatsHolder {
    unsigned long int statistics[ST_MAX];
    
    StatsHolder() {
        statistics[ST_DOWNLOAD] = 0;
        statistics[ST_UPLOAD] = 0;
    }
};

struct ServiceAddrBinary {
    IpAddrBinary host;
    ServiceType stype;
    unsigned short port;
    
    ServiceAddrBinary(IpAddrBinary h, ServiceType s, unsigned short p)
            : host(h), stype(s), port(p) {
    }
    
    uint64 keyVal() const {
        return uint64(uint64(host) << 20) | uint64(stype << 16) | uint64(port);
    }
    
    bool operator<(const ServiceAddrBinary& ref) const {
        return keyVal() < ref.keyVal();
    }
    
};

typedef unordered_map<IpAddrBinary, StatsHolder> HostMap;
typedef unordered_map<ServiceAddrBinary, StatsHolder> ServiceMap;

string convertIpAddrBinaryToString(IpAddrBinary addr);
string convertServiceAddrBinaryToString(ServiceAddrBinary addr);

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
    void AddCounterService(IpAddrBinary host, ServiceType stype, unsigned short port, StatType type, unsigned int value);
    
    // pull
    
private:
    HostMap m_hosts;
    ServiceMap m_services;
};

#endif	/* STATS_H */

