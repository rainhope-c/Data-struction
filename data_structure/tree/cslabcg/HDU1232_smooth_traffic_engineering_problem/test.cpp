// 【问题描述】
// 某省调查城镇交通状况，得到现有城镇道路统计表，表中列出了每条道路直接连通的城镇。省政府“畅通工程”的目标是使全省任何两个城镇间都可以实现交通（但不一定有直接的道路相连，只要互相间接通过道路可达即可）。问最少还需要建设多少条道路？
// 【输入形式】
//   每个测试用例的第1行给出两个正整数，分别是城镇数目n（n<1000）和道路数目m，随后的m行对应m条道路，每行给出一对正整数，分别是该条道路直接连通的两个城镇的编号。为简单起见，城镇从1到n编号。注意两个城市之间可以有多条道路相通，也就是说：
// 3 3
// 1 2
// 1 2
// 2 1
// 这种输入也是合法的。
// 【输出形式】对每个测试用例，在一行里输出最少还需要建设的道路数目。
// 【样例输入】
// 3 3
// 1 2
// 1 3
// 2 3
// 【样例输出】
// 0
// 【样例说明】
//      测试数据的文件名为in.txt
// 【评分标准】
//    该题目有10个测试用例，每通过一个测试用例，得10分。

//输入的第一行是城镇树木n和道路数目m
//接下来m行是这些道路所连接的城市
//输出最少还需要建设的城市
//考察的是并查集诶...
//如果两个城市之间有道路，那么这两个城市就是一个集
//这样建立若干个集
//建立完成后合并这些集，最终得到x个集合
//那么就需要x-1条道路把这x个集联系起来

#include <iostream>
#include <fstream>

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
ifstream infile("in.txt");
infile>>n>>m;  //输入城镇数目和已经有的道路的数目
Init();  //初始化并查集
for(int i=0;i<m;i++)
{
    int a,b;
    infile>>a>>b;
    Union(a,b);  //合并并查集a和b
}
int ans=0;
for(int i=0;i<=n;i++)
{
    if(parent[i]==i)
        ans++;  //求子树个数ans
}
cout<<ans-2;  //结果是ans-1
return 0;
}
