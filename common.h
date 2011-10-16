/* 
 * File:   common.h
 * Author: roman
 *
 * Created on 15. říjen 2011, 19:59
 */

#ifndef COMMON_H
#define	COMMON_H

#include <pcap.h>
#include <rrd.h>
#include <pthread.h>

#include <string>
#include <sstream>

#include <ctime>

#include <map>
#define unordered_map map

using std::string;
using std::ostringstream;
using std::unordered_map;
using std::make_pair;
        
typedef unsigned long IpAddrBinary;
typedef unsigned long long uint64;

#endif	/* COMMON_H */
