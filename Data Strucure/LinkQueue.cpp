#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

typedef struct LinkNode{
    int data;
    struct LinkNode * next;
} LinkNode;
typedef struct {
    LinkNode * front, * rear;//队列的 队头和队尾指针
} LinkQueue;
//初始化
void InitQueue(LinkQueue &Q)
{
    Q.front = Q.rear = (LinkNode *)malloc(sizeof(LinkNode));
    Q.front->next = NULL;
}
//判断队空
bool isEmpty(LinkQueue Q)
{
    if(Q.front == Q.rear) return true;
    else return false;
}
//入队
void EnQueue(LinkQueue &Q, int e)
{
    LinkNode * s = (LinkNode *)malloc(sizeof(LinkNode));
    s->data = e;
    s->next = NULL;
    Q.rear->next = s;
    Q.rear = s;
}
//出队
bool DeQueue(LinkQueue &Q, int &e)
{
    if(Q.front == Q.rear) return false;//队空
    LinkNode *p = Q.front->next;
    e = p->data;
    Q.front->next = p->next;
    if(Q.rear == p)
    {
        Q.rear = Q.front;//若原队列中只有一个结点，删除后变空
    }
    free(p);
    return true;
}

int main()
{

    system("pause");
    return 0;
}