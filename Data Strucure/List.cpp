#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

#define InitSize 10
typedef struct {
    int* data;
    int MaxSize;
    int length;
} SeqList;

void InitList(SeqList &L) {
    L.data = (int *)malloc(InitSize * sizeof(int));
    L.MaxSize = InitSize;
    L.length = 0;
}

void IncreaseSize(SeqList &L, int len) {
    int *p = L.data;
    L.data = (int *)malloc((L.MaxSize + len) * sizeof(int));
    for(int i = 0; i < L.length; i++) {
        L.data[i] = p[i];
    }
    L.MaxSize = L.MaxSize + len;
    free(p);
}

bool Min_elem(SeqList &L, int &min)
{
    if(L.length == 0)
    {
        printf("Error!");
        return false;
    }
    min = L.data[0];
    int k = 0;
    for(int i = 1; i < L.length; i++)
    {
        if(L.data[i] < min)
        {
            min = L.data[i];
            k = i;
        }
    }
    L.data[k] = L.data[L.length - 1];
    L.length -= 1;
    return true;
}

void PrintList(SeqList L)
{
    for(int i = 0 ; i < L.length; i++)
    {
        cout << L.data[i] << " ";
        if(i == L.length - 1) cout << endl;
    }
}


int main()
{
    srand(int (time(NULL)));
    SeqList L;
    InitList(L);
    IncreaseSize(L, 5);
    for(int i = 0; i < L.MaxSize; i++)
    {
        L.data[i] = rand() % 9 + 1;
        L.length++;
    }
    PrintList(L);
    int min = 0;
    Min_elem(L, min);
    cout << min << endl;
    PrintList(L);

    system("pause");
    return 0;
}