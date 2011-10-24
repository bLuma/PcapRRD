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
    string copy = name + ".rrd";
    return GetFileAttributesA(copy.c_str()) != 0xFFFFFFFF;
}
#else
/**
 * Zjistuje existuje-li soubor na disku
 * 
 * @param name jmeno souboru
 * @return true, pokud existuje
 */
bool fileExists(string name) {
    return false;
}
#endif

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
    RRDUpdater& updater = *reinterpret_cast<RRDUpdater*>(rrdAdapter);
    time_t lastRun = time(NULL);
    
    while (true) {
        sleep(1);
        
        time_t now = time(NULL);
        if (now % 5) {
            if (now - lastRun > 5) {
                now = now - (now % 5);
            } else {
                continue;
            }
        }
        
        for (HostMapIterator it = updater.m_stats.hostBegin(); it != updater.m_stats.hostEnd(); it++) {
            string name = convertIpAddrBinaryToString(it->first);
            StatsHolder localCopy = it->second;
            
            if (!fileExists(name)) {
                RRD::create(name);
            }
            
            RRD::update(name, now, 2, reinterpret_cast<unsigned int*>(localCopy.statistics));
        }

        for (ServiceMapIterator it = updater.m_stats.serviceBegin(); it != updater.m_stats.serviceEnd(); it++) {
            string name = convertServiceAddrBinaryToString(it->first);
            StatsHolder localCopy = it->second;
            
            if (!fileExists(name)) {
                RRD::create(name);
            }
            
            RRD::update(name, now, 2, reinterpret_cast<unsigned int*>(localCopy.statistics));
        }      
        
        lastRun = now;
    }
    
    return NULL;
}
