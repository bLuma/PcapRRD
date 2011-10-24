rrdtool.exe graph test.png -s end-1h DEF:a=stat-50440384-80.rrd:download:AVERAGE DEF:b=stat-50440384-80.rrd:upload:AVERAGE CDEF:c=1,b,* LINE1:c#00FF00 LINE1:a#FF0000
start test.png
