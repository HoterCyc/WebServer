
#ifndef _EVENT_TREE_H_
#define _EVENT_TREE_H_

#include <sys/epoll.h>
#include <pthread.h>
#include <malloc.h>
#include <stdlib.h>
#include "BaseTask.h"

typedef struct EventNode{
    void* next;
    void* pre;
    int fd;                            //socket
    int event;                         //事件
    Task* task;                        //任务
    // void (*CallHandel)(void* myself);  //回调函数
    // void* arg;                         //回调函数参数
}EventNode;

typedef struct EventTree{
    pthread_mutex_t TreeLock;           //树的锁
    int Root;                           //树根
    struct epoll_event* ActiveEvent;    //活动的事件
    unsigned int ActiveEventNum;        //活动事件数组大小
    unsigned int HasNum;                //当前的节点数
}EventTree;

/**
 * 初始化事件树
 * @param  ActiveEventNum 活动事件大小
 * @return                树根
 */
EventTree* InitEventTree(unsigned int ActiveEventNum);

/**
 * 创建新事件
 * @param  fd     文件描述符
 * @param  event  事件
 * @param  task   任务
 * @return        新节点地址
 */
EventNode* CreateEventNode(int fd, int event, void* task);


/**
 * 添加新节点
 * @param eventTree 事件树根
 * @param newNode   新节点
 */
void AddEvent(EventTree* eventTree, EventNode* newNode);


/**
 * 删除事件
 * @param eventTree 事件根节点
 * @param newNode   要删除的节点
 */
void DeleteEvent(EventTree* eventTree, EventNode* deleteNode);

/**
 * 循环监听事件
 * @param eventTree 事件树
 */
void WaitEvent(EventTree* eventTree);

#endif
