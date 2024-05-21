#include "MatGraph.cpp"
#include "AdjGraph.cpp"
#include <algorithm>
// #include <iostream>
//最小生成树：一个有n个顶点的灵通图的生成树是一个极小联通子图，包含n个顶点和n-1个边


//Prim算法生成以v为起始点的最小生成树  思路为
// （ 1）初始化U={v}。以v到其他顶点的所有边为候选边。
// （ 2）重复以下步骤n-1次，使得其他n-1个顶点被加入到U中：
// ① 从候选边中挑选权值最小的边加入TE（所有候选边一定是连
// 接两个顶点集U和V-U的边），设该边在V-U中的顶点是k，将顶点k加
// 入U中。
// ② 考察当前V-U中的所有顶点j，修改候选边：若(k， j)的权值
// 小于原来和顶点j关联的候选边，则用(k， j)取代后者作为候选边。
void Prim(MatGraph g,int v)  //Prim算法输出最小生成树
{
//初始化阶段
    int lowcost[MAXV];  //建立数组lowcost中存储的是集合V-U中某元素到集合U中任意元素的最小权
    int closest[MAXV];  //建立数组closest记录V-U中某元素到U中哪个元素最近
    for(int i=0;i<g.n;i++)
    {
        lowcost[i]=g.edges[v][i];  //刚开始U中只有一个v，所以lowcost就是直接v到i的距离
        closest[i]=v;  //因为只有一个v，别无选择了
    }
//找出n-1个顶点
    for(int i=1;i<g.n;i++)
    {
        int min=INF;  
        int k=-1;  //用k记录最近的顶点的编号
        for(int j=0;j<g.n;j++)  //在（V-U）中找出离U最近的顶点k
            if(lowcost[j]!=0 && lowcost[j]<min)  //lowcost[j]==0表示j已经在U中了
            {
                min=lowcost[j];  //找到了就替换一下
                k=j;
            }
        cout<<"  边("<<closest[k]<<","<<k<<" ,权为"<<min<<endl;
        lowcost[k]=0;  //标记k已经加入U 
        for(int j=0;j<g.n;j++)  //更新两个数组  思路为遍历V-U中每个元素，找到当前的lowcost和g.edged[k][j]谁更小
            if(lowcost[j]!=0 && g.edges[k][j]<lowcost[j])  //如果更小就更新
            {
                lowcost[j]=g.edges[k][j];
                closest[j]=k;
            }
    }
}

//Krukal算法构造最小生成树
// （1）置U的初值等于V（即包含有G中的全部顶点），TE的初值
// 为空集（即图T中每一个顶点都构成一个分量）。
// （2）将图G中的边按权值从小到大的顺序依次选取：若选取的边
// 未使生成树T形成回路，则加入TE；否则舍弃，直到TE中包含n-1
// 条边为止。

//关键在于怎么判断便捷是否与生成树之间有无回路 解决方法是设置一个辅助数组vset[0...n-1]，其元素vset[i]代表顶点i所属于的联通变量的编号
//由于是无向图，所以把邻接矩阵的上三角部分的所有边存放在边向量E中
struct Edge  //边向量元素类型
{
    int u;  //起始顶点
    int v;  //终止顶点
    int w;  //权值

    Edge(int u,int v,int w)  //构造函数
    {
        this->u=u;
        this->v=v;
        this->w=w;
    }
    bool operator<(const Edge& s)const  //重载构造小于号
    {
        return w<s.w;
    }
};
void Kruskal(MatGraph& g)
{
    int vset[MAXV];  //建立数组vset
    vector<Edge>E;  //建立数组存放所有的边
    for(int i=0;i<g.n;i++)  
        for(int j=0;j<g.n;j++)
            if(g.edges[i][j]!=0 &&g.edges[i][j]!=INF && i<j)  //遍历半个矩阵就行了
                E.push_back(Edge(i,j,g.edges[i][j]));
    sort(E.begin(),E.end());  //对E进行按权值的递增排序
    for(int i=0;i<g.n;i++)  vset[i]=i;  //初始化辅助数组
    int k=1;  //k是当前构造生成数的第几条边，初始值为1
    int j=0;  //E中边的下标
    while(k<g.n)  //如果还没有把所有边看一遍
    {
        int u1=E[j].u;
        int v1=E[j].v;  //取出一条边的起始和终止顶点
        int sn1=vset[u1];
        int sn2=vset[v1];  //分别得到两个边的起始和终止顶点
        if(sn1!=sn2)  //如果两个顶点属于不同的集合
        {
            cout<< "  边()"<<u1<<","<<v1<<"),权为"<<E[j].w<<endl;
            k++;  //生成的边数加一
            for(int i=0;i<g.n;i++)
                if(vset[i]==sn2)   //找到和v在同一个集合的点并且修改他们的编号表示在同一个集合
                    vset[i]=sn1;
        }
        j++;  //扫描下一条边
    }
}
//优化克鲁斯卡尔算法的主要思路就是利用并查集让最后集合合并时的时间复杂度更小
int parent[MAXV];  //并查集存储结构
int rnk[MAXV];  //存储结点的秩

void Init(int n)
{
    for(int i=0;i<n;i++)  //并查集的初始化  
    {
        parent[i]=i;
        rnk[i]=0;
    }
}
int Find(int x)  //查找x所处的并查集的根结点
{
    if(x!=parent[x])  //如果x不是他自己的父母
        parent[x]=Find(parent[x]);  //路径压缩
    return parent[x];
}
void Union(int x,int y)  //并查集中x和y两个集合的合并
{
    int rx=Find(x);
    int ry=Find(y);  //找到xy所属于的集合的根结点
    if(rx==ry)
        return ;  //如果已经在一个集合了，啥都不用干
    if(rnk[rx]<rnk[ry])
        parent[rx]=ry;  //也是路径压缩的目的
    else
    {if(rnk[rx]==rnk[ry])  //秩相同，合并后rx的秩加一
        rnk[rx]++;
    parent[ry]=rx;  //ry结点作为rx结点的孩子
    }
}
void Kruskal1(MatGraph& g)  //改进的Kruskal1算法
{
    vector<Edge>E;  //建立数组存放所有的边
    for(int i=0;i<g.n;i++)  
        for(int j=0;j<g.n;j++)
            if(g.edges[i][j]!=0 &&g.edges[i][j]!=INF && i<j)  //遍历半个矩阵就行了
                E.push_back(Edge(i,j,g.edges[i][j]));
    sort(E.begin(),E.end());  //对E进行按权值的递增排序
    Init(g.n);//并查集初始化
    int k=1;  //k是当前构造生成数的第几条边，初始值为1
    int j=0;  //E中边的下标
    while(k<g.n)  //如果还没有把所有边看一遍
    {
        int u1=E[j].u;
        int v1=E[j].v;  //取出一条边的起始和终止顶点
        int sn1=Find(u1);
        int sn2=Find(v1);  //分别得到两个边的起始和终止顶点
        if(sn1!=sn2)  //如果两个顶点属于不同的集合
        {
            cout<< "  边()"<<u1<<","<<v1<<"),权为"<<E[j].w<<endl;
            k++;  //生成的边数加一
            Union(sn1,sn2);  //合并
        }
        j++;  //扫描下一条边
    }}