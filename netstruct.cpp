
#include "netstruct.h"
#include "common.h"

ostream& operator<<(ostream& os, const MacAddress& mac) {
    os << hex << setw(2) << setfill('0')
            << (int)mac.addr[0] 
            << (int)mac.addr[1] 
            << (int)mac.addr[2] 
            << (int)mac.addr[3] 
            << (int)mac.addr[4] 
            << (int)mac.addr[5]
            << dec;
    return os;
}

ostream& operator<<(ostream& os, const Ipv4Address& ip) {
    os 
            << (int)ip.addr[0] << "."
            << (int)ip.addr[1] << "."
            << (int)ip.addr[2] << "."
            << (int)ip.addr[3];
    return os;
}

IpAddrBinary convertStringToIpAddrBinary(string str) {
    unsigned int ip = 0;
    unsigned int tmp = 0;
    
    for (int i = 0; i < 4; i++) {
        string token = str.substr(0, str.find('.'));
        istringstream ss(token);
        ss >> tmp;
        //cerr << tmp << " ... ";
        //ip <<= 8;
        ip |= (tmp << ((i)*8));
        
        str = str.substr(str.find('.') + 1);
    }
    
    //cerr << hex << ip;
    return ip;
}
