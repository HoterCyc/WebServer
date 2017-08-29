## codelover http服务器(待完善)

    为学习linux下高并发服务器开发,写了这个http服务器
    特点:
        1,基于事件触发
        2,线程池
        3,生产者消费者模型
        4,epoll

### 项目目录
-   DealRequest.h
    -   接收请求
-   EventTree.h
    -   事件树 监听链接请求和数据接受请求
-   Http.h
    -   处理http请求
-   linkTab.h
    -   通用数据结构:链表
-   ManagePthread.h
    -   线程池管理者
-   PthredaPool.h
    -   线程池
-   Queue.h
    -   通用数据结构:队列
-   server.c
    -   服务器主函数
-   SocketConnect.h
    -   socket连接操作


### 服务器并发测试结果
    测试工具:ab

#### 2017-8-29
------------------------------
    codelover@codelover ~ >_$ ab -n 1000 -c 1000 http://127.0.0.1:8089/index.htm
    This is ApacheBench, Version 2.3 <$Revision: 1796539 $>
    Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/
    Licensed to The Apache Software Foundation, http://www.apache.org/

    Benchmarking 127.0.0.1 (be patient)
    Completed 100 requests
    Completed 200 requests
    Completed 300 requests
    Completed 400 requests
    Completed 500 requests
    Completed 600 requests
    Completed 700 requests
    Completed 800 requests
    Completed 900 requests
    Completed 1000 requests
    Finished 1000 requests


    Server Software:        codelover
    Server Hostname:        127.0.0.1
    Server Port:            8089

    Document Path:          /index.html
    Document Length:        10240 bytes

    Concurrency Level:      1000
    Time taken for tests:   0.219 seconds
    Complete requests:      1000
    Failed requests:        0
    Total transferred:      10351000 bytes
    HTML transferred:       10240000 bytes
    Requests per second:    4557.20 [#/sec] (mean)
    Time per request:       219.433 [ms] (mean)
    Time per request:       0.219 [ms] (mean, across all concurrent requests)
    Transfer rate:          46065.99 [Kbytes/sec] received

    Connection Times (ms)
              min  mean[+/-sd] median   max
    Connect:        0    3   4.7      0      15
    Processing:     0    9  13.7      3     203
    Waiting:        0    8  13.6      3     203
    Total:          0   12  17.4      5     211

    Percentage of the requests served within a certain time (ms)
    50%      5
    66%     10
    75%     32
    80%     34
    90%     37
    95%     39
    98%     40
    99%     40
    100%    211 (longest request)

### 目前bug 2017-8-29
    1,当并发量过大时,1000*1000的时候,服务器会出现段错误,为随机出现,gdb调试时在PthreadHandel函数
    2,线程池工作有问题
