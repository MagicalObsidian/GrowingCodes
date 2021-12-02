#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

#define MaxSize 10
typedef struct {
    int data[MaxSize];
    int front, rear;
}   SqQueue;

//初始化
void InitQueue(SqQueue &Q)
{
    Q.front = Q.rear = 0;
}
//判断队空
bool isEmpty(SqQueue Q)
{
    if(Q.rear == Q.front) {
        return true;
    } else {
        return false;
    }
}
//入队
bool EnQueue(SqQueue &Q, int e)
{
    if((Q.rear + 1) % MaxSize == Q.front)//队列已满
    {
        return false;
    }
    Q.data[Q.rear] = e;//新元素入队
    Q.rear = (Q.rear+1)  % MaxSize;//队尾指针加1
    return true;
}
//出队
bool DeQueue(SqQueue &Q, int &e)
{
    if(Q.rear == Q.front)//队空则报错
    {
        return false;
    }
    e = Q.data[Q.front];//队头元素出队
    Q.front = (Q.front+1) % MaxSize;//队头指针加1取模
    return true;
}
int main()
{

    system("pause");
    return 0;
}