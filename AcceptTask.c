#include "AcceptTask.h"
#include <malloc.h>
AcceptTask* CreateAcceptTask(int fd, void* handel, void* arg)
{
    AcceptTask* newTask = (AcceptTask*)malloc(sizeof(AcceptTask));
    newTask->CallHandel = handel;
    newTask->arg = arg;
    newTask->serverFd = fd;
    return newTask;
}
