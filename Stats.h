/* 
 * File:   Stats.h
 * Author: roman
 *
 * Created on 15. říjen 2011, 20:07
 */

#ifndef STATS_H
#define	STATS_H

#include "common.h"

/**
 * Typ statistiky - download, upload.
 */
enum StatType {
    ST_DOWNLOAD,
    ST_UPLOAD,
    ST_MAX
};

/**
 * Typ protokolu ctvrte vrstvy.
 */
enum ServiceType {
    SR_TCP,
    SR_UDP,
    SR_MAX
};

/**
 * Struktura pro uchovani statistik. 
 */
struct StatsHolder {
    unsigned long int statistics[ST_MAX];
    
    StatsHolder() {
        statistics[ST_DOWNLOAD] = 0;
        statistics[ST_UPLOAD] = 0;
    }
};

/**
 * Struktura pro adresaci ctvrte vrstvy.
 */
struct ServiceAddrBinary {
    IpAddrBinary host;
    ServiceType stype;
    unsigned short port;
    
    ServiceAddrBinary()
            : host(0), stype(SR_MAX), port(0) {
    }
    
    ServiceAddrBinary(IpAddrBinary h, ServiceType s, unsigned short p)
            : host(h), stype(s), port(p) {
    }
    
    inline uint64 keyVal() const {
        return uint64(uint64(host) << 24) | uint64(stype << 16) | uint64(port);
    }
    
    bool operator<(const ServiceAddrBinary& ref) const {
        return keyVal() < ref.keyVal();
    }
    
};

string convertIpAddrBinaryToString(IpAddrBinary addr);
string convertServiceAddrBinaryToString(ServiceAddrBinary addr);

/// Mapy pro ulozeni statistik
typedef unordered_map<IpAddrBinary, StatsHolder> HostMap;
typedef unordered_map<ServiceAddrBinary, StatsHolder> ServiceMap;
    
typedef HostMap::const_iterator HostMapIterator;
typedef ServiceMap::const_iterator ServiceMapIterator;

/**
 * Stats uchovava souhrnne informace ze zachycenych paketu.
 */
class Stats {
public:      
    /**
     * Implementace singletonu. Vraci instanci Stats.
     * 
     * @return singleton tridy Stats
     */
    static Stats& instance() {
        if (!m_instance)
            m_instance = new Stats;
        
        return *m_instance;
    }
    
    // push
    void AddCounter(IpAddrBinary host, StatType type, unsigned int value);
    void AddCounterService(IpAddrBinary host, ServiceType stype, unsigned short port, StatType type, unsigned int value);
    
    // pull
    HostMapIterator hostBegin() const { return m_hosts.begin(); }
    HostMapIterator hostEnd() const { return m_hosts.end(); }
    ServiceMapIterator serviceBegin() const { return m_services.begin(); }
    ServiceMapIterator serviceEnd() const { return m_services.end(); }
    
private:
    Stats();
    Stats(const Stats& orig);
    virtual ~Stats();
    
    /**
     * Singleton tridy.
     */
    static Stats* m_instance;
    
    /**
     * Uchovava statistiky jednotlivych hostu.
     */
    HostMap m_hosts;
    
    /**
     * Uchovava statistiky sluzeb na L4.
     */
    ServiceMap m_services;
};

#endif	/* STATS_H */
