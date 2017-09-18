#ifndef _HTTP_TASK_H_
#define _HTTP_TASK_H_

typedef struct HttpTask{
    void* next;
    void* pre;
    void* (*CallHandel)(void* arg);
    void* arg;

    int client;                   //客户端 socket
}HttpTask;

void* CreateHttpTask(int fd);

void* DealHttp(void* arg);

#endif
