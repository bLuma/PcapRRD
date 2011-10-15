/* 
 * File:   main.cpp
 * Author: roman
 *
 * Created on 15. říjen 2011, 10:50
 */

#include <cstdlib>
#include <pcap.h>
#include "RRD.h"
#include <pthread.h>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    RRD::create("test.file.rrd");
    RRD::update("test.file.rrd", time(NULL), 2, MAKE_VAL_PAIR(1,2));
    return 0;
}

