//图的邻接矩阵类

#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int MAXV =100;  //图中最多的顶点数
const int INF=0x3f3f3f3f;  //INF是无限大
class MatGraph
{
public:
    int edges[MAXV][MAXV];  //邻接矩阵数组，这个元素类型为int
    int n,e; //顶点数和边数
    string vexs[MAXV];  //存放顶点信息

    //图的基本运算
    //创建邻接矩阵表达的图
    void CreateMatGraph(int a[][MAXV],int n,int e)  //邻接矩阵数组a，顶点数n和边数e
    {
        this->n=n; this->e=e;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
                this->edges[i][j]=a[i][j];
        }
    }
    void DisMatGraph()  //输出图的邻接矩阵
    {
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(edges[i][j]==INF)  //如果是无限大
                    cout<<"∞"<<" ";  //打印无限大
                else
                    cout<<edges[i][j]<<" ";  //否则打印相应的数值
            }
            cout<<endl;
        }
    }
};



//下面是一些基本的算法
//求度
int Degree1(MatGraph& g,int v)  //无向图邻接矩阵中求顶点v的度
{
    int d=0;
    for(int j=0;j<g.n;j++)
    {
        if(g.edges[v][j]!=0 && g.edges[v][j]!=INF)  //统计第v行中的非零非无限元素的个数
            d++;
    }
    return d;
}
vector<int> Degree2(MatGraph& g,int v)  //求有向图的出度和入度
{
    vector<int> ans{0,0};  //ans[0]累计出度，ans[1]累计入度
    for(int j=0;j<g.n;j++)
        if(g.edges[v][j]!=0 && g.edges[v][j]!=INF)  //第v行中非0非无限的元素表示出度
            ans[0]++;
    for(int i=0;i<g.n;i++)
        if(g.edges[i][v]!=0 && g.edges[i][v]!=INF)  //第v列中非0非无限的元素表示出度
            ans[1]++;
    return ans;
}


int main()
{
    MatGraph g;
    int n=5,e=5;
    int a[MAXV][MAXV]={{0,8,INF,5,INF},{INF,0,3,INF,INF},{INF,INF,0,INF,6},{INF,INF,9,0,INF},{INF,INF,INF,INF,0}};
    g.CreateMatGraph(a,n,e);  //创建这个图
    cout<<"g:"<<endl;  g.DisMatGraph();
    return 0;
}
//邻接表的存储方法

#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int MAXV =100;  //图中最多的顶点数
const int INF=0x3f3f3f3f;  //INF是无限大
struct ArcNode  //边结点
{
    int adjvex;  //邻接点
    int weight;  //权值
    ArcNode* nexctarc;  //指向下一条边的边结点
};
struct HNode  //头结点
{
    string info;  //顶点信息
    ArcNode* firstarc;  //指向第一条边的边结点
};

