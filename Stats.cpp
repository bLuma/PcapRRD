/* 
 * File:   Stats.cpp
 * Author: roman
 * 
 * Created on 15. říjen 2011, 20:07
 */

#include <string>

#include "Stats.h"
#include "RRD.h"

string convertIpAddrBinaryToString(IpAddrBinary addr) {
    ostringstream oss;
    oss << "stat-" << addr;
    return oss.str();
}

string convertServiceAddrBinaryToString(ServiceAddrBinary addr) {
    ostringstream oss;
    oss << "stat-" << addr.host << "-" << (addr.stype * 0xFFFF + addr.port);
    return oss.str();
}

Stats::Stats() {
}

Stats::Stats(const Stats& orig) {
}

Stats::~Stats() {
}

void Stats::AddCounter(IpAddrBinary host, StatType type, unsigned int value) {
    HostMap::iterator it = m_hosts.find(host);
    if (it == m_hosts.end()) {
        RRD::create(convertIpAddrBinaryToString(host));
        
        m_hosts.insert(make_pair(host, StatsHolder()));
        it = m_hosts.find(host);
    }
    
    StatsHolder& holder = it->second;
    holder.statistics[type] += value;
}

void Stats::AddCounterService(IpAddrBinary host, ServiceType stype, unsigned short port, StatType type, unsigned int value) {
    ServiceAddrBinary saddr(host, stype, port);
    
    ServiceMap::iterator it = m_services.find(saddr);
    if (it == m_services.end()) {
        RRD::create(convertServiceAddrBinaryToString(saddr));
        
        m_services.insert(make_pair(saddr, StatsHolder()));
        it = m_services.find(saddr);
    }
    
    StatsHolder& holder = it->second;
    holder.statistics[type] += value;
    
}