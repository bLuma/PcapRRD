/* 
 * File:   RRD.h
 * Author: roman
 *
 * Created on 15. říjen 2011, 12:53
 */

#ifndef RRD_H
#define	RRD_H

#include "common.h"

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
VDEF:vname=RPN expression - agregace (max, min, average)
CDEF:vname=RPN expression - výpočty nové množiny bodů

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

#define MAKE_VAL_PAIR(a, b) \
        unsigned int tValsDum[2]; \
        tValsDum[0] = (unsigned int)(a); \
        tValsDum[1] = (unsigned int)(b);

#define GET_VAL_PAIR \
        tValsDum

/**
 * Trida slouzici k manipulaci s RRD databazemi. Vyuziva C API 
 * knihovny librrd.
 */
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
    
    /**
     * Mutex pro vylucny pristup k RRD db.
     */
    static pthread_mutex_t m_mutex;
};

#endif	/* RRD_H */
