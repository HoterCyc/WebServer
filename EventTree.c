#include "EventTree.h"
#include "global.h"
#include <unistd.h>

/**
 * 初始化事件树
 * @param  ActiveEventNum 活动事件大小
 * @return                树根
 */
EventTree* InitEventTree(unsigned int ActiveEventNum)
{
    EventTree* eventTree = (EventTree*)malloc(sizeof(EventTree));
    if(eventTree == NULL)
    {
        printf("malloc eventTree error:\n");
        exit(1);
    }
    eventTree->Root = epoll_create(10);
    eventTree->ActiveEventNum = ActiveEventNum;
    eventTree->HasNum = 0;
    eventTree->ActiveEvent = (struct epoll_event*)malloc(sizeof(struct epoll_event) * eventTree->ActiveEventNum);
    if(eventTree->ActiveEvent == NULL)
    {
        printf("malloc eventTree error:\n");
        exit(1);
    }
    return eventTree;
}

/**
 * 创建新事件
 * @param  fd     文件描述符
 * @param  event  事件
 * @param  task 回调函数
 * @return        新节点地址
 */
EventNode* CreateEventNode(int fd, int event, void* task)
{
    EventNode* newNode = malloc(sizeof(EventNode));
    if(newNode == NULL)
    {
        printf("malloc error\n");
        exit(1);
    }
    newNode->task->arg = newNode;
    newNode->task = task;
    // newNode->arg = newNode;
    // newNode->CallHandel = handel;
    newNode->event = event;
    newNode->fd = fd;
    return newNode;
}

/**
 * 添加新节点
 * @param eventTree 事件树根
 * @param newNode   新节点
 */
void AddEvent(EventTree* eventTree, EventNode* newNode)
{
    struct epoll_event new;
    new.events = newNode->event;
    new.data.ptr = newNode;
    pthread_mutex_lock(&(eventTree->TreeLock));
    epoll_ctl(eventTree->Root, EPOLL_CTL_ADD, newNode->fd, &new);
    eventTree->HasNum++;
    pthread_mutex_unlock(&eventTree->TreeLock);
}

/**
 * 删除事件
 * @param eventTree 事件根节点
 * @param newNode   要删除的节点
 */
void DeleteEvent(EventTree* eventTree, EventNode* deleteNode)
{

    pthread_mutex_lock(&(eventTree->TreeLock));
    close(deleteNode->fd);
    epoll_ctl(eventTree->Root, EPOLL_CTL_DEL, deleteNode->fd, NULL);
    eventTree->HasNum--;
    pthread_mutex_unlock(&eventTree->TreeLock);
}

/**
 * 循环监听事件
 * @param eventTree 事件树
 */
void WaitEvent(EventTree* eventTree)
{
    while(1)
    {
        int nready = epoll_wait(eventTree->Root, eventTree->ActiveEvent, eventTree->ActiveEventNum, -1);
        if(DEBUG)
            printf("所有事件:%d,活动事件%d\n", eventTree->HasNum,nready);
        for(int i=0; i<nready; i++)
        {
            EventNode* activeNode = (EventNode*)(eventTree->ActiveEvent[i].data.ptr);
            // activeNode->CallHandel(activeNode->arg);
            AddTask(pthreadPool, activeNode);
        }
        // nready = 0;
    }
}
