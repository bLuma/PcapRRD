/* 
 * File:   main.cpp
 * Author: roman
 *
 * Created on 15. říjen 2011, 10:50
 */

#include <cstdlib>
#include "RRD.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    RRD::create("test.file.rrd");
    
    MAKE_VAL_PAIR(10, 20);
    RRD::update("test.file.rrd", time(NULL), 2, GET_VAL_PAIR);
    
    return 0;
}

