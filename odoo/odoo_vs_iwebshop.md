# apache-benchmark socket recv error
http://blog.scene.ro/posts/apache-benchmark-apr_socket_recv/

```
telesoho@telesoho-Lenovo-Yoga-3-11:~/prjs$ ab -n 100 -c 30  http://test.haibaobei-ec.com:8069/
This is ApacheBench, Version 2.3 <$Revision: 1706008 $>
Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/
Licensed to The Apache Software Foundation, http://www.apache.org/

Benchmarking test.haibaobei-ec.com (be patient).....done


Server Software:        Werkzeug/0.11.15
Server Hostname:        test.haibaobei-ec.com
Server Port:            8069

Document Path:          /
Document Length:        18447 bytes

Concurrency Level:      30
Time taken for tests:   19.448 seconds
Complete requests:      100
Failed requests:        0
Total transferred:      1878500 bytes
HTML transferred:       1844700 bytes
Requests per second:    5.14 [#/sec] (mean)
Time per request:       5834.546 [ms] (mean)
Time per request:       194.485 [ms] (mean, across all concurrent requests)
Transfer rate:          94.32 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        4   73 219.3     16    1031
Processing:   741 5652 6735.8   1399   16170
Waiting:      712 5635 6726.2   1385   16047
Total:        755 5725 6726.0   1459   16218

Percentage of the requests served within a certain time (ms)
  50%   1459
  66%   2290
  75%  15852
  80%  15898
  90%  15956
  95%  16006
  98%  16104
  99%  16218
 100%  16218 (longest request)
telesoho@telesoho-Lenovo-Yoga-3-11:~/prjs$ ab -n 100 -c 30  http://test.haibaobei-ec.com:8080/
This is ApacheBench, Version 2.3 <$Revision: 1706008 $>
Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/
Licensed to The Apache Software Foundation, http://www.apache.org/

Benchmarking test.haibaobei-ec.com (be patient).....done


Server Software:        Apache/2.4.18
Server Hostname:        test.haibaobei-ec.com
Server Port:            8080

Document Path:          /
Document Length:        52291 bytes

Concurrency Level:      30
Time taken for tests:   1.339 seconds
Complete requests:      100
Failed requests:        96
   (Connect: 0, Receive: 0, Length: 96, Exceptions: 0)
Total transferred:      5264806 bytes
HTML transferred:       5228406 bytes
Requests per second:    74.71 [#/sec] (mean)
Time per request:       401.564 [ms] (mean)
Time per request:       13.385 [ms] (mean, across all concurrent requests)
Transfer rate:          3841.04 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        4   22  19.6     12      58
Processing:   118  337  73.8    354     476
Waiting:      102  327  74.0    344     462
Total:        162  359  67.3    368     533

Percentage of the requests served within a certain time (ms)
  50%    368
  66%    391
  75%    398
  80%    404
  90%    433
  95%    463
  98%    487
  99%    533
 100%    533 (longest request)
telesoho@telesoho-Lenovo-Yoga-3-11:~/prjs$ 
```
