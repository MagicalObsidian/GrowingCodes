#include <iostream>
#include <cstdlib>
#include <ctime>
#include <deque> 
using namespace std;

/* 二叉排序树 */

//二叉排序树结点
typedef struct BSTNode {
    int key;//关键字
    int level;//所在层数
    struct BSTNode *lchild, *rchild;
} BSTNode, *BSTree;

//在二叉排序树中查找值为key的结点(非递归)
BSTNode *BST_Search(BSTree T, int key)
{
    while(T != NULL && key != T->key) //若树空或等于根结点的值，则结束循环
    {
        if(key < T->key) T = T->lchild;//若小于，则在左子树上查找
        else T = T->rchild;//若大于，则在右子树上查找
    }
    return T;
}

//在二叉排序树中查找值为key的结点(递归)
BSTNode *BST_Search_Recur(BSTree T, int key)
{
    if(T == NULL) return NULL;//查找失败
    if(key == T->key) return T;//查找成功
    else if(key < T->key) return BST_Search_Recur(T->lchild, key);//在左子树中查找
    else return BST_Search_Recur(T->rchild, key);//在右子树中查找
}

//在二叉排序树中插入关键字为 k 的新结点(递归)
int BST_Insert(BSTree &T, int k)
{
    if(T == NULL)//原树为空，新插入的结点为根结点
    {
        T = (BSTree)malloc(sizeof(BSTNode));
        T->key = k;
        T->lchild = T->rchild = NULL;
        return 1;//插入成功，返回1
    }
    else if(k == T->key) return 0;//树中存在相同关键字的结点，插入失败
    else if(k < T->key) return BST_Insert(T->lchild, k);//插入到T的左子树
    else return BST_Insert(T->rchild, k);//插入到T的右子树
}

//在二叉排序树中插入关键字为 k 的新结点(非递归)
int BST_Insert_While(BSTree &T, int k)
{
    if(T == NULL)//原树为空，新插入的结点为根结点
    {
        T = (BSTree)malloc(sizeof(BSTNode));
        T->key = k;
        T->lchild = T->rchild = NULL;
        return 1;//插入成功，返回1
    }
    while(T != NULL)
    {
        if(k < T->key)//插入到左子树
        {
            if(T->lchild == NULL)//如果当前结点没有左孩子
            {
                T->lchild = (BSTree)malloc(sizeof(BSTNode));
                return 1;
            }
            T = T->lchild;//左孩子不为空，继续访问左子树
        } else {//插入到右子树
            if(T->rchild == NULL)//若果当前结点没有右孩子
            {
                T->rchild = (BSTree)malloc(sizeof(BSTNode));
                return 1;
            }
            T = T->rchild;//右孩子不为空，继续访问右子树
        }
    }
    return 0;//插入失败
}

//构造二叉排序树
void Create_BST(BSTree &T, int str[], int n)
{
    T = NULL;//初始时T为空树
    int i = 0;
    while(i < n)//依次将每个关键字插入到二叉排序树中
    {
        BST_Insert(T, str[i]);
        i++;
    }
}

//先序遍历打印二叉树
void Print_BST_PreOrder(BSTree T)
{
    if(T != NULL) 
    {
        cout << T->key << " ";
        Print_BST_PreOrder(T->lchild);
        Print_BST_PreOrder(T->rchild);
    }
}

//层次遍历打印二叉树
void Print_BST_LevelOrder(BSTree T)
{
    deque<BSTree> Q;
    BSTree p, pre;
    Q.push_back(T);//将根结点入队
    T->level = 0;//根结点层次为 0
    while(!Q.empty())//队列不空则循环
    {
        p = Q.front();
        if(p->level != 0 && p->level != pre->level)//不是根结点且当前队头结点层次大于上一个结点
        {
            cout << endl;//换行
            cout << p->key << " ";
        } else {
            cout << p->key << " ";//访问出队结点
        }
        pre = Q.front();
        Q.pop_front();//队头结点出队
        if(p->lchild != NULL)//左子树不为空，则左子树根结点入队
        {
            Q.push_back(p->lchild);
            p->lchild->level = p->level + 1;
        }
        if(p->rchild != NULL)//右子树不为空，则右子树根结点入队
        {
            Q.push_back(p->rchild);
            p->rchild->level = p->level + 1;
        }
    }
}



int main()
{
    BSTree t;
    int str[8] = {50,66,60,26,21,30,70,68};
    Create_BST(t, str, 8);
    Print_BST_PreOrder(t);
    cout << endl;
    Print_BST_LevelOrder(t);


    cout << endl;
    system("pause");
    return 0;
}