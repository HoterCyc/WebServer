#include "DealRequest.h"
#include "global.h"
#include <pthread.h>
#include <string.h>
/**
 * 初始化请求队列
 * @return 队列
 */
RequestQueue* InitRequestQueue()
{
    RequestQueue* queue = (RequestQueue*)malloc(sizeof(RequestQueue));
    if(queue == NULL)
    {
        printf("malloc error\n");
        exit(1);
    }
    queue->Requests = CreatQueue();
    pthread_mutex_init(&(queue->Lock), NULL);
    pthread_cond_init(&(queue->HasRequest), NULL);
    if(DEBUG)
        printf("初始化请求数据队列\n");
    return queue;
}

/**
 * 创建新的请求信息
 * @param  userInfo    event信息
 * @param  requestInfo 请求数据
 * @return             新请求节点
 */
RequestNode* CreatRequest(EventNode* userInfo, const char* requestInfo, void* handel)
{
    RequestNode* p = (RequestNode*)malloc(sizeof(RequestNode));
    if(p == NULL)
    {
        printf("malloc error%s\n", __func__);
        exit(1);
    }
    p->CallHandel = handel;
    p->myself = p;
    p->RquestInfo = userInfo;
    strcpy(p->buf, requestInfo);
    return p;
}

/**
 * 添加新增节点
 * @param queue   队列
 * @param newNode 新节点
 */
void AddRequest(RequestQueue* queue, RequestNode* newNode)
{
    pthread_mutex_lock(&(queue->Lock));
    Push(queue->Requests, newNode);
    pthread_mutex_unlock(&(queue->Lock));
    //通知消费者
    pthread_cond_broadcast(&(queue->HasRequest));
    // pthread_cond_signal(&(queue->HasRequest));
}


/**
 * 获取一个请求
 * @param  queue 队列
 * @return       请求节点
 */
RequestNode* GetOneRequest(RequestQueue* queue)
{
    RequestNode* p = (RequestNode*)Pop(queue->Requests);
    return p;
    // if(p){
    //     RequestNode tmp = *p;
    //     free(p);
    //     return tmp;
    // }

}
