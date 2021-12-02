#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

typedef struct LNode {
    int data;
    struct LNode *next;
} LNode, *LinkList;

//带头结点 按位序插入
bool ListInsert(LinkList &L, int i, int e)
{
    if(i < 1)
    {
        return false;
    } 
    /* 如果不带头结点，要插入第一个结点需另做处理
    if(i == 1) {
        LNode *s = (LNode *)malloc(sizeof(LNode));
        s->data = e;
        s->next = L;
        L = s;
        return true;
    }
    */
    LNode *p;   //指针p指向当前扫描到的结点
    int j = 0;  //当前p指向的是第几个结点
    p = L;      //L指向头结点，头结点是第0个结点(不存数据)
    while(p != NULL && j < i - 1)   //循环找到第i-1个结点
    {
        p = p->next;
        j++;
    }
    if(p == NULL)   //i值不合法
    {
        return false;
    }
    LNode *s = (LNode *)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;    //将结点s连到p之后
    return true;    //插入成功
}
//带头结点 按位序删除
bool ListDelete(LinkList &L, int i, int &e)
{
    if(i < 1)
    {
        return false;
    }
    LNode *p;   //指针p指向当前扫描到的结点
    int j = 0;  //当前p指向的是第几个结点
    p = L;      //L指向头结点，头结点是第0个结点(不存数据)
    while (p != NULL && j < i - 1)  //循环找到第i-1个结点
    {
        p = p->next;
        j++;
    }
    if(p == NULL)   //i值不合法
    {
        return false;
    }
    if(p->next == NULL)     //第i-1个结点之后已无其他结点
    {
        return false;
    }
    LNode *q = p->next;     //令q指向被删除结点
    e = q->data;            //用e返回元素的值
    p->next = q->next;      //将*q结点从链中"断开"
    free(q);                //释放结点的存储空间
    return true;            //删除成功
}
//按位查找,返回第i个元素(带头结点)
LNode * GetElem(LinkList L, int i)
{
    if(i < 0)
    {
        return NULL;
    }
    LNode *p;
    int j = 0;
    p = L;
    while(p != NULL && j < i)
    {
        p = p->next;
        j++;
    }
    return p;
}
//按值查找,找到数据域==e的结点
LNode * LocateElem(LinkList L, int e)
{
    LNode *p = L->next;
    while(p != NULL && p->data != e)
    {
        p = p->next;
    }
    return p;
}


int main()
{

    system("pause");
    return 0;
}