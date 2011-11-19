/* 
 * File:   common.h
 * Author: roman
 *
 * Created on 15. říjen 2011, 19:59
 */

#ifndef COMMON_H
#define	COMMON_H

#include <pthread.h>

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <set>

#include <ctime>

#include <map>
// prozatim nevyuziti unordered_map pro problemy s IDE
#define unordered_map map

using namespace std;
        
typedef unsigned long IpAddrBinary;
typedef unsigned long long uint64;

#ifdef DEBUG_FULL
#define DEBUG
#define DEBUG_PACKET(x) cerr << x << endl;
#else
#define DEBUG_PACKET(x)
#endif

#ifdef DEBUG
#define DEBUG_OUTPUT(x) cout << x << endl
#else
#define DEBUG_OUTPUT(x)
#endif

#ifdef WIN
#define CONFIG_PATH 
#else
#define CONFIG_PATH "/etc/pcaprrd/"
#endif

#ifndef WIN
#ifndef LINUX
#define LINUX
#endif
#endif

#include "Config.h"

#endif	/* COMMON_H */
