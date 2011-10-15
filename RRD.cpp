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

bool RRD::create(string filename/*, dbtype type */) {   
    int argc = 0;
    const char* argv[MAX_ARGV];
    argv[argc++] = "rrd_create";
    //argv[argc++] = "~/PcapRRD/dist/Debug/GNU-Linux-x86/";
    argv[argc++] = filename.c_str();
    argv[argc++] = "--step";
    argv[argc++] = "5";
    argv[argc++] = "DS:data:DERIVE:300:0:U";
    argv[argc++] = "RRA:AVERAGE:0.5:1:100";
    cleanRest(argc, argv);
        
    pthread_mutex_lock(&m_mutex);
    prepare();    
    int res = rrd_create(argc, const_cast<char**>(argv));
    pthread_mutex_unlock(&m_mutex);
    
    return !res;
}

bool RRD::update(string filename, time_t time, unsigned int cnt, unsigned int* datasets) {
    int argc = 0;
    const char* argv[MAX_ARGV];
    argv[argc++] = "rrd_update";
    //argv[argc++] = "~/PcapRRD/dist/Debug/GNU-Linux-x86/";
    argv[argc++] = filename.c_str();
    
    ostringstream oss;
    oss << time;
    for (int i = 0; i < cnt; i++) {
        oss << ":" << *datasets;
        datasets++;
    }

    argv[argc++] = oss.str().c_str();
    cleanRest(argc, argv);
        
    pthread_mutex_lock(&m_mutex);
    prepare();    
    int res = rrd_update(argc, const_cast<char**>(argv));
    pthread_mutex_unlock(&m_mutex);
    
    return !res; 
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


