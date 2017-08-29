#include "SocketConnect.h"
#include "EventTree.h"
#include "global.h"
#include "Http.h"
#include <unistd.h>
#include <sys/fcntl.h>
/**
 * 初始化服务器端socket
 * @param  port 端口
 * @return      server socket
 */
SocketConnect* InitSocket(uint16_t port)
{
    SocketConnect* server = (SocketConnect*)malloc(sizeof(SocketConnect));
    if(server == NULL)
    {
        printf("malloc error:%s\n", __func__);
        exit(1);
    }
    server->ServerFd = socket(AF_INET, SOCK_STREAM, 0);
    if(server->ServerFd < -1)
    {
        printf("socket error%s\n", strerror(server->ServerFd));
        exit(1);
    }
    server->ServerAddr.sin_family = AF_INET;
    server->ServerAddr.sin_port = htons(port);
    server->ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    int n = bind(server->ServerFd, (struct sockaddr *)&(server->ServerAddr), sizeof(server->ServerAddr));
    if(n < 0)
    {
        printf("bind error%s\n" ,strerror(n));
        exit(1);
    }
    listen(server->ServerFd, 10);
    return server;
}

/**
 * 关闭服务器端socket
 * @param server server socket
 */
void CloseSocket(SocketConnect* server)
{
    shutdown(server->ServerFd, SHUT_WR);
    free(server);
}


void AcceptConnect(void* arg)
{
    struct sockaddr_in client;
    EventNode* node = (EventNode*)arg;

    socklen_t len = sizeof(client);
    int con = accept(node->fd, (struct sockaddr*)&client, &len);

    EventNode* newNode = CreateEventNode(con, EPOLLIN, DealHttp);

    AddEvent(eventTree, newNode);
    if(DEBUG)
        printf("客户端连接\n");
}
void DealHttp(void* arg)
{
    EventNode* node = (EventNode*)arg;
    char buf[1024];
    int n = read(node->fd, buf, sizeof(buf));
    if(n == 0 || n < 0)
    {
        DeleteEvent(eventTree, node);
    }else {
        buf[n] = '\0';
        // printf("%s\n", buf);
        RequestNode* p =  CreatRequest(node, buf, HttpMain);
        AddRequest(requests, p);
        // DeleteEvent(eventTree, node);
        // printf("%s\n", buf);
        // strcpy(buf, "HTTP/1.1 200 OK\r\nDate: Mon, 28 Aug 2017 17:58:24 GMT\r\nServer: Apache/2.4.27 (Debian)\r\nVary: Accept-Encoding\r\nContent-Length: 8\r\nKeep-Alive: timeout=5, max=98\r\n\r\n");
        // int fp = open("index.html",O_CREAT|O_RDWR);
        // read(fp, &buf[strlen(buf)], sizeof(buf));
        // write(node->fd, buf, strlen(buf));
    }
}
// void* sendinfo(void* arg)
// {
//     RequestNode* p = (RequestNode*)arg;
//
//     return NULL;
//     write(p->RquestInfo->fd, "server", sizeof("server"));
//     while(1);
//     // sleep(2);
//     // int n = 0;
//     // while(n++<100000000)while(n++<100000000);
//     return NULL;
// }
