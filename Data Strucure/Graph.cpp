#include <iostream>
#include <cstdlib>
#include <ctime>
#include <deque> 
using namespace std;

/* 图 */

// 邻接矩阵
#define MaxVertexNum 100 //图中顶点数目的最大值
typedef struct {
    char Vex[MaxVertexNum]; //顶点表
    int Edge[MaxVertexNum][MaxVertexNum]; //邻接矩阵 边表
    int vexnum, arcnum; //图的当前顶点数和边数/弧数
} MGraph;

//邻接表

typedef struct ArcNode { //边表结点
    int adjvex;//边/弧指向的结点
    struct ArcNode *next;//指向下一条弧的指针
    //InfoType info;//网的边权值
} ArcNode;

typedef struct VNode { //顶点表结点
    char data;//顶点信息
    ArcNode *first;//第一条边/弧
}VNode, AdjList[MaxVertexNum];

typedef struct { //邻接表
    AdjList vertices; //邻接表
    int vexnum, arcnum;//图的顶点数和弧数
} ALGraph;

bool visited[MaxVertexNum]; //访问标记数组
void visit(int v)
{
    cout << v << " " << endl;
}
int FirstNeighbor(MGraph G, int v);
int NextNeighbor(MGraph G, int v);
void BFS(MGraph G, int v);
void DFS(MGraph G,int v);

//广度优先遍历
void BFSTraverse(MGraph G)
{
    for(int i = 0; i < G.vexnum; i++) {
        visited[i] = false;//访问标记数组初始化
    }
    deque<int> Q;//初始化辅助队列
    for(int j = 0; j < G.vexnum; j++) {//从 0 号顶点开始遍历
        if(!visited[j]){//对每个联通分量调用一次BFS
            BFS(G, j);
        }
    }
}
void BFS(MGraph G, int v)
{
    visit(v);//访问初始结点v
    visited[v] = true; //对 v 做已访问标记
    
    deque<int> Q;//辅助队列
    Q.push_back(v);//顶点 v 入队
    while(!Q.empty())
    {
        Q.pop_front();//顶点v出队
        for(int w = FirstNeighbor(G,v); w >= 0; w = NextNeighbor(G, v))
        {
            //检测 v 的所有邻接顶点
            if(!visited[w]) { //w 为 v 的尚未访问的邻接顶点
                visit(w);//访问顶点 w
                visited[w] = true;//对 w 做已访问标记
                Q.push_back(w);//顶点 w 入队
            }//if
        }//for
    }//while 
}

//深度优先遍历
void DFSTraverse(MGraph G)
{
    for(int i = 0; i < G.vexnum; i++) {
        visited[i] = false;
    }
    for(int v = 0; v < G.vexnum; v++) {
        if(!visited[v]) {
            DFS(G, v);
        }
    }
}
void DFS(MGraph G, int v)
{
    visit(v);//访问初始结点v
    visited[v] = true; //对 v 做已访问标记
    for(int w = FirstNeighbor(G,v); w >= 0; w = NextNeighbor(G, v))
    {
        if(!visited[w]) {
            DFS(G, w);
        }
    }
}

//Floyd算法核心代码
void Floyd(int n)
{
    int A[MaxVertexNum][MaxVertexNum];
    int path[MaxVertexNum][MaxVertexNum];
    for(int k = 0; k < MaxVertexNum; k++){//考虑以 vk 作为中转点
        for(int i = 0; i < MaxVertexNum; i++){  //遍历整个矩阵
            for(int j = 0; j < MaxVertexNum; j++){
                if(A[i][j] > A[i][k] + A[k][j]) { //以 vk 为中转点的路径更短
                    A[i][k] = A[i][k] + A[k][j]; //更新最短路径长度
                    path[i][j] = k; //中转点
                }
            }
        }
    }
}

//拓扑排序
