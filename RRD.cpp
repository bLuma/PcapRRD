/* 
 * File:   RRD.cpp
 * Author: roman
 * 
 * Created on 15. říjen 2011, 12:53
 */

#include <rrd.h>
#include "RRD.h"
#include <cstring>

pthread_mutex_t RRD::m_mutex = PTHREAD_MUTEX_INITIALIZER;

#ifdef WIN
void callRRD(int argc, char** argv) {
    ostringstream oss;
    oss << "./rrdtool.exe ";
    if (argv[0] == "rrd_create")
        oss << "create";
    else
        oss << "update";
    
    for (int i = 1; i < argc; i++)
        oss << " " << argv[i];

    cout << oss.str().c_str() << endl;
    system(oss.str().c_str());
}

int rrd_create(int argc, char** argv) { callRRD(argc, argv); return 0; }
int rrd_update(int argc, char** argv) { callRRD(argc, argv); return 0; }
void rrd_clear_error() { }
#endif

/**
 * Konstruktor privatni, trida je staticka.
 */
RRD::RRD() {
}

/**
 * Kopirovaci konstruktor.
 * 
 * @param orig instance RRD
 */
RRD::RRD(const RRD& orig) {
}

/**
 * Destruktor
 */
RRD::~RRD() {
}

/**
 * Vytvori novou RRD databazi.
 * 
 * @param filename nazev databaze
 * @return true pri uspechu vytvoreni db
 */
bool RRD::create(string dbname/*, dbtype type */) {   
    int argc = 0;
    const char* argv[MAX_ARGV];
    
    char filename[255];
    if (dbname.size() > 255 - 1 - 4)
        return false;
    
    strcpy(filename, dbname.c_str());
    strcpy(filename + dbname.size(), ".rrd");
    
    argv[argc++] = "rrd_create";
    //argv[argc++] = "~/PcapRRD/dist/Debug/GNU-Linux-x86/";
    
    argv[argc++] = filename;

    argv[argc++] = "--step";
    argv[argc++] = "5";
    
    argv[argc++] = "DS:download:DERIVE:300:0:U";
    argv[argc++] = "DS:upload:DERIVE:300:0:U";
    
    argv[argc++] = "RRA:AVERAGE:0.5:1:86400";   // 5s - den
    argv[argc++] = "RRA:AVERAGE:0.5:12:10080";  // 1m - 7 dni
    argv[argc++] = "RRA:AVERAGE:0.5:60:105120"; // 5m - 1 rok
    argv[argc++] = "RRA:AVERAGE:0.5:720:35040"; // 1h - 4 roky
    cleanRest(argc, argv);
        
    pthread_mutex_lock(&m_mutex);
    prepare();    
    int res = rrd_create(argc, const_cast<char**>(argv));
    pthread_mutex_unlock(&m_mutex);
    
    return !res;
}

/**
 * Aktualizuje data v RRD databazi.
 * 
 * @param dbname nazev databaze
 * @param time casova znacka
 * @param cnt pocet hodnot v DB
 * @param datasets hodnoty jednotlivych polozek v DB
 * @return true pri uspechu aktualizace dat
 */
bool RRD::update(string dbname, time_t time, unsigned int cnt, unsigned int* datasets) {
    int argc = 0;
    const char* argv[MAX_ARGV];
    
    char filename[255], updatestr[512];
    if (dbname.size() > 255 - 1 - 4)
        return false;
    
    strcpy(filename, dbname.c_str());
    strcpy(filename + dbname.size(), ".rrd");    
    
    argv[argc++] = "rrd_update";
    //argv[argc++] = "~/PcapRRD/dist/Debug/GNU-Linux-x86/";
    argv[argc++] = filename;
    
    ostringstream oss;
    oss << time;
    for (unsigned int i = 0; i < cnt; i++) {
        oss << ":" << *datasets;
        datasets++;
    }

    string tmp = oss.str();
    if (tmp.size() > 512 - 1)
        return false;
    
    strcpy(updatestr, tmp.c_str());
    
    argv[argc++] = updatestr;
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
