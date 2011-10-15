/* 
 * File:   RRD.cpp
 * Author: roman
 * 
 * Created on 15. říjen 2011, 12:53
 */

#include <pcap/pcap.h>

#include "RRD.h"

/**
 * Konstruktor - privatni. Trida je staticka.
 */
RRD::RRD() {
}

RRD::RRD(const RRD& orig) {
}

RRD::~RRD() {
}

void RRD::create() {
    prepare();
    
    int argc = 0;
    const char* argv[MAX_ARGV];
    argv[argc++] = "rrd_create";
    //argv[argc++] = "~/PcapRRD/dist/Debug/GNU-Linux-x86/";
    argv[argc++] = "test.rrd";
    argv[argc++] = "--step";
    argv[argc++] = "5";
    argv[argc++] = "DS:data:DERIVE:300:0:U";
    argv[argc++] = "RRA:AVERAGE:0.5:1:100";
    cleanRest(argc, argv);
        
    int res = rrd_create(argc, const_cast<char**>(argv));
    printf("%i\n", res);
    printf("%s\n", rrd_get_error());
}

/**
 Pripravi prostredi pro volani funkci RRD knihovny.
 */
void RRD::prepare() {
    optind = 1;
    opterr = 0;
    rrd_clear_error();
}

/**
 * Vycisti zbytek pole argumentu od bordelu.
 * 
 * @param argc pocet platnych argumentu
 * @param argv pole argumentu
 */
void RRD::cleanRest(int argc, const char** argv) {
    for (int i = argc; i < MAX_ARGV; i++)
        argv[i] = "";
}


