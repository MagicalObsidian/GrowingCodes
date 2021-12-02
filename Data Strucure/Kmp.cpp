#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

/* KMP算法 */

#define MAXLEN 255
typedef struct {
    char ch[MAXLEN];
    int length;
} SString;
//赋值
void StrAssign(SString &ss, string T)
{
    for(int i = 0; i <= T.length(); i++)
    {
        ss.ch[i+1] = T[i];
    }
    ss.ch[0] = T.length();
    ss.length = T.length();
}
//求串长
int StrLength(string S)
{
    return S.length();
}
//求子串
string SubString(string S, int pos, int len)
{
    string sub = "";
    for(int i = pos; i <= len; i++) 
    {
        sub.push_back(S[i]);
    }
    return sub;
}
//比较字符串
int StrCompare(string S, string T)
{
    if(S > T) return 1;
    else if(S < T) return -1;
    return 0;
}

//-----------------------------------------
//简单模式匹配
int Index(SString S, SString T)
{
    int i = 1, j = 1;
    while(i <= S.length && j <= T.length)
    {
        if(S.ch[i] == T.ch[j])
        {
            ++i, ++j;//继续向后比较字符
        } else {
            i = i - j + 2;
            j = 1;
        }
    }
    if(j > T.length) return i - T.length;
    else return 0;
}
//--------------------------------------------------
//求next数组
void get_next(SString T, int next[])
{
    int i = 1, j = 0;
    next[1] = 0;
    while(i < T.length)
    {
        if(j == 0 || T.ch[i] == T.ch[j])
        {   
            ++i, ++j;
            next[i] = j;
        } else {
            j = next[j];
        }
    }
}
//KMP算法的进一步优化-------求nextval数组
void get_nextval(SString T, int nextval[])
{
    int i = 1, j = 0;
    nextval[1] = 0;
    while(i < T.length)
    {
        if(j == 0 || T.ch[i] == T.ch[j])
        {
            ++i, ++j;
            if(T.ch[i] != T.ch[j]) nextval[i] = j;
            else nextval[i] = nextval[j];
        } 
        else j = nextval[j];
    } 
}
//KMP算法
int Index_KMP(SString S, SString T, int next[])
{
    int i = 1, j = 1;
    while(i <= S.length && j <= T.length)
    {
        if(j == 0 || S.ch[i] == T.ch[j])
        { 
            ++i, ++j;
        } else {
            j = next[j];
        }
    }
    if(j > T.length) return i - T.length;
    else return 0;
}
int main()
{
    SString s, t;
    StrAssign(s, "chengchen");
    StrAssign(t, "gc");
    int next[t.length];
    get_next(t, next);
    cout << "index = "<< Index(s, t) << endl;
    cout << "kmpindex = " << Index_KMP(s, t, next) << endl;

    system("pause");
    return 0;
}