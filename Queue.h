
#ifndef _Queue_H_
#define _Queue_H_

#include <pthread.h>

typedef struct node
{
	struct node* next;
    struct node* pre;
} node;

typedef struct Queue{
    node* tail;             //队尾巴
    node* head;             //队头
    int num;                //总结点数
    pthread_mutex_t lock;   //锁
}Queue;


/**
 * 创建队列
 * @return 队列
 */
Queue* CreatQueue();

/**
 * 入队
 * @param  node 新节点
 */
void Push(Queue* queue, void* NewNode);


/**
 * 出队
 * 此处出队元素需要手动free
 */
void* Pop(Queue* queue);

/**
 * 判断是否为空
 * @return 1 为空 0 不为空
 */
int IsEmpty(Queue* queue);
#endif
