//广度优先遍历
#include "AdjGraph.cpp"
#include "MatGraph.cpp"
#include <queue>

int visited[MAXV]={0};
//邻接表的广度优先遍历
void BFSAdj(AdjGraph& G,int v)  //广度优先遍历(邻接表)
{
    queue<int>qu;  //广度优先遍历需要借助队列
    cout<<v<<" ";  //访问当前结点
    visited[v]=1;  //标记当前结点已经访问
    qu.push(v);  //把顶点入队
    while(!qu.empty())  //队不空时循环
    {
        int u=qu.front();  qu.pop();  //出队顶点u
        ArcNode* p=G.adjlist[u].firstarc;  //找到顶点u的第一个邻接点
        while(p!=NULL)
        {
            if(visited[p->adjvex]==0)  //如果u的邻接点还未访问
            {
                cout<<p->adjvex<<" ";  //访问邻接点
                visited[p->adjvex]=1;  //标记已经访问结点
                qu.push(p->adjvex);  //邻接点入队
            }
            p=p->nexctarc;  //找到下一个邻接点
        }
    }
}  //这个算法的时间复杂度为O(n+e)

int BFSMat(MatGraph& g,int v)  //广度优先遍历(邻接矩阵)
{
    queue<int>qu;  //定义一个数组
    cout<<v<<" ";  //访问当前结点
    visited[v]=1;  //标记当前结点已被访问
    qu.push(v);  //顶点v进队
    while(!qu.empty())  //队列不空时循环
    {
        int u =qu.front();  qu.pop();  //出队顶点u
        for(int i=0;i<g.n;i++)
            if(g.edges[u][i]!=0&&g.edges[u][i]!=INF)
            {
                if(visited[i]==0)  //存在边<u,i>并且还未被访问
                {
                    cout<<i<<" "; //访问邻接点i
                    visited[i]=1;  //标记邻接点已经被访问
                    qu.push(i);  //邻接表i入队
                }
            }
    }
}  //这个算法的时间复杂度是O(n^2)
void BFSA(AdjGraph& G)  //非连通图的BFS
{
    for(int i=0;i<G.n;i++)
        if(visited[i]==0)
            BFSAdj(G,i);
}