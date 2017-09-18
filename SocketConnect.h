
#ifndef _SOCKET_CONNECT_H_
#define _SOCKET_CONNECT_H_

#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    int ServerFd;
    struct sockaddr_in ServerAddr;
}SocketConnect;


/**
 * 初始化服务器端socket
 * @param  port 端口
 * @return      server socket
 */
SocketConnect* InitSocket(uint16_t port);

/**
 * 关闭服务器端socket
 * @param server server socket
 */
void CloseSocket(SocketConnect* server);


// void AcceptConnect(void* arg);

// void* sendinfo(void* arg);

void DealHttp(void* arg);
#endif
