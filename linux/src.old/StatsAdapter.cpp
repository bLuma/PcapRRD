/* 
 * File:   StatsAdapter.cpp
 * Author: roman
 * 
 * Created on 20. říjen 2011, 10:36
 */

#include "StatsAdapter.h"
#include "netstruct.h"
#include "Stats.h"
#include <fstream>

set<unsigned short> StatsAdapter::m_servicePorts;
set<IpAddrBinary> StatsAdapter::m_hostFilter;
set<uint64> StatsAdapter::m_serviceFilter;

/**
 * Zjistuje je-li port sluzbou.
 * 
 * @param port cislo portu
 * @return true, pokud se jedna o znamou sluzbu
 */
bool StatsAdapter::isService(unsigned short port) {
    return m_servicePorts.find(port) != m_servicePorts.end();
}

/**
 * Snazi se najit port, ke kteremu by mely byt pripocitany statistiky.
 * 
 * @param localPort mistni port
 * @param remotePort vzdaleny port
 * @return cislo portu, ktery by mel byt sluzbou
 */
unsigned short StatsAdapter::findServicePort(unsigned short localPort, unsigned short remotePort) {
    if (isService(localPort))
        return localPort;
    else if (isService(remotePort))
        return remotePort;
    
    if (localPort < 1024)
        return localPort;
    else if (remotePort < 1024)
        return remotePort;

    return localPort;
}

StatsAdapter::StatsAdapter() {
}

StatsAdapter::StatsAdapter(const StatsAdapter& orig) {
}

StatsAdapter::~StatsAdapter() {
}

/**
 * Adapter pro volani aktualizace statistik.
 * 
 * @param addr adresa hosta
 * @param type typ statistiky
 * @param value hodnota
 */
void StatsAdapter::callHostStat(const IpAddrBinary addr, StatType type, unsigned int value) {
    if (m_hostFilter.find(addr) == m_hostFilter.end())
        return;
    
    Stats::instance().AddCounter(
        addr,
        type,
        value);
}

/**
 * Adapter pro volani aktualizace statistik.
 * 
 * @param addr adresa hosta
 * @param protocol protokol
 * @param localPort mistni port
 * @param remotePort vzdaleny port
 * @param type typ statistiky
 * @param value hodnota
 */
void StatsAdapter::callServiceStat(const IpAddrBinary addr, const L3Proto protocol, unsigned short localPort, unsigned short remotePort, StatType type, unsigned int value) {
    unsigned short service = findServicePort(localPort, remotePort);
    
    ServiceAddrBinary sab;
    sab.host = addr;
    sab.port = service;
    sab.stype = protocol == PROTO_L3_TCP ? SR_TCP : SR_UDP;
    
    //cout << hex << sab.keyVal() << dec << endl;
    
    if (m_serviceFilter.find(sab.keyVal()) == m_serviceFilter.end())
        return;
    
    //cout << (*((Ipv4Address*)&addr)) << " " << (protocol==PROTO_L3_TCP ? "TCP(" : "UDP(") << service << ") " << (type==ST_DOWNLOAD ? "<--" : "-->") << " " << value << endl; 
    
    Stats::instance().AddCounterService(
        addr,
        protocol == PROTO_L3_TCP ? SR_TCP : SR_UDP,
        service,
        type,
        value);
}

/**
 * Prida port sluzby do seznamu.
 * 
 * @param port cislo portu
 */
void StatsAdapter::addServicePort(unsigned short port) {
    m_servicePorts.insert(port);
}

/**
 * Nacte zachytavaci pravidla ze souboru.
 */
void StatsAdapter::loadRules() {
    ifstream file(CONFIG_PATH "rules.cfg");
    if (!file.is_open())
        return;

    while (!file.eof() && file.good()) {
        string line;
        getline(file, line);
        istringstream iss(line);
        
        if (file.eof() || line.empty())
            break;
        
        if (line[0] == '#')
            continue;
        
        string type, address;
        iss >> type >> address;
        
        IpAddrBinary ip = convertStringToIpAddrBinary(address);
        
        if (type == "H") {
            m_hostFilter.insert(ip);
        } else if (type == "S") {
            ServiceAddrBinary sab;
            sab.host = ip;
            
            iss >> type >> sab.port;
            sab.stype = type == "TCP" ? SR_TCP : SR_UDP;

            m_serviceFilter.insert(sab.keyVal());
            m_servicePorts.insert(sab.port);
        } else {
            continue;
        }
    }
    
    file.close();
}
