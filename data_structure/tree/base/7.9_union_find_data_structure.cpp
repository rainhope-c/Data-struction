//并查集
//给定n个结点的集合，结点编号1~n，再给定一个等价关系，由登记啊关系产生所有结点的一个划分，每个节点属于一个等价类
//要求求一个节点所属的等价类以及合并两个等价类
//用有根树来表示集合，树中每个结点包括集合的一个的一个成员，每棵树表示一个集合
//多个集合形成一个森林，每棵树的树根表示集合的代表
#include <iostream>
using namespace std;

const int MAXN=1000;

int parent[MAXN];  //并查集存储结构
int rnk[MAXN];  //存储结点的秩
int n;  //n表示结点个数
int m;  //m表示初始的的等价关系的个数
void Init()
{
    for(int i=0;i<=n;i++)
    {
        parent[i]=i;  //初始化建立并查集
        rnk[i]=0;  //结点的秩初始化为0
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

int main()
{
cout<<"请输入数据结点个数和等价关系的个数："<<endl;
cin>>n>>m;  //输入数据结点个数和等价关系的个数
if(n==0) return;
Init();  //初始化并查集
for(int i=0;i<m;i++)
{
    cout<<"请输入第"<<i<<"组等价关系";
    int a,b;
    cin>>a>>b;
    Union(a,b);  //合并并查集a和b
}
int cnt=0;
for(int i=0;i<=n;i++)
{
    if(parent[i]==i)
        cnt++;  //求子树个数ans
}
cout<<cnt;  //输出的cnt是最终的集合个数
return 0;
}
