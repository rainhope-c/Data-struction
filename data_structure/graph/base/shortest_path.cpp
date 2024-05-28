#include "MatGraph.cpp"
#include "AdjGraph.cpp"
#include <stdio.h>

//最短路径问题    
//图上一个点到另一个点路径上所有权值的和的定义是该路径的路径长度
//路径长度最短的那条路径称为最短路径

//Dijkstra算法
//思路是找到当前这个顶点到其余任一顶点最短的那条路径并把这个路径的终点作为新的顶点

//需要四个数组——S存储已经连接的路径 U存储还没连接的路径 dist[]存储U中各点到达起点的最短路径 path[]表示各点经过路径的起点
void Dijkstra(MatGraph& g,int v)
{
    int dist[MAXV];  //建立dist数组
    int path[MAXV];  //建立path数组
    int S[MAXV];  //建立S数组
    for(int i=0;i<g.n;i++)
    {
        dist[i]=g.edges[v][i];  //初始化dist[]数组
        S[i]=0;  //S[]初始置空
        if(g.edges[v][i]!=0 && g.edges[v][i]<INF)  //如果有边
            path[i]=v;  //设置前驱结点
        else
            path[i]=-1;  //没有路径就设置为-1
    }
    S[v]=1;  //设置顶点v在S中
    int minidis,u=-1;
    for(int i=0;i<g.n-1;i++)  //循环向S中添加n-1个顶点
    {
        minidis=INF;  //minidis置最小距离初值
        for(int j=0;j<g.n;j++)  //选取不在S中具有最小距离的顶点u
        {
            if(S[j]==0 && dist[j]<minidis)  
            {
                u=j;
                minidis=dist[j];
            }
        }
        S[u]=1;  //顶点u加入S中
        for(int j=0;j<g.n;j++)
        {
            if(S[j]==0) // 修改不在s中的顶点的距离
            {
                if(g.edges[u][j]<INF && dist[u]+g.edges[u][j]<dist[j])
                {
                    dist[j]==dist[u]+g.edges[u][j];
                    path[j]=u;
                }
            } 
        }
    }
    DispAllPath(dist,path,S,v,g.n);
}
void DispAllPath(int dist[],int path[],int S[],int v,int n)  //输出从顶点v出发的全部最短路径
{
    for(int i=0;i<n;i++)  //循环输出从顶点v到i的路径
    {
        if(S[i]==1 && i!=v)
        {
            vector<int>apath;  // 存放一条最短逆路线
            printf("  从%d到%d最短路径长度为： %d\t路径： ",v,i,dist[i]);
            apath.push_back(i);  //添加终点i
            int pre=path[i];
            while (pre!=v)
            {
                apath.push_back(pre);
                pre=path[pre];
            }
            printf("%d",v);  //选输出起点v
            for(int k=apath.size()-1;k>=0;k--)
                printf("->%d",apath[k]);  //再反向输出路径中其他顶点
            printf("\n");    
            }
        }
        else {
            printf("   从%d到%d没有路径\n",v,i);
        }
    }

}


//Floyd算法利用一个二维数组Al来存放当前顶点之间的最短路径长度，Ak[i][k]表示从顶点i到顶点j的路径上所经过的顶点编号不大于k的最短路径
//A-1[i][j]=g.edges[i][j]
//Ak[i][j]=MIN{Ak-1[i][j],Ak-1[i][k]+Ak-1[k][j]}
//还需要一个二维数组path来保存最短路径，它与当前的迭代次数有关
//pathk[i][j]表示在考虑顶点k时的从顶点i到顶点j的最短路径的前驱结点
void Floyd(MatGraph& g)
{
    int A[MAXV][MAXV];  //建立A数组
    int path[MAXV][MAXV];  //建立path数组

    for(int i=0;i<g.n;i++)  //初始化A数组和path数组
    {
        for(int j=0;j<g.n;j++)
        {
            A[i][j]=g.edges[i][j];
            if(i!=j && g.edges[i][j]<INF)
                path[i][j]=i;  //顶点i和顶点j之间有一条边的时候
            else
                path[i][j]=-1;  //顶点i和顶点j直接没有边的时候
        }
    }
    for(int k=0;k<g.n;k++)
    {
        for(int i=0;i<g.n;i++)
            for(int j=0;j<g.n;j++)
                if(A[i][j]>A[i][k]+A[k][j])
                {
                    A[i][j]=A[i][j]+A[k][j];  //修改最短路径
                    path[i][j]=path[k][j];
                }
    }
    Dispath(A,path,g.n);//输出结果
}
void Dispath(int A[][MAXV],int path[][MAXV];int n)
//输出
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(A[i][j]!=INF && i!=j)  //如果ij两点间存在路径
            {
                vector<int> apath;  //存放一条i到j的最短路径
                printf("顶点%d到%d的最短路径长度：%d\t路径：",i,j,A[i][j]);
                apath.push_back(j);  //路径上添加终点j
                int pre=path[i][j];
                while(pre!=i)  //在路径上添加中间点
                {
                    apath.push_back(pre);
                    pre=path[i][pre];
                }
                cout<<i;  //输出顶点i
                for(int k=apath.size()-1;k>=0;k--)
                    printf("->%d",apath[k]);  //反向输出路径上的其他顶点
                printf("\n");
            }
        }
    }
}//弗洛伊德算法有三重循环，时间复杂度为O(n^3)