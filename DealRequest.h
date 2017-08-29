#ifndef _DEAL_HTTP_H_
#define _DEAL_HTTP_H_
#include "EventTree.h"
// #include "global.h"
#include "Queue.h"

#define MAX_BUF 1024
typedef struct RequestNode{
    void* next;
    void* pre;
    void* myself;
    void (*CallHandel)(void* myself);   //回调函数,处理请求函数
    EventNode* RquestInfo;
    char buf[MAX_BUF];                  //请求数据
}RequestNode;

typedef struct RequestQueue{
    Queue* Requests;            //请求队列
    pthread_mutex_t Lock;       //请求队列锁
    pthread_cond_t HasRequest;  //有新请求需要处理时通知线程池
}RequestQueue;

/**
 * 初始化请求队列
 * @return 队列
 */
RequestQueue* InitRequestQueue();

/**
 * 创建新的请求信息
 * @param  userInfo    event信息
 * @param  requestInfo 请求数据
 * @return             新请求节点
 */
RequestNode* CreatRequest(EventNode* userInfo, const char* requestInfo, void* handel);

/**
 * 添加新增节点
 * @param queue   队列
 * @param newNode 新节点
 */
void AddRequest(RequestQueue* queue, RequestNode* newNode);

/**
 * 获取一个请求
 * @param  queue 队列
 * @return       请求节点
 */
RequestNode* GetOneRequest(RequestQueue* queue);


#endif
