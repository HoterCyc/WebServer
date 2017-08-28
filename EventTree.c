#include "EventTree.h"
#include <unistd.h>


EventTree* InitEventTree(unsigned int ActiveEventNum)
{
    EventTree* eventTree = (EventTree*)malloc(sizeof(EventTree));
    eventTree->Root = epoll_create(10);
    eventTree->ActiveEventNum = ActiveEventNum;
    eventTree->ActiveEvent = (struct epoll_event*)malloc(sizeof(struct epoll_event) * eventTree->ActiveEventNum);
    if(eventTree->ActiveEvent == NULL)
    {
        printf("malloc eventTree error:\n");
        exit(1);
    }
    return eventTree;
}

EventNode* CreateEventNode(int fd, int event, void* handel, void* arg)
{
    EventNode* newNode = malloc(sizeof(EventNode));
    if(newNode == NULL)
    {
        printf("malloc error\n");
        exit(1);
    }
    newNode->arg = arg;
    newNode->CallHandel = handel;
    newNode->event = event;
    newNode->fd = fd;
    return newNode;
}


void AddEvent(EventTree* eventTree, EventNode* newNode)
{
    struct epoll_event new;
    new.events = newNode->event;
    new.data.ptr = newNode;
    pthread_mutex_lock(&(eventTree->TreeLock));
    epoll_ctl(eventTree->Root, EPOLL_CTL_ADD, newNode->fd, &new);
    pthread_mutex_unlock(&eventTree->TreeLock);
}

void DeleteEvent(EventTree* eventTree, EventNode* deleteNode)
{

    pthread_mutex_lock(&(eventTree->TreeLock));
    close(deleteNode->fd);
    epoll_ctl(eventTree->Root, EPOLL_CTL_DEL, deleteNode->fd, NULL);
    pthread_mutex_unlock(&eventTree->TreeLock);
}

void WaitEvent(EventTree* eventTree)
{
    while(1)
    {
        int nready = epoll_wait(eventTree->Root, eventTree->ActiveEvent, eventTree->ActiveEventNum, -1);
        printf("活动事件%d\n", nready);
        for(int i=0; i<nready; i++)
        {
            EventNode* activeNode = (EventNode*)(eventTree->ActiveEvent[i].data.ptr);
            activeNode->CallHandel(activeNode->arg);

        }
        // nready = 0;
    }
}
