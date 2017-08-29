#include "Http.h"
#include <sys/fcntl.h>
#include <unistd.h>
#include "global.h"

#include <time.h>

void* HttpMain(void* arg)
{
    // sleep(1);
    // while(1);
    RequestNode* req = (RequestNode*)arg;
    // Response* res = (Response*)malloc(sizeof(Response));
    // // char ch;
    // int n = 0, m = 0;
    // while(1){
    //     while(req->buf[n++] != '/');
    //     m = 0;
    //     while(req->buf[n] != ' ')
    //     {
    //         res->Path[m++] = req->buf[n++];
    //     }
    //     res->Path[m] = '\0';
    //     break;
    //     // GET / HTTP/1.1
    //     // Host: 127.0.0.1:8089
    //     // User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:53.0) Gecko/20100101 Firefox/53.0
    //     // Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
    //     // Accept-Language: zh-CN,zh;q=0.8,en-US;q=0.5,en;q=0.3
    //     // Accept-Encoding: gzip, deflate
    //     // Connection: keep-alive
    //     // Upgrade-Insecure-Requests: 1
    //     // Cache-Control: max-age=0
    //
    //
    //     // HTTP/1.1 200 OK
    //     // Date: Mon, 28 Aug 2017 17:58:24 GMT
    //     // Server: Apache/2.4.27 (Debian)
    //     // Vary: Accept-Encoding
    //     // Content-Encoding: gzip
    //     // Content-Length: 802
    //     // Keep-Alive: timeout=5, max=98
    //     // Connection: Keep-Alive
    //     // Content-Type: text/html;charset=UTF-8
    //
    //
    // }
    // // printf("%s\n", req->buf);
    // // sprintf(res->Path, "%s", "index.html");
    // // strcpy(res->Path, "index.html");
    // sprintf(res->Date, "%ld", time(NULL));
    // sprintf(res->Status, "%s", "HTTP/1.1 200 OK");
    // sprintf(res->Server, "%s", "codelover Server");
    // // FILE* fd = fopen(res->Path, "rb");
    // // int sum = fread(res->Content, sizeof(res->Content), 1,fd);
    // // fclose(fd);
    // int fd = open("index.html", O_CREAT|O_RDWR, 0644);
    // int sum;
    // // read(int __fd, void *__buf, size_t __nbytes)
    // // while(1)
    // // {
    //     sum = read(fd, res->Content, sizeof(res->Content));
    //     // printf("%s\n", res->Content);
    // // }
    // close(fd);
    // // printf("%s\n", res->Path);
    // // n = 0;
    // // m = 0;
    // // while(res->Path[n++] != '.');
    // // printf("%s\n", &res->Path[n]);
    // // while(res->Path[n] != '\0')
    // //     res->ContentType[m++] = res->Path[n++];
    // // res->ContentType[m] = '\0';
    //
    // char* format = "%s\r\nDate: %s\r\nContent-Type: %s\r\nServer: %s\r\nContent-Length: %d\r\n\r\n%s";
    // char buf[102400];
    // // if(strcmp(res->ContentType, "jpg") == 0)
    // // {
    // //     sprintf(buf, format, res->Status,res->Date,"image/jpeg",res->Server,sum,"");
    // //     memcpy(&buf[strlen(buf)], res->Content, sizeof(res->Content));
    // // }else{
    //     sprintf(buf, format, res->Status,res->Date,"text/html",res->Server,strlen(res->Content),res->Content);
    // // }
    //
    // write(req->RquestInfo->fd, buf, strlen(buf));

    // printf("%s\n", res->Content);
    write(req->RquestInfo->fd, "server", sizeof("server"));
    return NULL;
}
