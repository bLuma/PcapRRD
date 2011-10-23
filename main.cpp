/* 
 * File:   main.cpp
 * Author: roman
 *
 * Created on 15. říjen 2011, 10:50
 */

#include <cstdlib>
#include <signal.h>
#include <sys/types.h>
#include "RRD.h"
#include "Stats.h"
#include "PacketLogger.h"
#include "StatsAdapter.h"
#include "RRDUpdater.h"

void loadConfig();

void signalHandler(int sig) {
    //cout << "exit!" << endl;
    App::exit = true;
}

/*
 * 
 */
int main(int argc, char** argv) {
    /* Nastaveni zachytavani signalu */
    signal(SIGINT, signalHandler);
    signal(SIGHUP, signalHandler);
    signal(SIGQUIT, signalHandler);
    signal(SIGABRT, signalHandler);
    signal(SIGTERM, signalHandler);
    signal(SIGTSTP, signalHandler);
    
    /* Nacti konfiguraci */
    loadConfig();
    StatsAdapter::loadRules();
    
#ifdef LINUX
    /* Daemonize */
    //daemon(0, 0);
#endif
    
    PacketLogger pl;
    RRDUpdater updater;
    
    updater.start();

    if (pl.setInterface(App::interface)) {
        cout << "Capturing at: " << App::interface.c_str() << endl;
    } else {
        cerr << "Nelze nastavit interface!" << endl;
        return 9;
    }
    pl.setFilter(App::pcapFilter);
    
    if (!pl.startCapture())
        return 8;
    
    pl.join();
    updater.join();
    return 0;
}
