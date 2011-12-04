/* 
 * File:   RRD.cpp
 * Author: roman
 * 
 * Created on 15. říjen 2011, 12:53
 */

#ifndef WIN
#include <rrd.h>
#endif
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

    DEBUG_OUTPUT("callRRD: " << oss.str().c_str());
    system(oss.str().c_str());
}

const char* rrd_err = "";

int rrd_create(int argc, char** argv) { callRRD(argc, argv); return 0; }
int rrd_update(int argc, char** argv) { callRRD(argc, argv); return 0; }
void rrd_clear_error()                { }
const char* rrd_get_error()           { return rrd_err; }
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
    
#ifdef WIN
    dbname = "\"" + dbname + RRD_FILE_EXT + "\"";
#endif
    
    char filename[255];
    if (dbname.size() > 255 - 1 - 4)
        return false;
    
    strcpy(filename, dbname.c_str());
#ifdef LINUX
    strcpy(filename + dbname.size(), RRD_FILE_EXT);
#endif
    
    argv[argc++] = "rrd_create";
    
    argv[argc++] = filename;

    argv[argc++] = "--step";
    argv[argc++] = RRD_UPDATE_INTERVAL_STR;
    
    //argv[argc++] = "DS:value:DERIVE:300:0:U";
    argv[argc++] = "DS:download:DERIVE:300:0:U";
    argv[argc++] = "DS:upload:DERIVE:300:0:U";
    
    argv[argc++] = "RRA:AVERAGE:0.5:1:5760";   // 5s - den // 15
    argv[argc++] = "RRA:AVERAGE:0.5:4:10080";  // 1m - 7 dni
    argv[argc++] = "RRA:AVERAGE:0.5:20:105120"; // 5m - 1 rok
    argv[argc++] = "RRA:AVERAGE:0.5:240:35040"; // 1h - 4 roky   
    argv[argc++] = "RRA:MIN:0.5:4:10080";
    argv[argc++] = "RRA:MIN:0.5:240:35040";
    argv[argc++] = "RRA:MAX:0.5:4:10080";
    argv[argc++] = "RRA:MAX:0.5:240:35040";
    
    cleanRest(argc, argv);
    
    pthread_mutex_lock(&m_mutex);
    prepare();    
    int res = rrd_create(argc, const_cast<char**>(argv));
    pthread_mutex_unlock(&m_mutex);
    
#ifdef DEBUG
    cout << "rrd_create: " << res << endl;
    if (res) cout << "E:" << rrd_get_error() << endl;
#endif
    
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
    
#ifdef WIN    
    dbname = "\"" + dbname + RRD_FILE_EXT + "\"";
#endif
    
    char filename[255], updatestr[512];
    if (dbname.size() > 255 - 1 - 4)
        return false;
    
    strcpy(filename, dbname.c_str());
#ifdef LINUX
    strcpy(filename + dbname.size(), RRD_FILE_EXT);    
#endif
    
    argv[argc++] = "rrd_update";
    
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
    
#ifdef DEBUG
    cout << "rrd_update: " << res << endl;
    if (res) cout << "E:" << rrd_get_error() << endl;
#endif    
    
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
