/* 
 * File:   StatsAdapter.cpp
 * Author: roman
 * 
 * Created on 20. říjen 2011, 10:36
 */

#include "StatsAdapter.h"

set<unsigned short> StatsAdapter::servicePorts;

struct Ipv4Addressb {
    unsigned char addr[4];
};

ostream& operator<<(ostream& os, const Ipv4Addressb& ip) {
    os 
            << (int)ip.addr[0] << "."
            << (int)ip.addr[1] << "."
            << (int)ip.addr[2] << "."
            << (int)ip.addr[3];
    return os;
}

bool isService(unsigned short port) {
    return StatsAdapter::servicePorts.find(port) != StatsAdapter::servicePorts.end();
}

unsigned short findServicePort(unsigned short localPort, unsigned short remotePort) {
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

void StatsAdapter::callHostStat(const IpAddrBinary addr, StatType type, unsigned int value) {
    
}

void StatsAdapter::callServiceStat(const IpAddrBinary addr, const L3Proto protocol, unsigned short localPort, unsigned short remotePort, StatType type, unsigned int value) {
    unsigned short service = findServicePort(localPort, remotePort);
    cout << (*((Ipv4Addressb*)&addr)) << " " << (protocol==PROTO_L3_TCP ? "TCP(" : "UDP(") << service << ") " << (type==ST_DOWNLOAD ? "<--" : "-->") << " " << value << endl; 
}
