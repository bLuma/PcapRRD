/* 
 * File:   RRD.h
 * Author: roman
 *
 * Created on 15. říjen 2011, 12:53
 */

#ifndef RRD_H
#define	RRD_H

#include <rrd.h>
#include <time.h>
#include <sstream>
#include <string>
#include <pthread.h>

using std::string;
using std::ostringstream;

#define MAX_ARGV 255

/*
rrd create
rrdtool create filename [--start|-b start time] [--step|-s step] [--no-overwrite] [DS:ds-name:DST:dst arguments] [RRA:CF:cf arguments]
DS:ds-name:GAUGE | COUNTER | DERIVE | ABSOLUTE:heartbeat:min:max
RRA:AVERAGE | MIN | MAX | LAST:xff:steps:rows

rrd update
rrdtool {update | updatev} filename [--template|-t ds-name[:ds-name]...] [--daemon address] [--] N|timestamp:value[:value...] at-timestamp@value[:value...] [timestamp:value[:value...] ...]

rrd graph 
DEF:<vname>=<rrdfile>:<ds-name>:<CF>[:step=<step>][:start=<time>][:end=<time>][:reduce=<CF>]
VDEF:vname=RPN expression
CDEF:vname=RPN expression

PRINT:vname:format
GPRINT:vname:format
COMMENT:text
VRULE:time#color[:legend][:dashes[=on_s[,off_s[,on_s,off_s]...]][:dash-offset=offset]]
HRULE:value#color[:legend][:dashes[=on_s[,off_s[,on_s,off_s]...]][:dash-offset=offset]]
LINE[width]:value[#color][:[legend][:STACK]][:dashes[=on_s[,off_s[,on_s,off_s]...]][:dash-offset=offset]]
AREA:value[#color][:[legend][:STACK]]
TICK:vname#rrggbb[aa][:fraction[:legend]]
SHIFT:vname:offset
TEXTALIGN:{left|right|justified|center}
PRINT:vname:CF:format (deprecated)
GPRINT:vname:CF:format (deprecated)
STACK:vname#color[:legend] (deprecated)
 */

typedef unsigned long long int uint64;
#define MAKE_VAL_PAIR(a, b) &(uint64 tVals = uint64(uint64(a) << 32 | b))

class RRD {
private:
    RRD();
    RRD(const RRD& orig);

public:
    virtual ~RRD();
    
    static bool create(string filename/*, dbtype type */);
    static bool update(string filename, time_t time, unsigned int cnt, unsigned int* datasets);

private:
    static void prepare();
    static void cleanRest(int argc, const char** argv);
    
    static pthread_mutex_t m_mutex = PTHREAD_MUTEX_INITIALIZER;
};

#endif	/* RRD_H */

