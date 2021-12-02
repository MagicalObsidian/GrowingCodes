#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <deque> 
using namespace std;

/* 查找 */

//顺序查找
typedef struct {
    int *elem;//元素存储空间基址
    int len;//表的长度
} SSTable;
//从数组0下标开始从头往后查找
int Search_Seq(SSTable ST, int key)
{
    int i;
    for(i = 0; i < ST.len && ST.elem[i] != key; i++);
    return i == ST.len ? -1 : i;//查找成功则返回元素下标,失败则返回-1
}
//"哨兵"
int Search_Seq_Sen(SSTable ST, int key)
{
    ST.elem[0] = key;//"哨兵",放在0号位置，表数据从1号位置开始存放
    int i;
    for(i = ST.len; ST.elem[i] != key; i--);//从后往前找
    return i;//查找成功则返回元素下标,失败则返回0
}

//折半查找
int Binary_Search(SSTable ST, int key)
{
    int mid, low = 0, high = ST.len - 1;
    while(low <= high) 
    {
        mid = (low + high) / 2;
        if(ST.elem[mid] == key){
            return mid;//查找成功则返回所在位置
        }
        else if(ST.elem[mid] > key){
            high = mid - 1;//从前半部分继续查找 
        }
        else low = mid + 1;//从后半部分继续查找
    } 
    return -1;//查找失败返回-1
}

//分块查找 --块内无序，块间有序
//索引表
typedef struct {
    int maxvalue;//最大关键字
    int low, high;//分块的存储区间
} Index;

int main()
{
    int arr[7] = {1,3,5,6,7,8,11}; 
    SSTable t;
    t.elem = arr;
    t.len = 7;
    for(int i = 0; i < 7; i++) {
        cout << t.elem[i] << " ";
        if(i == 6) cout << endl;
    }
    cout << "searching 11 ..." << endl;
    if(Binary_Search(t, 11) == -1){
        cout << "false!" << endl;
    } else {
        cout << "success! index:" << Binary_Search(t, 11) << endl;
    }
    system("pause");
    return 0;
}