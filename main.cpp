/* 
 * File:   main.cpp
 * Author: roman
 *
 * Created on 15. říjen 2011, 10:50
 */

#include <cstdlib>
#include "RRD.h"
#include "Stats.h"
#include "PacketLogger.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    PacketLogger pl;
#ifdef WIN
    pl.listInterfaces();
    //pl.setFirstAvailableInterface();
    cout << (pl.setInterface("\\Device\\NPF_{6F732E9A-EE1E-460D-ADC6-EB64EB656E76}") ? "int ok" : "int fa") << endl;
#else
    cout << (pl.setInterface("eth0") ? "int ok" : "int fa") << endl;
#endif
    cout << (pl.startCapture() ? "ca ok" : "ca fa") << endl;
    pl.join();
    
    //Stats stat;
    //stat.AddCounter(0x000000FF, ST_DOWNLOAD, 100);
    //stat.AddCounterService(0xFF, SR_TCP, 10, ST_DOWNLOAD, 100);
    //stat.AddCounterService(0x10, SR_UDP, 10, ST_DOWNLOAD, 100);
    
    //RRD::create("test.file.rrd");
    
    //MAKE_VAL_PAIR(10, 20);
    //RRD::update("test.file.rrd", time(NULL), 2, GET_VAL_PAIR);
    
    return 0;
}
