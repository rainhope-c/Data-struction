//深度优先遍历DFS(v)
#include "AdjGraph.cpp"
#include "MatGraph.cpp"
int visited[MAXV];
//邻接表的深度优先遍历算法
void DFSAdj(AdjGraph& G,int v)  //深度优先遍历（邻接表
{
    cout<<v<<" ";  //访问结点v
    visited[v]=1;  //标记已经访问
    ArcNode*p=G.adjlist[v].firstarc;  //p指向顶点v的第一个邻接点
    while(p!=NULL)
    {
        int w=p->adjvex;  //邻接点为w
        if(visited[w]==0) DFSAdj(G,w);  //如果w顶点还未访问，递归访问它
        p=p->nexctarc;  //置p为下一个邻接点
    }
}  //这个算法的时间复杂度是O(n+e)
void DFSMat(MatGraph& g,int v)  //深度优先遍历（邻接矩阵
{
    cout<<v<<" ";  //访问结点v
    visited[v]=1;  //标记已访问
    for(int w=0;w<g.n;w++)
    {
        if(g.edges[v][w]!=0 && g.edges[v][w]!=INF)
        {
            if(visited[w]==0)  //存在边<v,w>并且w没有访问过
                DFSMat(g,w);  //若w顶点未被访问，递归访问它
        }
    }
}  //这个算法的时间复杂度为O(n^2)
void DFSA(AdjGraph& G)  //非连通图的DFS
{
    for(int i=0;i<G.n;i++)
        if(visited[i]==0)  //如果顶点i还没有被访问过
            DFSAdj(G,i);
}
