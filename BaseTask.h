#ifndef _BASE_TASK_H_
#define _BASE_TASK_H_


typedef struct Task{
    void* next;
    void* pre;
    // RunHandel
    void* (*CallHandel)(void* arg);
    void* arg;
}Task;


#endif
