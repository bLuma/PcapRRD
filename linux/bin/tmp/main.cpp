#include <iostream>
using namespace std;
#include <rrd.h>
#include <pthread.h>

int main() {
	int lo = 5;
	pthread_attr_destroy(NULL);
	pthread_exit(&lo);
	rrd_update(0, NULL);
	return 0;
}

