// 【问题描述】
//      由二叉树的先序序列和中序序列构造二叉树并求其后序序列
// 【输入形式】
//     每个测试用例的第一行包含一个整数n（1<=n<=1000）表示二叉树的节点个数，所有节点的编号为1~n，后面两行分别给出先序序列和中序序列。可以假设构造出的二叉树是唯一的。
// 【输出形式】
//     对于每个测试用例，输出一行表示其后序序列。
// 【样例输入】
//   9
//   1 2 4 7 3 5 8 9 6
//   4 7 2 1 8 5 9 3 6
// 【样例输出】
//  7 4 2 8 9 5 6 3 1
// 【样例说明】
//      测试数据的文件名为in.txt
// 【评分标准】
//     该题目有10个测试用例，每通过一个测试用例，得10分。

//这题也没提前告知这个结点的data是什么数据类型，我来扒一下
//从扒来的数据看都是int类型的
//直接根据先序序列和中序序列建立二叉树然后输出这个二叉树的后序序列不就行了

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <string>
#include <fstream>

using namespace std;

struct BTNode  //二叉链结点类
{
	int data;  //数据元素
	BTNode* lchild;  //左孩子结点
	BTNode* rchild;  //右孩子结点
	BTNode():lchild(NULL), rchild(NULL){}  //构造函数
	BTNode(int d)
	{
		data = d;
		lchild = rchild = NULL;
	}
};

class BTree
{
public:
	BTNode* r;  //二叉树的根节点r
	BTree()  //构造函数，创建一个空树
	{
		r = NULL;
	}
};
//后序遍历的算法
void PostOrder1(BTNode* b)
{
if(b!=NULL)
{
PostOrder1(b->lchild);  //先对左子树遍历
PostOrder1(b->rchild);  //再对右子树遍历
cout<<b->data<<" ";  //再访问当前根节点
}
}
void PostOrder(BTree &bt)   //后序遍历算法
{
PostOrder1(bt.r);
}

//用先序序列和中序序列还原二叉树

BTNode* CreatBTree11(vector<int>pres,int i,vector<int>ins,int j,int n)  
//这些参数分别是先序序列，这个子树的根节点在先序序列的位置。中序序列，这个子树的根节点在中序序列的位置，这个子树的全部结点数
{
if(n<=0) return NULL; 
int d =pres[i];  //取根节点的值
BTNode*b=new BTNode(d);  //创建根结点
int p=j;
while(ins[p]!=d) p++;   //循环在中序序列中找到根结点的位置
int k=p-j;  //左子树的结点个数k
b->lchild=CreatBTree11(pres,i+1,ins,j,k);  //递归构造左子树
b->rchild=CreatBTree11(pres,i+k+1,ins,p+1,n-k-1);  //递归构造右子树
return b;
}
void CreayBTree1(BTree& bt,vector<int> pres,vector<int> ins)
{
	int n=pres.size();
	bt.r=CreatBTree11(pres,0,ins,0,n);
}

int main()
{
    ifstream infile("in.txt");
    int m;
    infile>>m;
    vector<int>pres(m),ins(m);  //创建两个数组收集先序序列和后序序列
    for(int i=0;i<m;i++)
    {
    int tem=0;
    infile>>tem;
    pres[i]=tem;
    }
    for(int i=0;i<m;i++)
    {
    int tem=0;
    infile>>tem;
    ins[i]=tem;
    }
    BTree target;
    CreayBTree1(target,pres,ins);
    PostOrder(target);
    return 0;
}