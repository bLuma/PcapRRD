/* 
 * File:   RRD.h
 * Author: roman
 *
 * Created on 15. říjen 2011, 12:53
 */

#ifndef RRD_H
#define	RRD_H

#include <rrd.h>

#define MAX_ARGV 255

class RRD {
private:
    RRD();
    RRD(const RRD& orig);

public:
    virtual ~RRD();
    
    static void create();

private:
    static void prepare();
    static void cleanRest(int argc, const char** argv);
};

#endif	/* RRD_H */

