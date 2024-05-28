#include "AdjGraph.cpp"
#include <stack>
#include <cstring>
//拓扑排序
//拓扑排序的过程为：
//从有向图中选择一个没有前驱（入度为0)的顶点并输出它
//从图中删除这个顶点，并且删去从这个顶点出发的所有有向边
//重复前两步直到剩下的图中不再存在没有前驱的顶点为止

//这样我们就需要一个数组来存储订点的入度->设计一个ind数组->ind[v]实际存储的是顶点v的入度个数
//在执行拓扑排序时我们可以利用一个栈存放多个入度为0的订点，
//在出栈顶点i时，我们要把i输出同时删除这个顶点的所有出边->顶点i的所有出边的邻接点的入度减一
void TopSort(AdjGraph& G)  //拓扑排序
{
    stack<int> st;  //定义一个栈
    int ind[MAXV];  //存储每个顶点的入度
    memset(ind,0,sizeof(ind));  //初始化为0
    ArcNode* p;
    for(int i=0;i<G.n;i++)  //求所有顶点的入度
    {
        p=G.adjlist[i].firstarc;
        while(p!=NULL)  //处理顶点i的所有出边
        {
            int w=p->adjvex;   //存在有向边<i,w>
            ind[w]++;  //w的入度加一
            p=p->nexctarc;
        }

    }
    for(int i=0;i<G.n;i++)  //将所有入度为0的顶点进栈
        if(ind[i]==0)
            st.push(i);
    while(!st.empty())  //栈不为空时循环
    {
        int i=st.top();  st.pop();  //输出拓扑排序序列中的第一个顶点i
        printf("%d  ",i);

        p=G.adjlist[i].firstarc;  //找到顶点i的邻接点
        while(p!=NULL)
        {
            int w=p->adjvex;  //邻接点为w
            ind[w]--;  //顶点w的入度减一
            if(ind[w]==0)  //如果入度为0那就进栈
                st.push(w);
            p=p->nexctarc;  //找下一个邻接点
        }
    }
}//时间复杂度为O(n+e)
