#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <deque> 
using namespace std;

/* 排序 */

//直接插入排序 --每次将一个待排序的记录按其关键字大小插入前面已经排好序的子序列
void InsertSort(vector<int> &A, int n)//n为数组中数据元素个数
{
    int i, j, temp;
    for(i = 1; i < n; i++)
    {
        if(A[i] < A[i-1]) { //若A[i]关键字小于前驱
            temp = A[i]; //暂存A[i]
            for(j = i - 1; j >= 0 && A[j] > temp; j--) {//检查前面已排好的元素
                A[j + 1] = A[j];//所有大于temp的元素向后移位
            }
            A[j + 1] = temp;//复制到插入位置
        }
    }
}

//折半插入排序(对直接插入排序的改进) --先用折半查找找到应该插入的位置，再移动元素
void InsertSort_mid(vector<int> &A, int n)
{
    int i, j, temp;
    int low, mid, high;
    for(i = 1; i < n; i++)
    {
        temp = A[i]; //暂存A[i]
        low = 0; high = i - 1; //设置折半查找的默认范围
        while(low <= high)//折半查找(默认递增有序)
        {
            mid = (low + high) / 2;
            if(A[mid] > temp) high = mid - 1;//查找左半子表
            else low = mid + 1;//查找右半子表
        }
        for(j = i - 1; j >= high + 1; j--) {
            A[j + 1] = A[j];//统一后移元素，空出插入位置
        }
        A[high + 1]  = temp;//插入操作
    }
}

//希尔排序 --先对表中部分元素分割成若干子表并对其直接插入排序，再对整体进行排序
void ShellSort(vector<int> &A, int n)
{
    int d, i, j, temp;
    for(d = n / 2; d >= 1; d = d / 2) {//歩长变化
        for(i = d + 1; i < n; i++) {
            if(A[i] < A[i - d]) { //需将A[i]插入有序增量子表
                temp = A[i]; //暂存A[i]
                for(j = i - d; j >= 0 && temp < A[j]; j -= d) {
                    A[j + d] = A[j];//记录后移，查找插入位置
                }
                A[j + d] = temp;
            }        
        }
    }
}

//两数交换
void swap(int &a, int &b) 
{
    int temp = a;
    a = b;
    b = temp;
}

//冒泡排序
void BubbleSort(vector<int> &A, int n)
{
    for(int i = 0; i < n; i++) {
        bool flag = false;//表示本趟冒泡是否发生交换的标志
        for(int j = n - 1; j > i; j--) {
            if(A[j] < A[j - 1]) {
                swap(A[j], A[j - 1]);
                flag = true;
            }
        }
        if(flag == false) return;//本趟遍历后没有发生交换，说明表已经有序
    }
}

//划分待排序序列
int Partition(vector<int> &A, int low, int high)
{
    int pivot = A[low];//用第一个元素作为枢轴
    while(low < high) {
        while(low < high && A[high] >= pivot) --high;
        A[low] = A[high];//将比枢轴小的元素移动到左端
        while(low < high && A[low] <= pivot) ++low;
        A[high] = A[low];//将比枢轴大的元素移动到右端
    }
    A[low] = pivot;//枢轴元素存放到最终位置
    return low;//返回存放枢轴的最终位置
}
//快速排序
void QuickSort(vector<int> &A, int low, int high)
{
    if(low < high) {//递归跳出的条件
        int pivotpos = Partition(A, low, high);//划分
        QuickSort(A, low, pivotpos -1);//对左子表进行递归排序
        QuickSort(A, pivotpos + 1, high);//对右字表进行递归排序
    }
}

//简单选择排序 --每一趟在待排序元素中选择关键字最小的元素加入有序子序列
void SelectSort(vector<int> &A, int n)
{
    int i, j;
    for(i = 0; i < n - 1; i++) {//一共进行n-1趟
        int min = i;//记录最小元素位置
        for(j = i + 1; j < n; j++) {//在A[i+1...n-1]中选择最小元素
            if(A[j] < A[min]) min = j;//更新最小元素位置
        }
        if(min != i) swap(A[i], A[min]);//把当前待排序元素中最小元素与其第一个元素交换
    }
}

