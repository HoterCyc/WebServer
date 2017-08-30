#include "PthreadPool.h"
#include <malloc.h>
#include <unistd.h>
#include "global.h"
/**
 * 创建线程池
 * @param  max  默认线程值
 * @param  step 步进
 * @return      线程池
 */
PthreadPool* CreatPthreadPool(unsigned int max, unsigned int step)
{
    PthreadPool* pool = (PthreadPool*)malloc(sizeof(PthreadPool));
    if(pool == NULL)
    {
        printf("malloc error:%s\n", __func__);
        exit(1);
    }
    pthread_mutex_init(&(pool->LockActiveNum),NULL);
    pthread_mutex_init(&(pool->LockPool), NULL);
    pool->MaxPoolNum = max;
    pool->Step = step;
    pool->ActiveNum = 0;
    pool->Pool = CreatLinkTab();
    for(int i=0; i<max; i++)
    {
        Pthread* p = (Pthread*)malloc(sizeof(Pthread));
        if(p == NULL)
        {
            printf("malloc error%s\n", __func__);
            exit(1);
        }
        p->IsBusy = 0;
        pthread_mutex_init(&(p->LockPthread),NULL);
        p->showWay = ShowPthread;
        AddLinkTabNode(pool->Pool, p);
        pthread_create(&(p->Pid), NULL, PthreadHandel, NULL);
        pthread_detach(p->Pid);
    }
    return pool;
}


void* PthreadHandel(void* arg)
{
    if(DEBUG)
        printf("线程创建\n");

    while(1)
    {
        pthread_mutex_lock(&(requests->Lock));
        while(requests->Requests->num == 0)
        {
            pthread_cond_wait(&(requests->HasRequest), &(requests->Lock));
        }

        if(DEBUG)
            printf("消费者消费\n");
        RequestNode* p = GetOneRequest(requests);
        if(p == NULL)
            continue;
        pthread_mutex_unlock(&(requests->Lock));

        pthread_mutex_lock(&(pthreadPool->LockActiveNum));
        pthreadPool->ActiveNum++;
        pthread_mutex_unlock(&(pthreadPool->LockActiveNum));

        //线程池中查找对应的线程
        pthread_t* pid = (pthread_t*)malloc(sizeof(pthread_t));
        if(pid == NULL)
        {
            printf("malloc error%s\n", __func__);
            exit(1);
        }
        *pid = pthread_self();
        Pthread* tmp = SearchlinkTabNode(pthreadPool->Pool, SearchByPid, (void*)pid);
        free(pid);
        // if(tmp)
            tmp->IsBusy = 1;
        p->CallHandel(p->myself);
        free(p);
        // if(tmp)
            tmp->IsBusy = 0;

        pthread_mutex_lock(&(pthreadPool->LockActiveNum));
        pthreadPool->ActiveNum--;
        pthread_mutex_unlock(&(pthreadPool->LockActiveNum));
        // DeleteEvent(eventTree, p->RquestInfo);
        // usleep(50);
    }
    return NULL;
}

void ShowPthread(void* p)
{
    printf("线程信息显示\n");
}

/**
 * 新增线程
 * @param pool 线程池
 */
void AddPthread(PthreadPool* pool, unsigned int n)
{
    unsigned int step = pool->Step;
    step = (n == 0 ? step : n);
    pthread_mutex_lock(&(pool->LockPool));
    for(int i=0; i<step; i++,pool->MaxPoolNum++)
    {
        Pthread* p = (Pthread*)malloc(sizeof(Pthread));
        if(p == NULL)
        {
            printf("malloc error:%s\n", __func__);
            exit(1);
        }
        p->IsBusy = 0;
        pthread_mutex_init(&(p->LockPthread),NULL);
        p->showWay = ShowPthread;
        AddLinkTabNode(pool->Pool, p);
        pthread_create(&(p->Pid), NULL, PthreadHandel, NULL);
        pthread_detach(p->Pid);
        if(DEBUG)
            printf("新增线程\n");

    }
    pthread_mutex_unlock(&(pool->LockPool));
}


/**
 * 销毁线程
 * @param pool 线程池
 */
void DeletePthread(PthreadPool* pool, unsigned int m)
{
    pthread_mutex_lock(&(pool->LockPool));
    unsigned int step = pool->Step;
    step = (m == 0 ? step : m);
    int n = 0;
    for(; n!=step; )
    {
        Pthread* p = (Pthread*)SearchlinkTabNode(pool->Pool, SearchNotBusy, NULL);
        if(p != NULL)
        {
            // pthread_mutex_lock(&(p->LockPthread));

            pthread_cancel(p->Pid);
            pthread_mutex_destroy(&(p->LockPthread));
            DeleteLinkTabNode(pool->Pool, p);
            pool->MaxPoolNum--;
            n++;
            if(DEBUG)
                printf("删除线程%ld,%d\n",p->Pid,p->IsBusy);

        }
        usleep(500);
    }
    pthread_mutex_unlock(&(pool->LockPool));
}

int SearchNotBusy(void* aim, void* key)
{
    return ((Pthread*)aim)->IsBusy == 1 ? 0 : 1;
}

int SearchByPid(void* aim, void* key)
{
    pthread_t tmp = *((pthread_t*)key);
    Pthread* p = (Pthread*)aim;
    return (p->Pid == tmp ? 1 : 0);
}
