#include "HttpTask.h"
#include <unistd.h>
#include <malloc.h>
#include "global.h"
#include "Http.h"

void* CreateHttpTask(int fd)
{
    HttpTask* task = (HttpTask*)malloc(sizeof(HttpTask));
    task->arg = task;
    task->CallHandel = DealHttp;
    task->client = fd;
    return task;
}
/**
 * 处理http请求主入口
 * @param arg 参数
 */
void* DealHttp(void* arg)
{
    HttpTask* node = (HttpTask*)arg;
    char buf[1024];
    int n = read(node->client, buf, sizeof(buf));
    if(n == 0 || n < 0)
    {
        // DeleteEvent(eventTree, node);
    }else {
        buf[n] = '\0';
        // printf("%s\n", buf);
        // RequestNode* p =  CreatRequest(node, buf, HttpMain);
        // AddRequest(requests, p);
        // DeleteEvent(eventTree, node);
        // printf("%s\n", buf);
        // strcpy(buf, "HTTP/1.1 200 OK\r\nDate: Mon, 28 Aug 2017 17:58:24 GMT\r\nServer: Apache/2.4.27 (Debian)\r\nVary: Accept-Encoding\r\nContent-Length: 8\r\nKeep-Alive: timeout=5, max=98\r\n\r\n");
        // int fp = open("index.html",O_CREAT|O_RDWR);
        // read(fp, &buf[strlen(buf)], sizeof(buf));
        write(node->client, buf, strlen(buf));
    }
    return NULL;
}
