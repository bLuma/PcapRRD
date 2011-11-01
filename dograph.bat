rrdtool.exe graph test.png -s end-1h -w 800 -h 300 -E DEF:a=stat-67217600-80.rrd:download:AVERAGE DEF:b=stat-67217600-80.rrd:upload:AVERAGE CDEF:c=1,b,* DEF:d=stat-67217600.rrd:download:AVERAGE DEF:e=stat-67217600.rrd:upload:AVERAGE LINE1:d#0000FF LINE1:e#FF00FF LINE1:c#00FF00 LINE1:a#FF0000
start test.png
