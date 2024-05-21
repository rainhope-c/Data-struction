//图遍历算法的应用
#include "BFS.cpp"
#include "DFS.cpp"
#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

int visited[MAXV];  //在每次调用访问的时候都需要把这个数组置为0
//判断图中顶点v和顶点u之间有没有路径
bool HasPath1(AdjGraph& G,int u,int v)
{
    visited[u]=1;
    ArcNode* p=G.adjlist[u].firstarc;  //p指向结点u的邻接结点
    while (p!=NULL)  //用p遍历结点u的邻接结点
    {
        int w=p->adjvex;  //w存储具体的值
        if(w==v)  //如果找到了
            return true;  //返回真
        else if(visited[w]=0)  //如果顶点w没有被访问
        {
            if(HasPath1(G,w,v));  //对顶点w进行递归访问
                return true;  //如果返回真，那么w能到v，则u->w->v
        }
        p=p->nexctarc;
        /* code */
    }
    return false;
}

//求顶点u到顶点v的一条简单路径
void FindPath11(AdjGraph& G,int u,int v,vector<int> path)
{
    visited[u]=1;
    path.push_back(u);
    if(u==v)  //如果找到路径了，直接输出并且返回
    {   for(int i=0;i<path.size();i++)
            cout<<path[i]<<" "; 
        cout <<endl;
        return ;
    }
    ArcNode* p=G.adjlist[u].firstarc;
    while(p!=NULL)
    {
        int w=p->adjvex;  //找到u的邻接点w
        if(visited[w]==0)
            FindPath11(G,w,v,path);
        p=p->nexctarc;
    }
}
void FindPath1(AdjGraph& G,int u,int v)
{
    memset(visited,0,sizeof(visited));  //置零
    vector<int>path;
    FindPath11(G,u,v,path);
}


//求顶点u到顶点v的最短路径
struct QNode
{
    int v;  //顶点编号
    int dis;  //原点到当前顶点的最短路径长度

    QNode() {}  //构造函数
    QNode(int v,int dis)  //重载构造函数
    {
        this->v=v;
        this->dis=dis;
    }
};
int Shortdist(AdjGraph& G,int u,int v)  //求u到v的最短路径
{
    int visited[MAXV];
    memset(visited,0,sizeof(visited));
    queue<QNode> qu;  //定义一个队列qu
    while(!qu.empty())  //队不空循环
    {
        QNode e=qu.front(); qu.pop();
        if(e.v==v)  //找到1顶点v
            return e.dis;  //返回最短路径
        ArcNode* p=G.adjlist[e.v].firstarc;
        while(p!=NULL)
        {
            int w=p->adjvex;  //找到u的邻接点w
            if(visited[w]==0)  //如果没有访问
            {
                visited[w]=1;  //置已经访问
                qu.push(QNode(w,e.dis+1));  //邻接点w入队
            }
            p=p->nexctarc;
        }
    }
    return INF;  //没有路径的情况
}
int Shortdist2(AdjGraph& G,int u,int v)  //算法2
{
    int visited[MAXV];
    memset(visited,0,sizeof(visited));
    queue<int> qu;  //定义一个队列qu
    int ans=0;  //存放最短路径的长度
    visited[u]=1;  //置已经访问结点
    qu.push(u);  //起始点u进队
    while(!qu.empty())
    {
        int n=qu.size();  //求队列qu中的元素个数n
        for(int i=0;i<n;i++)
        {
            u=qu.front();  qu.pop();  //出队一个顶点u
            if(u==v)
                return ans;
            ArcNode* p=G.adjlist[u].firstarc;
            while(p!=NULL)
            {
                int w=p->adjvex;//找到u的邻接点
                if(visited[w]==0)  //若还没访问
                {
                    visited[w]=1;
                    qu.push(w);
                }
                p=p->nexctarc;
            }
        }
        ans++;  //一层的顶点扩展后ans加一
    }
    return INF;
}