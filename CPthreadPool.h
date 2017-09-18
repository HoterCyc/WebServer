#ifndef _PTHREADPOOL_H_
#define _PTHREADPOOL_H_
#include <pthread.h>
#include "linkTab.h"
#include "Queue.h"
#include "BaseTask.h"
// #include <>

#define MAX_PTHREAD_NUM 300
#define MAX_STEP 100
/**
 * 任务
 */


typedef struct Pthread{
    void* next;                         //链表需要使用
    pthread_t pid;                      //线程id

}Pthread;

/**
 * 线程池结构
 */
typedef struct PthreadPool{
    pthread_mutex_t LockPool;           //线程池锁
    pthread_cond_t HasTask;             //新任务通知

    unsigned int ActiveNum;             //活动线程数量
    pthread_mutex_t LockActive;         //活动数量锁

    unsigned int DeleteNum;             //将要删除的线程数
    pthread_mutex_t LockDelete;         //删除锁

    unsigned int Step;                  //步进值
    unsigned int MaxPthread;            //最大线程数

    double MaxActiveRate;               //最大活动率
    // pthread_mutex_t LockMaxActive;      //最大活动锁

    double MinActiveRate;               //最小活动率
    // pthread_mutex_t LockMinActive;      //最小活动锁

    plinkTab Pool;                      //所有线程
    Queue* TaskQueue;                   //任务队列
    pthread_mutex_t LockTask;           //任务锁

}PthreadPool;

/**
 * 创建一个线程池
 * @return 线程池指针
 */
PthreadPool* CreatePthreadPool();

/**
 * 添加任务
 * @param  pool 线程池
 * @param  task 任务
 * @return      添加情况
 */
int AddTask(PthreadPool* pool, void* task);

/**
 * 设置最大线程数
 * @param  pool 线程池
 * @param  num  数量
 * @return      设置情况
 */
void SetMaxPthread(PthreadPool* pool, unsigned int num);


/**
 * 设置活动线程率
 * @param  pool 线程池
 * @param  rate 比例
 * @return      设置情况
 */
void SetMaxActiveRate(PthreadPool* pool, double rate);


/**
 * 设置最小活动线程比率
 * @param  pool 线程池
 * @param  rate 比例
 * @return      设置情况
 */
void SetMinActiveRate(PthreadPool* pool, double rate);


/**
 * 删除线程
 * @param  pool 线程池
 */
void DeletePthread(PthreadPool* pool, unsigned int num);


/**
 * 设置步进值
 * @param  PthreadPool 线程池
 * @param  step        步进
 */
void SetStep(PthreadPool* pool, unsigned int step);

/**
 * 线程管理
 * @param arg 线程池
 */
void* ManageTaskHandel(void* arg);

/**
 * 获取线程数量
 * @param  pool 线程池
 * @return      线程数量
 */
unsigned int GetSumPthread(PthreadPool* pool);

/**
 * 线程回调函数
 * @param arg 参数
 */
void* Handel(void* arg);


/**
 * 添加线程
 * @param  pool 线程池
 * @param  num  添加数量
 * @return      添加成功数量
 */
int AddPthread(PthreadPool* pool, unsigned int num);







/**
 * 搜索线程池链表中的某个线程
 * @param  some 遍历的线程
 * @param  key  关键字,线程id
 * @return      查找情况
 */
int SearchPthreadCondition(void* some, void* key);
#endif
