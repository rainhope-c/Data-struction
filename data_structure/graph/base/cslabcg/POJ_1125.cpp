// 【问题描述】
// 股票经纪人会对消息反应过度，由若干股票经纪人组成的一个股票经纪人社区，从一个股票经纪人传递消息另一个股票经纪人需要一定的时间，注意从A传递到B所花费的时间不一定与从B传递给A所花费的时间相同。你的任务是编写一个程序，该程序选择哪个股票经纪人作为消息的起点，以及该消息传播到整个股票经纪人社区所需的时间，该持续时间以最后一个人接收消息所需的时间来衡量。
// 【输入形式】
// 输入包含多组股票经纪人的数据，每组的第一行是股票经纪人数量n（1到100），每个人的编号从1到n。接下来每个股票经纪人对应一行，其格式是，他的联系人数量（m），后跟m对整数，分别为联系人编号和将消息传递给该联系人所花费的时间（以分钟为单位）。没有特殊的标点符号或间距规则。
// 【输出形式】
// 对于每组数据，输出一行包含消息传输最快的人的编号，以及在将该消息发送给此人之后，最后一个人多久后收到该消息，以整数分钟为单位。如果不能传递到某些人则输出"disjoint"。
// 【样例输入】
//         5
//         3 4 4 2 8 5 3
//         1 5 8
//         4 1 6 4 10 2 7 5 2
//         0
//         2 2 5 1 5
// 【样例输出】
//         3 10
// 【样例说明】
//        3号股票经纪人作为消息的起点，消息传播的最快，最后一个人10分钟后收到消息。测试数据存放在in.txt文件中。
// 【评分标准】
//         共10个测试用例，每通过一个测试得10分。

//这是个典型的单向图模型
//第一行的输入表示结点数 接下 是每个结点对应的能连接到的结点和相应的权 一共有结点个数行 这个权的格式是结点标号＋权值
//我们要求的是求出最短路径 这个最短路径是从一个结点开始到所有其他节点的路径的值的最大值的最小值 然后输出这个结点的标号和最小值
//直接利用算法好像就行
//直接用Floyd算法求出最短路径呗
//那难点就在于创建这个图了

//图的邻接矩阵类

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

const int MAXV =100;  //图中最多的顶点数
const int INF=0x3f3f3f3f;  //INF是无限大
class MatGraph
{
public:
    int edges[MAXV][MAXV]; // 初始化大小为m×m的二维向量 
    int n,e; //顶点数和边数
    string vexs[MAXV];  //存放顶点信息

    //图的基本运算
    //创建邻接矩阵表达的图
    void CreateMatGraph(vector<vector<int>> a,int n,int e)  //邻接矩阵数组a，顶点数n和边数e
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

// //Floyd算法
// void Dispath(int A[][MAXV],int path[][MAXV],int n)
// //输出
// {
//     for(int i=0;i<n;i++)
//     {
//         for(int j=0;j<n;j++)
//         {
//             if(A[i][j]!=INF && i!=j)  //如果ij两点间存在路径
//             {
//                 vector<int> apath;  //存放一条i到j的最短路径
//                 printf("顶点%d到%d的最短路径长度：%d\t路径：",i,j,A[i][j]);
//                 apath.push_back(j);  //路径上添加终点j
//                 int pre=path[i][j];
//                 while(pre!=i)  //在路径上添加中间点
//                 {
//                     apath.push_back(pre);
//                     pre=path[i][pre];
//                 }
//                 cout<<i;  //输出顶点i
//                 for(int k=apath.size()-1;k>=0;k--)
//                     printf("->%d",apath[k]);  //反向输出路径上的其他顶点
//                 printf("\n");
//             }
//         }
//     }
// }//弗洛伊德算法有三重循环，时间复杂度为O(n^3)

//我们要的结果需要满足俩个点 一是能通往任意节点，二是通往任意节点的的路径中的最长值最小
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
                    A[i][j]=A[i][k]+A[k][j];  //修改最短路径
                    path[i][j]=path[k][j];
                }
    }
    // for(int i=0;i<g.n;i++)
    // {
    //     for(int j=0;j<g.n;j++)
    //     {
    //         cout<<A[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    // cout <<endl;
    //我们现在是得到这个最短路径数组了 然后处理一下就行了
    vector<int> longestlength(g.n,INF);
    for(int i=0;i<g.n;i++)
    {
        int longest=0;
        for(int j=0;j<g.n;j++)  //需要想办法得到最长的
            longest=max(longest,A[i][j]);
        longestlength[i]=longest;
    }
    // for(int i=0;i<g.n;i++)
    //     cout<<longestlength[i]<<" ";
    //得到每个顶点的最长的了
    int shortest=INF;
    int num=0;
    for(int i=0;i<g.n;i++)
    {  
        if(longestlength[i]<shortest)
        {
            num=i;
            shortest=longestlength[i];
        }
    }
    if(shortest==INF)
        cout<<"disjoint"; 
    else
        cout<<num+1<<" "<<shortest;

}


// 【样例输入】
        // 5
        // 3 4 4 2 8 5 3
        // 1 5 8
        // 4 1 6 4 10 2 7 5 2
        // 0
        // 2 2 5 1 5
int main()
{
    ifstream infile;
    infile.open("in.txt");
    int n;
    infile>>n;  //输入节点个数
    vector<vector<int>> tem(n,vector<int>(n,INF)); // 初始化大小为m×m的二维向量 
    //需要设置对角为0
    for(int i=0;i<n;i++)
        tem[i][i]=0;
    int e;  //e表示边数
    for(int i=0;i<n;i++)
    {
        int demo;
        infile>>demo;
        e+=demo;
        int num,quan;  //输入终点和权
        for(int j=0;j<demo;j++)
        {
            infile>>num>>quan;
            tem[i][num-1]=quan;  //表示从i到num的边的权是quan
        }
    }
    //输入完成了 现在需要创建邻接矩阵
    MatGraph g;
    g.CreateMatGraph(tem,n,e);
    // g.DisMatGraph();  //输出试试？
    //ok邻接表创建完毕
    //接下来就是用Floyd算法了
    Floyd(g);//这个Floyd写的不好改
    return 0;
}
