#include <stdio.h>
#include "Queue.h"
// #include "linkTab.h"
#include <malloc.h>
typedef struct{
    void* next;
    void* pre;
    // void (*showWay)(void* x);
    int num;
}qq;

void show(void* arg){
    qq* q = (qq*)arg;
    printf("%d\n" ,q->num);
}

int condition(void* aim, void* key)
{
    qq* q = (qq*)aim;
    return q->num == 9 ? 1 : 0;
}

int main()
{
    Queue* q = CreatQueue();
    printf("%d\n", q->num);
    for(int i=0; i<10; i++)
    {
        qq* p = (qq*)malloc(sizeof(qq));
        p->num = i;
        Push(q, p);
    }
    for(int i=0; i<19; i++)
    {
        qq* x = Pop(q);
        if(x)
        printf("%d\n", x->num);
    }


    // plinkTab p = CreatLinkTab();
    // for(int i=0; i<10; i++){
    //     qq* q = (qq*)malloc(sizeof(qq));
    //     q->num = i;
    //     q->showWay = show;
    //     AddLinkTabNode(p, q);
    // }
    // qq* tmp = SearchlinkTabNode(p, condition, NULL);
    // printf("%d\n", tmp->num);
    // DeleteLinkTabNode(p, tmp);
    // ShowLinkTab(p);



    return 0;
}
