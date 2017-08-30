#include <stdio.h>
#include "global.h"


int main()
{
    //初始化套接字
    server = InitSocket(8080);
    //初始化事件树
    eventTree = InitEventTree(300);
    //初始化请求数据队列
    requests = InitRequestQueue();
    //初始化线程池
    pthreadPool = CreatPthreadPool(10, 10);
    //线程池管理
    manage = CreataManage(ManageHandel,pthreadPool);
    for(int i=0; i<5; i++)
    {
        //创建监听事件
        EventNode* newNode = CreateEventNode(server->ServerFd, EPOLLIN, AcceptConnect);

        //添加监听事件
        AddEvent(eventTree, newNode);
    }


    //等待事件发生
    WaitEvent(eventTree);
    CloseSocket(server);
    return 0;
}
