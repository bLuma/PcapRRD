/* 
 * File:   RRDAdapter.cpp
 * Author: roman
 * 
 * Created on 22. říjen 2011, 13:25
 */

#include "common.h"
#include "RRDUpdater.h"
#include "RRD.h"

#ifdef WIN
#include <windows.h>

/**
 * Zjistuje existuje-li soubor na disku
 * 
 * @param name jmeno souboru
 * @return true, pokud existuje
 */
bool fileExists(string name) {
    string copy = name; // + RRD_FILE_EXT;
    return GetFileAttributesA(copy.c_str()) != 0xFFFFFFFF;
}

void makeDir(string name) {
    CreateDirectoryA(name.c_str(), NULL);
}
#else
#include <sys/stat.h>
/**
 * Zjistuje existuje-li soubor na disku
 * 
 * @param name jmeno souboru
 * @return true, pokud existuje
 */
bool fileExists(string name) {
    struct stat stats;
    
    string copy = name; // + RRD_FILE_EXT;
    return stat(copy.c_str(), &stats) == 0;
}

void makeDir(string name) {
    mkdir(name.c_str(), 0775);
}
#endif

#define PATH_CONCAT(a, b) (a + "/" + b)
#define COLLECTD_TYPE "prenosy-"

RRDUpdater::RRDUpdater() : m_stats(Stats::instance()) {
}

RRDUpdater::RRDUpdater(const RRDUpdater& orig) : m_stats(Stats::instance()) {
}

RRDUpdater::~RRDUpdater() {
}

/**
 * Spusti aktualizacni vlakno.
 */
void RRDUpdater::start() {
    pthread_create(&m_thread, NULL, &loggerThread, reinterpret_cast<void*>(this));
}

/**
 * Aktualizacni vlakno.
 * 
 * @param rrdAdapter reference na RRDUpdater
 * @return nic
 */
void* RRDUpdater::loggerThread(void* rrdAdapter) {
    DEBUG_OUTPUT("RRDUpdater thread ready.");
    RRDUpdater& updater = *reinterpret_cast<RRDUpdater*>(rrdAdapter);
    time_t lastRun = time(NULL);
    
    while (!App::exit) {
        sleep(1);
        
        time_t now = time(NULL);
        if (now % RRD_UPDATE_INTERVAL) {
            if (now - lastRun > RRD_UPDATE_INTERVAL) {
                now = now - (now % RRD_UPDATE_INTERVAL);
            } else {
                continue;
            }
        }
        DEBUG_OUTPUT("Calling update process at " << now);
        
        for (HostMapIterator it = updater.m_stats.hostBegin(); it != updater.m_stats.hostEnd(); it++) {
            string hostName = convertIpAddrBinaryToString(it->first);
            string realFilename = PATH_CONCAT(hostName, COLLECTD_TYPE + hostName);
            StatsHolder localCopy = it->second;
            
            if (!fileExists(hostName)) {
                makeDir(hostName);
            }
            
            if (!fileExists(realFilename + RRD_FILE_EXT)) {
                RRD::create(realFilename);
            }
            
            RRD::update(realFilename, now, 2, reinterpret_cast<unsigned int*>(localCopy.statistics));
        }

        for (ServiceMapIterator it = updater.m_stats.serviceBegin(); it != updater.m_stats.serviceEnd(); it++) {
            string hostName = convertIpAddrBinaryToString(it->first.host);
            string serviceName = convertServiceAddrBinaryToString(it->first);
            string realFilename = PATH_CONCAT(hostName, COLLECTD_TYPE + hostName + "-" + serviceName);
            StatsHolder localCopy = it->second;
            
            if (!fileExists(hostName)) {
                makeDir(hostName);
            }
            
            if (!fileExists(realFilename + RRD_FILE_EXT)) {
                RRD::create(realFilename);
            }
            
            RRD::update(realFilename, now, 2, reinterpret_cast<unsigned int*>(localCopy.statistics));
        }      
        
        lastRun = now;
    }
    
    return NULL;
}
