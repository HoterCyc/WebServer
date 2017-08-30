#include "Queue.h"
#include <malloc.h>
#include <stdlib.h>
/**
 * 创建队列
 * @return 队列
 */
Queue* CreatQueue()
{
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if(queue == NULL)
    {
        printf("malloc error:%s\n",__func__);
        exit(1);
    }
    queue->head = NULL;
    queue->tail = NULL;
    queue->num = 0;
    pthread_mutex_init(&(queue->lock), NULL);
    // printf("初始化队列\n");
    return queue;
}

/**
 * 入队
 * @param  node 新节点
 * @return      添加情况
 */
void Push(Queue* queue, void* NewNode)
{

    node* p = (node*)NewNode;
    pthread_mutex_lock(&(queue->lock));

    if(IsEmpty(queue) == 1)
    {
        // printf("队列添加\n");
        p->next = NULL;
        p->pre = NULL;
        queue->head = p;
        queue->tail = p;
        queue->num++;
    }else{
        p->pre = NULL;
        p->next = queue->head;
        queue->head->pre = p;
        queue->head = p;
        queue->num++;
    }
    pthread_mutex_unlock(&(queue->lock));
}


/**
 * 出队
 */
void* Pop(Queue* queue)
{
    node* p=NULL;
    pthread_mutex_lock(&(queue->lock));
    if(IsEmpty(queue) == 0)
    {
        p = queue->tail;
        queue->tail = queue->tail->pre;
        queue->num--;
    }
    pthread_mutex_unlock(&(queue->lock));
    return (void*)p;
}

/**
 * 判断是否为空
 * @return 1 为空 0 不为空
 */
int IsEmpty(Queue* queue)
{
    return queue->num == 0 ? 1 : 0;
}
