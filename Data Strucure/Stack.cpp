#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

#define MaxSize 50

//定义栈的顺序存储类型
typedef struct {
     char data[MaxSize];
     int top;
} SqStack;
//初始化栈
void InitStack(SqStack &stack)
{
    stack.top = -1;//初始化栈顶指针
}
//判断栈空
bool StackIsEmpty(SqStack stack)
{
    if(stack.top == -1)
    {
        return true;
    } else {
        return false;
    }
}
//进栈
bool Push(SqStack &stack, char e)
{
    if(stack.top == MaxSize - 1)
    {
        return false;
    }
    stack.data[++stack.top] = e;//指针先加一，再入栈
    return true;
}
//出栈
bool Pop(SqStack &stack, char &e)
{
    if(stack.top == -1)
    {
        return false;
    }
    e = stack.data[stack.top--];
    return true;
}
//读栈顶元素
bool GetTop(SqStack stack, char &e)
{
    if(stack.top == -1)
    {
        return false;
    }
    e = stack.data[stack.top];
    return true;
}

//------------------------
//括号匹配
bool bracketCheck(char str[], int len)
{
    SqStack stack;
    InitStack(stack);//初始化一个栈
    for(int i = 0; i < len; i++)
    {
        //扫描到左括号，入栈
        if(str[i] == '(' || str[i] == '[' || str[i] == '{')
        {
            Push(stack, str[i]);
            //cout << str[i] << endl;
        } else {
            //如果扫描到右括号，且当前栈空
            if(StackIsEmpty(stack))
            {
                return false;//匹配失败
            }

            char topElem;//栈顶元素
            Pop(stack, topElem);//栈顶元素出栈
            if(str[i] == ')' && topElem != '(')
            {
                return false;
            }
            if(str[i] == ']' && topElem != '[')
            {
                return false;
            } 
            if(str[i] == '}' && topElem != '{')
            {
                return false;
            }
        }   
    }
    return StackIsEmpty(stack);//检索完全部括号后，栈空说明匹配成功
}



int main()
{
    char buf[20] = "(())";
    cout << buf << endl;
    cout << "check answer:" << bracketCheck(buf, 4) << endl;

    system("pause");
    return 0;
}