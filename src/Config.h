/* 
 * File:   config.h
 * Author: roman
 *
 * Created on 23. říjen 2011, 21:48
 */

#ifndef CONFIG_H
#define	CONFIG_H

#include "common.h"

/**
 * Konfigurace aplikace a stavove promenne.
 */
namespace App {
    extern bool exit;
    
    extern string interface;
    extern string pcapFilter;
};

void loadConfig();
bool fileExists(string name);
void makeDir(string name);

#endif	/* CONFIG_H */

