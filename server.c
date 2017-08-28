#include <stdio.h>
#include "global.h"


int main()
{
    //初始化套接字
    server = InitSocket(8080);
    //初始化事件树
    eventTree = InitEventTree(100);
    //创建监听事件
    EventNode* newNode = CreateEventNode(server->ServerFd, EPOLLIN, AcceptConnect, NULL);
    newNode->arg = newNode;
    //添加监听事件
    AddEvent(eventTree, newNode);
    //等待事件发生
    WaitEvent(eventTree);
    CloseSocket(server);
    return 0;
}
