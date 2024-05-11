//哈夫曼树，每个结点赋上一个数值——权、
//从根结点到某个结点之间的路径长度与该节点权的乘积称为结点的带权路径长度
//当带全路径长度的和最小的二叉树称为哈夫曼树
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct HTNode //哈夫曼树结点类
{
    char data;  //结点值
    double weight;  //权值
    int parent;  //双亲结点
    int lchild;  //左孩子结点
    int rchild;  //右孩子结点
    bool flag;  //标识是双亲的左(true)右(false)孩子结点
    HTNode()  //构造函数
    {
    parent=-1;
    lchild=rchild=-1;
    }
    HTNode(char d,double w)
    {
    data=d;
    weight=w;
    parent=lchild=rchild=-1;
    flag=true;
    }
    /* data */
};
struct HeapNode  //优先队列元素类型
{
    double w;  //权值
    int i;  //对应哈夫曼树中的结点编号
    HeapNode(double w1,int i1):w(w1),i(i1){}  //构造函数
    bool operator< (const HeapNode& s) const  //重载小于号
    {
    return w>s.w;  //按w越小越优先出列
    }
};

class HT{
public:
int n0;  //叶子结点的数量
vector<char>D;  //叶子结点的值
vector<double>W;  //叶子结点的权
vector<HTNode>ht;  //存放结果
vector<string>hcd;  //存放得到的编码

void CreateHT()  
{
priority_queue<HeapNode>qu;  //建立优先队列
for(int i=0;i<n0;i++)
{   ht[i]=HTNode(D[i],W[i]);  //建立一个叶子节点
    qu.push(HeapNode(W[i],i));  //将(W[i],i)进队
}
for(int i=n0;i<2*n0-1;i++)
{
    HeapNode p1=qu.top();  qu.pop();
    HeapNode p2=qu.top();  qu.pop();
    ht[i]=HTNode();
    ht[i].weight=ht[p1.i].weight+ht[p2.i].weight;  //求权值的和
    ht[p1.i].parent=i;  //设置ht[p1.i]的双亲为ht[i]
    ht[i].lchild=p1.i;  //将ht[p1.i]作为双亲ht[i]的左孩子
    ht[p1.i].flag=true;
    ht[p2.i].parent=i;  //设置ht[p2.i]的双亲为ht[i]
    ht[i].rchild =p2.i;  //设置ht[p2.i]作为双亲ht[i]的右孩子
    ht[p2.i].flag=false;
    qu.push(HeapNode(ht[i].weight,i));  //将新结点ht[i]进队
}
}

void CreateHCode()  //根据哈夫曼树求哈夫曼编码
{
for(int i=0;i<n0;++i)
{
string code="";  
int j=i;
while(ht[j].parent!=-1)
{
if(ht[j].flag)
    code+="0";  //ht[j]结点是双亲的左孩子
else    code+="1";  //是右孩子
j=ht[i].parent;
}
reverse(code.begin(),code.end());  //将code逆置并添加到hec中
hcd[i]=code q1;
}
}
};