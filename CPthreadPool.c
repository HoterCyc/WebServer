#include "CPthreadPool.h"
#include <malloc.h>
#include <unistd.h>
/**
 * 创建一个线程池
 * @return 线程池指针
 */
PthreadPool* CreatePthreadPool()
{


    PthreadPool* pool = (PthreadPool*)malloc(sizeof(PthreadPool));
    pthread_mutex_init(&pool->LockActive, NULL);
    pthread_mutex_init(&pool->LockDelete, NULL);
    pthread_mutex_init(&pool->LockPool, NULL);
    pthread_mutex_init(&pool->LockTask, NULL);
    pthread_cond_init(&pool->HasTask, NULL);
    pool->ActiveNum = 0;
    pool->DeleteNum = 0;
    pool->MaxActiveRate = 0.8;
    pool->MaxPthread = MAX_PTHREAD_NUM;
    pool->MinActiveRate = 0.2;
    pool->Step = 10;
    pool->Pool = CreatLinkTab();
    pool->TaskQueue = CreatQueue();
    AddPthread(pool, 4);
    //线程管理者
    Task* manage = (Task*)malloc(sizeof(Task));
    manage->CallHandel = ManageTaskHandel;
    manage->arg = pool;
    AddTask(pool, manage);

    return pool;
}

/**
 * 添加任务
 * @param  pool 线程池
 * @param  task 任务
 * @return      添加情况
 */
int AddTask(PthreadPool* pool, void* task)
{
    pthread_mutex_lock(&pool->LockTask);
    Push(pool->TaskQueue, task);
    pthread_mutex_unlock(&pool->LockTask);
    pthread_cond_signal(&pool->HasTask);//告诉线程池有新任务
    return 1;
}

/**
 * 设置最大线程数
 * @param  pool 线程池
 * @param  num  数量
 */
void SetMaxPthread(PthreadPool* pool, unsigned int num)
{
    pool->MaxPthread = num;
    // return 1;
}


/**
 * 设置活动线程率
 * @param  pool 线程池
 * @param  rate 比例
 */
void SetMaxActiveRate(PthreadPool* pool, double rate)
{
    pool->MaxActiveRate = rate < pool->MinActiveRate ? pool->MaxActiveRate : rate;
}


/**
 * 设置最小活动线程比率
 * @param  pool 线程池
 * @param  rate 比例
 */
void SetMinActiveRate(PthreadPool* pool, double rate)
{
    pool->MinActiveRate = rate > pool->MaxActiveRate ? pool->MinActiveRate : rate;
}


/**
 * 删除线程
 * @param  pool 线程池
 * 如果传入的线程数为所以线程数量,会保留线程管理线程
 */
void DeletePthread(PthreadPool* pool, unsigned int num)
{
    num = num > 0 ? num : pool->Step;

    pool->DeleteNum = num < GetSumPthread(pool) ? num : GetSumPthread(pool)-1;
    pthread_cond_broadcast(&pool->HasTask);
}


/**
 * 设置步进值
 * @param  PthreadPool 线程池
 * @param  step        步进
 */
void SetStep(PthreadPool* pool, unsigned int step)
{
    pool->Step = step > MAX_STEP ? MAX_STEP : step;
}

/**
 * 线程管理
 * @param arg 线程池
 */
void* ManageTaskHandel(void* arg)
{
    // Task* task = (Task*)arg;
    PthreadPool* pool = (PthreadPool*)arg;
    while(1)
    {
        // printf("manage---\n");
        if(GetSumPthread(pool) && ((double)pool->ActiveNum)/GetSumPthread(pool) > pool->MaxActiveRate)
            AddPthread(pool, 0);
        if(GetSumPthread(pool) && ((double)pool->ActiveNum)/GetSumPthread(pool) < pool->MinActiveRate)
            DeletePthread(pool, 0);
        usleep(700);
    }

    return NULL;
}


/**
 * 获取线程数量
 * @param  pool 线程池
 * @return      线程数量
 */
unsigned int GetSumPthread(PthreadPool* pool)
{
    return pool->Pool->sum;
}


/**
 * 添加线程
 * @param  pool 线程池
 * @param  num  添加数量
 * @return      添加成功数量
 */
int AddPthread(PthreadPool* pool, unsigned int num)
{
    num = num > 0 ? num : pool->Step;
    int i;
    for(i=0; i<num; i++)
    {
        if(GetSumPthread(pool) > pool->MaxPthread)
            break;
        Pthread* newP = (Pthread*)malloc(sizeof(Pthread));
        pthread_create(&newP->pid, NULL, Handel, pool);
        AddLinkTabNode(pool->Pool, newP);           //链表是线程安全的
        pthread_detach(newP->pid);
        printf("创建线程\n");
    }
    return i;
}

/**
 * 线程回调函数
 * @param arg 参数
 */
void* Handel(void* arg)
{
    PthreadPool* pool = (PthreadPool*)arg;
    Task* task = NULL;

    int NeedExit = 0;
    while(1)
    {
        NeedExit = 0;
        task = NULL;
        pthread_mutex_lock(&pool->LockPool);
        while(pool->TaskQueue->num == 0 && pool->DeleteNum == 0)
        {
            pthread_cond_wait(&pool->HasTask, &pool->LockPool);
        };
        pthread_mutex_unlock(&pool->LockPool);
        // printf("运行任务\n");
        //活跃线程数
        pthread_mutex_lock(&pool->LockActive);
        pool->ActiveNum++;
        pthread_mutex_unlock(&pool->LockActive);
        // if(IsEmpty(pool->TaskQueue) != 1)
        // {
        pthread_mutex_lock(&pool->LockTask);
        task = Pop(pool->TaskQueue);
        pthread_mutex_unlock(&pool->LockTask);

        // }
        if(task)
        {
            task->CallHandel(task->arg);
            // printf("运行任务\n");
        }
        //是否需要退出
        pthread_mutex_lock(&pool->LockDelete);
        if(pool->DeleteNum > 0)
        {
            NeedExit = 1;
            pool->DeleteNum--;
        }
        pthread_mutex_unlock(&pool->LockDelete);
        //活跃数-1
        pthread_mutex_lock(&pool->LockActive);
        pool->ActiveNum--;
        pthread_mutex_unlock(&pool->LockActive);
        // pthread_mutex_lock(&pool->LockPool);
        if(NeedExit == 1)
        {
            pthread_t pid = pthread_self();
            void* p = SearchlinkTabNode(pool->Pool, SearchPthreadCondition, (void*)pid);
            DeleteLinkTabNode(pool->Pool, p);
            printf("%ld退出\n", pthread_self());
            pthread_exit(NULL);
            // DeleteLinkTabNode(plinkTab linkTab, void *linkNode)
        }
        // pthread_mutex_unlock(&pool->LockPool);
    }
}
/**
 * 搜索线程池链表中的某个线程
 * @param  some 遍历的线程
 * @param  key  关键字,线程id
 * @return      查找情况
 */
int SearchPthreadCondition(void* some, void* key)
{
    Pthread* aim = (Pthread*)some;
    pthread_t pid = (pthread_t)key;
    return aim->pid == pid ? 1 : 0;

}
