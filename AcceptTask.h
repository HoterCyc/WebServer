
#ifndef _ACCEPT_TASK_H_
#define _ACCEPT_TASK_H_
#include "BaseTask.h"

typedef struct AcceptTask{
    void* next;
    void* pre;
    void* (*CallHandel)(void* arg);
    void* arg;

    int serverFd;                   //服务端监听 socket
}AcceptTask;

void* Handel(void* arg);

AcceptTask* CreateAcceptTask(int fd, void* handel, void* arg);







#endif
