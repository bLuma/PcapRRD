/* 
 * File:   Stats.cpp
 * Author: roman
 * 
 * Created on 15. říjen 2011, 20:07
 */

#include "Stats.h"
#include "RRD.h"

Stats* Stats::m_instance = NULL;

/**
 * Prevede binarni podobu IP adresy na retezec.
 * 
 * @param addr IP adresa
 * @return usporne textove vyjadreni adresy
 */
string convertIpAddrBinaryToString(IpAddrBinary addr) {
    ostringstream oss;
    //oss << "stat-" << addr;
    oss << (addr & 0xFF) << ".";
    oss << ((addr >> 8) & 0xFF) << ".";
    oss << ((addr >> 16) & 0xFF) << ".";
    oss << ((addr >> 24) & 0xFF);
    
    return oss.str();
}

/**
 * Prevede binarni podobu L4 adresy na retezec.
 * 
 * @param addr L4 adresa
 * @return usporne textove vyjadreni adresy
 */
string convertServiceAddrBinaryToString(const ServiceAddrBinary& addr) {
    ostringstream oss;
    //oss << "stat-" << addr.host << "-" << (addr.stype * 0xFFFF + addr.port);
    //oss << convertIpAddrBinaryToString(addr.host).c_str() << "-";
    //oss << (addr.stype == SR_TCP ? "TCP(" : "UDP(") << addr.port << ")";
    oss << (addr.stype == SR_TCP ? "TCP-" : "UDP-") << addr.port;
    
    return oss.str();
}

/**
 * Konstruktor.
 */
Stats::Stats() {
}

/**
 * Destruktor.
 * 
 * @param orig reference
 */
Stats::Stats(const Stats& orig) {
}

/**
 * Destruktor
 */
Stats::~Stats() {
}

/**
 * Inkrementuje statistiku hosta.
 * 
 * @param host IP adresa hosta
 * @param type typ statistiky
 * @param value pridana hodnota
 */
void Stats::AddCounter(IpAddrBinary host, StatType type, unsigned int value) {
    HostMap::iterator it = m_hosts.find(host);
    if (it == m_hosts.end()) {
        m_hosts.insert(make_pair(host, StatsHolder()));
        it = m_hosts.find(host);
    }
    
    StatsHolder& holder = it->second;
    holder.statistics[type] += value;
}

/**
 * Inkrementuje statistiku L4 sluzby.
 * 
 * @param host IP adresa hosta
 * @param stype typ L4 protokolu
 * @param port port L4
 * @param type typ statistiky
 * @param value pridana hodnota
 */
void Stats::AddCounterService(IpAddrBinary host, ServiceType stype, unsigned short port, StatType type, unsigned int value) {
    ServiceAddrBinary saddr(host, stype, port);
    
    ServiceMap::iterator it = m_services.find(saddr);
    if (it == m_services.end()) {
        m_services.insert(make_pair(saddr, StatsHolder()));
        it = m_services.find(saddr);
    }
    
    StatsHolder& holder = it->second;
    holder.statistics[type] += value;
}
