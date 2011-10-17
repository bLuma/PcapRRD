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
    pl.setInterface(0);
    
    //Stats stat;
    //stat.AddCounter(0x000000FF, ST_DOWNLOAD, 100);
    //stat.AddCounterService(0xFF, SR_TCP, 10, ST_DOWNLOAD, 100);
    //stat.AddCounterService(0x10, SR_UDP, 10, ST_DOWNLOAD, 100);
    
    //RRD::create("test.file.rrd");
    
    //MAKE_VAL_PAIR(10, 20);
    //RRD::update("test.file.rrd", time(NULL), 2, GET_VAL_PAIR);
    
    return 0;
}

