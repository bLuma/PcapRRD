/* 
 * File:   RRDAdapter.h
 * Author: roman
 *
 * Created on 22. říjen 2011, 13:25
 */

#ifndef RRDADAPTER_H
#define	RRDADAPTER_H

#include "common.h"
#include "Stats.h"

#define PATH_CONCAT(a, b) (a + "/" + b)
#define COLLECTD_TYPE "prenosy-"

/**
 * Trida pro opakovane ukladani dat do RRD databazi.
 */
class RRDUpdater {
public:
    RRDUpdater();
    RRDUpdater(const RRDUpdater& orig);
    virtual ~RRDUpdater();

    void start();
    
    /**
     * Spoji vlakna a pocka na ukonceni vlakna RRDUpdateru.
     */
    void join() {
        pthread_join(m_thread, NULL);
    }
    
private:
    static void* loggerThread(void* rrdAdapter);
    
    /**
     * Reference na statistiky.
     */
    Stats& m_stats;
    
    /**
     * Vlakno RRDUpdateru.
     */
    pthread_t m_thread;
};

#endif	/* RRDADAPTER_H */

