#include "AcceptTask.h"
#include <malloc.h>
#include "global.h"
#include <unistd.h>
#include "HttpTask.h"

/**
 * 创建一个接受请求的任务
 * @param  fd  请求任务的socket
 * @param  arg 回调函数参数
 * @return     任务地址
 */
AcceptTask* CreateAcceptTask(int fd)
{
    AcceptTask* newTask = (AcceptTask*)malloc(sizeof(AcceptTask));
    newTask->CallHandel = AcceptConnect;
    newTask->arg = newTask;
    newTask->serverFd = fd;
    return newTask;
}

/**
 * 回调处理函数
 * @param arg 参数
 */
void* AcceptConnect(void* arg)
{
    struct sockaddr_in client;
    AcceptTask* node = (AcceptTask*)arg;

    socklen_t len = sizeof(client);
    int con = accept(node->serverFd, (struct sockaddr*)&client, &len);
    HttpTask* task = CreateHttpTask(con);
    EventNode* newNode = CreateEventNode(con, EPOLLIN, task);

    AddEvent(eventTree, newNode);
    if(DEBUG)
        printf("客户端连接\n");
    return NULL;
}
