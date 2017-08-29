

#ifndef _HTTP_H_
#define _HTTP_H_
#define MAX_NAME 128
#define MAX_METHOD 16
#define MAX_CONTENT 10240

// typedefl struct{
//     char Method
// }RequestInfo;
typedef struct {
    char Status[MAX_METHOD];
    char Path[MAX_NAME];
    char Date[MAX_NAME];
    char ContentType[MAX_NAME];
    char Server[MAX_NAME];
    char ContentLength[MAX_METHOD];
    char Content[MAX_CONTENT];
}Response;



// HTTP/1.1 200 OK
// Date: Mon, 28 Aug 2017 17:58:24 GMT
// Server: Apache/2.4.27 (Debian)
// Vary: Accept-Encoding
// Content-Encoding: gzip
// Content-Length: 802
// Keep-Alive: timeout=5, max=98
// Connection: Keep-Alive
// Content-Type: text/html;charset=UTF-8
void* HttpMain(void* arg);



#endif
