#include "ManagePthread.h"
#include "PthreadPool.h"
#include "global.h"
#include <malloc.h>
#include <unistd.h>

void* ManageHandel(void* arg)
{
    PthreadPool* pool = (PthreadPool*)arg;
    double active, sum;
    while(1)
    {

        pthread_mutex_lock(&(pool->LockActiveNum));
        active = pool->ActiveNum;
        pthread_mutex_unlock(&(pool->LockActiveNum));
        sum = pool->MaxPoolNum;
        if(DEBUG)
            printf("活动线程:%f总线程:%f\n", active,sum);
        if(active/sum >= 0.8)
        {
            AddPthread(pool,0);
        }else if(sum > 10){
            DeletePthread(pool,2);
        }
        sleep(1);
    }

    return NULL;

}

pthread_t* CreataManage(void* handel, void* arg)
{
    pthread_t* p = (pthread_t*)malloc(sizeof(pthread_t));
    pthread_create(p, NULL, handel, arg);
    return p;
}