//将以k为根的子树调整为大根堆
void HeadAdjust(vector<int> &A, int k, int len) 
{
    int temp = A[k]; //暂存根结点
    for(int i = 2 * k; i < len; i *= 2) { //从当前根的左孩子开始沿关键字较大的子结点向下筛选
        if(i < len && A[i] < A[i+1]) i++; //去关键字较大的子结点的下标
        if(temp >= A[i]) break;//筛选结束
        else {
            A[k] = A[i];//将A[i]调整到根结点位置
            k = i;//修改k值以便继续向下筛选
        }
    }
    A[k] = temp;//将被调整的结点放入最终位置
}

//建立大根堆
void BuildMaxHeap(vector<int> &A, int len) 
{
    for(int i = len / 2; i >= 0; i--) {//从后往前调整所有非终端结点
        HeadAdjust(A, i, len);
    }
}

//堆排序 --每一趟将堆顶元素加入有序子序列(与待排序序列中最后一个元素交换),并将待排序序列再次调整为大根堆
void HeapSort(vector<int> &A, int len)
{
    BuildMaxHeap(A, len);//初始建堆
    for(int i = len - 1; i > 0; i--)
    {
        swap(A[i], A[0]);//堆顶元素和堆底元素交换
        HeadAdjust(A, 0, i - 1);//把剩余待排序元素整理成堆
    }
}

//归并排序
vector<int> B(6);//辅助数组B
void Merge(vector<int> &A, int low, int mid, int high)//low-mid和mid-high各自有序
{
    int i, j, k;
    for(k = low; k <= high; k++) {
        B[k] = A[k];// 将A中所有元素复制到B中
    }
    for(i = low, j = mid + 1, k = i; i <= mid && j <= high; k++) {
        if(B[i] <= B[j]) {
            A[k] = B[i++];//将较小值复制到A中
        } else {
            A[k] = B[j++];
        }
    }
    while(i <= mid) A[k++] = B[i++];//没有归并完的部分复制到尾部
    while(j <= high) A[k++] = B[j++];
}

void MergeSort(vector<int> &A, int low, int high) 
{
    if(low < high) {
        int mid = (low + high) / 2;//从中间划分两个子序列
        MergeSort(A, low, mid);//对左侧子序列进行递归排序
        MergeSort(A, mid + 1, high);//对右侧子序列进行递归排序
        Merge(A, low, mid, high);//归并
    }
}

//打印数组
void Print_Arr(vector<int> A)
{
    for(auto i : A)
    {
        cout << i << " ";
    }
    cout << endl;
}

int main()
{
    vector<int> arr = {2, 4, 6, 1, 3, 5};
    cout << "Orign array:\t";
    Print_Arr(arr);

    /* InsertSort(arr, arr.size());
    cout << "InsertSort:\t";
    Print_Arr(arr);  */

    /* InsertSort_mid(arr, arr.size());
    cout << "InsertSort_mid:\t";
    Print_Arr(arr); */

    /* ShellSort(arr, arr.size());
    cout << "ShellSort:\t";
    Print_Arr(arr); */

    /* BubbleSort(arr, arr.size());
    cout << "BubbleSort:\t";
    Print_Arr(arr); */

    /* QuickSort(arr, 0, arr.size() - 1);
    cout << "QuickSort:\t";
    Print_Arr(arr); */

    /* SelectSort(arr, arr.size());
    cout << "SelectSort:\t";
    Print_Arr(arr); */

    /* HeapSort(arr, arr.size());
    cout << "HeapSort:\t";
    Print_Arr(arr); */

    MergeSort(arr, 0, arr.size() - 1);
    cout << "MergeSort:\t";
    Print_Arr(arr);

    system("pause");
    return 0;
}