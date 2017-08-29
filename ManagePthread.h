#ifndef _MANAGE_PTHREAD_H_
#define _MANAGE_PTHREAD_H_
#include <pthread.h>
/**
 * 线程管理函数入口
 * @param arg 参数
 */
void* ManageHandel(void* arg);

pthread_t* CreataManage(void* handel, void* arg);

#endif
