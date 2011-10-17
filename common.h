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

#include <ctime>

#include <map>
// prozatim nevyuziti unordered_map pro problemy s IDE
#define unordered_map map

using std::string;
using std::ostringstream;
using std::unordered_map;
using std::make_pair;

using std::cout;
using std::endl;
        
typedef unsigned long IpAddrBinary;
typedef unsigned long long uint64;

#endif	/* COMMON_H */
