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

//图的邻接表存储类AdjGraph
class AdjGraph
{
public:
    HNode adjlist[MAXV];  //头结点数组
    int n,e;
    AdjGraph()
    {
        for(int i=0;i<MAXV;i++)  //初始头结点的firstarc设置为0
            adjlist[i].firstarc=NULL;
    }
    // ~AdjGraph()  //析构函数，释放图的邻接表空间
    // {
    //     ArcNode* pre,*p;
    //     for(int i=0;i<n;i++)  //遍历所有头结点
    //     {
    //         pre=adjlist[i].firstarc;
    //         if(pre!=NULL)
    //         {
    //             p=p->nexctarc;
    //             while(p!=NULL)  //释放adjlist[i]的所有边结点空间
    //             {
    //                 delete pre;
    //                 pre=p; p=p->nexctarc; //pre和p指针同步后移
    //             }
    //             delete pre;
    //         }
    //     }
    // }

    //下面是图的基本算法
    void CreateAdjGraph(int a[][MAXV],int n,int e)  //利用邻接数组a，顶点数n和边数e创建图的邻接表
    {
        ArcNode* p;
        this->n=n;  this->e=e;
        for(int i=0;i<n;i++)  //检查邻接矩阵中的每一个元素
            for(int j=n-1;j>=0;j--)
                if(a[i][j]!=0 && a[i][j]!=INF)  //存在一条边
                {
                    p=new ArcNode;  //创建一个结点
                    p->adjvex=j;
                    p->weight=a[i][j];
                    p->nexctarc=adjlist[i].firstarc;  //采用头插法插入p
                    adjlist[i].firstarc=p;
                }
    }
    //输出图
    void DisAdjGraph()  //输出图的邻接表
    {
        ArcNode* p;
        for(int i=0;i<n;i++)  //遍历每个头结点
        {
            cout<<"["<<i<<"]";
            p=adjlist[i].firstarc;  //p指向第一个邻接点
            if(p!=NULL) cout<<"->";
            while(p!=NULL)  //遍历第i个结点
            {
                cout<<" ("<<p->adjvex<<","<<" "<<p->weight<<")";
                p=p->nexctarc;  //p移向下一个邻接点
            }
            cout<<endl;
        }
    }
};


//下面是一些基本算法
//求无向图的度
int Degree1(AdjGraph& G,int v)  //无向图邻接表G中求顶点v的度
{
    int d=0;
    ArcNode* p=G.adjlist[v].firstarc;
    while(p!=NULL)  //统计单链表v中边结点个数
    {
        d++;
        p=p->nexctarc;
    }
    return d;
}
vector<int> Degree2(AdjGraph& G,int v)  //有向图邻接表G中求顶点v的出度和入度
{
    vector<int> ans{0,0};  //ans[0]累计出度，ans[1]累计入度
    ArcNode* p=G.adjlist[v].firstarc;
    while(p!=NULL)  //统计单链表v中边结点个数
    {
        ans[0]++;
        p=p->nexctarc;
    }
    for(int i=0;i<G.n;i++)
    {
        p=G.adjlist[i].firstarc;
        while(p!=NULL)
        {
            if(p->adjvex==v);
            {
                ans[1]++;
                break;  //每个单链表最多只有一个这样的结点
            }
            p=p->nexctarc;
        }
    }
    return ans;  //返回结果
}

int main()
{
    AdjGraph G;
    int n=5,e=5;
    int A[MAXV][MAXV]={{0,8,INF,5,INF},{INF,0,3,INF,INF},{INF,INF,0,INF,6},{INF,INF,9,0,INF},{INF,INF,INF,INF,0}};

    G.CreateAdjGraph(A,n,e);
    cout<<"图的邻接表："<<endl;    G.DisAdjGraph();
    // cout <<"销毁图"<<endl;
    return 0;
}