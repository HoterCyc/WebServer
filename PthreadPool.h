#ifndef _PTHREAD_POOL_H_
#define _PTHREAD_POOL_H_
#include <pthread.h>
#include "linkTab.h"

typedef struct Pthread{
    void* next;
	void (*showWay)(void* x);
    pthread_t Pid;              //线程id
    unsigned int IsBusy;        //线程是否忙
    pthread_mutex_t LockPthread;//锁
}Pthread;

typedef struct PthreadPool{

    pthread_mutex_t LockPool;       //锁
    plinkTab Pool;            //线程池
    unsigned int ActiveNum;      //活动线程
    pthread_mutex_t LockActiveNum;  //活动线程锁
    unsigned int MaxPoolNum;    //默认最大线程
    unsigned Step;              //新增线程和销毁线程步进值
}PthreadPool;

/**
 * 创建线程池
 * @param  max  默认线程值
 * @param  step 步进
 * @return      线程池
 */
PthreadPool* CreatPthreadPool(unsigned int max, unsigned int step);

/**
 * 新增线程
 * @param pool 线程池
 */
void AddPthread(PthreadPool* pool, unsigned int n);


/**
 * 销毁线程
 * @param pool 线程池
 */
void DeletePthread(PthreadPool* pool, unsigned int m);

void ShowPthread(void* p);

void* PthreadHandel(void* arg);

int SearchByPid(void* aim, void* key);
int SearchNotBusy(void* aim, void* key);
#endif
