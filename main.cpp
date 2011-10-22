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

bool App::exit = false;
string pcapFilter = "";

void signalHandler(int sig) {
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
    StatsAdapter::loadRules();
    
#ifdef LINUX
    /* Daemonize */
    //daemon(0, 0);
#endif
    
    PacketLogger pl;
    RRDUpdater updater;
    
    updater.start();   
#ifdef WIN
    pl.listInterfaces(NULL);
    cout << (pl.setInterface("\\Device\\NPF_{6F732E9A-EE1E-460D-ADC6-EB64EB656E76}") ? "int ok" : "int fa") << endl;
#else
    cout << (pl.setInterface("eth0") ? "int ok" : "int fa") << endl;
#endif
    cout << (pl.startCapture() ? "ca ok" : "ca fa") << endl;
    
    pl.join();
    updater.join();
    return 0;
}
