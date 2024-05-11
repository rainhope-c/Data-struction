//二叉树的遍历以及相关算法

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

struct BTNode  //二叉链结点类
{
	char data;  //数据元素
	BTNode* lchild;  //左孩子结点
	BTNode* rchild;  //右孩子结点
	BTNode():lchild(NULL), rchild(NULL){}  //构造函数
	BTNode(char d)
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

//二叉树的基本运算

//创建二叉树（以括号表示串为例）
	void CreatBTree(string str)  //str是这个括号表示串
	{
		stack<BTNode*>st;  //定义一个栈st
		BTNode* p;
		bool flag;
		int i = 0;
		while (i < str.length())  //遍历str中的字符
		{
			switch (str[i])
			{
			case '(':    //如果输入的是一个"("，就说明刚刚建立的新结点p有子树
				st.push(p);  //压入栈进行处理
				flag = true;  //flag=true表示是对左子树进行处理
				break;
			case ')':
				st.pop();  //表示这个结点p处理完毕，进行出栈
				break;
			case ',':
				flag = false;  //左子树处理好了，接下来处理右子树
				break;
			default:  //如果输入的不是"(),"就说明这是个结点值 
				p = new BTNode(str[i]);  //创建一个新的结点
				if (r == NULL)
					r = p;
				else
				{
					if (flag && !st.empty())
						st.top()->lchild = p;  //存到左边或者右边
					else if (!st.empty())
						st.top()->rchild = p;
				}
				break;
			}
			i++;  //继续遍历
		}
	}

	//反过来，求二叉树的括号表示串
	void DispBTree()  //将二叉链转换为括号表达式并输出
	{
		DispBTreel(r);
	}
	void DispBTreel(BTNode* b)  //被DispBTree函数调用
	{
		if (b != NULL)
		{
			cout << b->data;  //输出根节点的值
			if(b->lchild!=NULL||b->rchild!=NULL)
			{
				cout << "(";  //有孩子结点的时候输出(
				DispBTreel(b->lchild);  //递归输出左子树
				if (b->rchild != NULL)
					cout << ",";  //有右子树的时候输出 ，
				DispBTreel(b->rchild);  //递归输出右子树

				cout << ")";  //输出")"
			}
		}
	}

	//查找值为x的结点
	BTNode* FindNode(char x)
	{
		return FindNodel(r, x);
	}
	BTNode* FindNodel(BTNode* b, char x)
	{
		BTNode* p;
		if (b == NULL) return NULL;  //
		else if (b->data == x) return b;  //若p所指的结点值为x的时候返回
		else
		{
			p = FindNodel(b->lchild, x);  //在左子树中查找
			if (p != NULL)
				return p;  //在左子树中找到节点
			else
				return FindNodel(b->rchild, x);  //返回右子树中的查找结果
		}
	}
	//求高度
	int Height()
	{
		return Heightl(r);
	}
	int Heightl(BTNode* b)  
	{
		if (b == NULL)  //空树的高度是0
			return 0;
		else
			return max(Heightl(b->lchild), Heightl(b->rchild) + 1);
	}
	//销毁二叉树
	void DestoryBTrer(BTNode* b)
	{
		if (b != NULL)
		{
			DestoryBTrer(b->lchild);
			DestoryBTrer(b->rchild);
			delete b;
		}
	}
	~BTree()
	{
		DestoryBTrer(r);
		r = NULL;
	}


};






//上面是基本的定义

//先序遍历算法
void PerOrder1(BTNode *b)
{
if(b!=NULL)
{
cout <<b->data;  //访问根节点
PerOrder1(b->lchild);  //先序遍历左节点
PerOrder1(b->rchild);  //先序遍历右节点
}
}
void PerOrder(BTree& bt)  //先序遍历的递归算法
{
PerOrder1(bt.r);
}

//中序遍历算法
void InOrder1(BTNode *b)  //被InOrder1函数调用
{
if(b!=NULL)
{
InOrder1(b->lchild);  //先遍历左子树
cout<<b->data;  //访问根节点
InOrder1(b->rchild);  //再遍历左子树
}
}
void InOrder(BTree &bt)  //中序递归的遍历算法
{
InOrder1(bt.r);
}

//后序遍历的算法
void PostOrder1(BTNode* b)
{
if(b!=NULL)
{
PostOrder1(b->lchild);  //先对左子树遍历
PostOrder1(b->rchild);  //再对右子树遍历
cout<<b->data;  //再访问当前根节点
}
}
void PostOrder(BTree &bt)   //后序遍历算法
{
PostOrder1(bt.r);
}


//计算二叉树中的结点个数

//基于先序遍历的思想
int NodeCount11(BTNode *b)
{
int m,n,k;  //k表示根结点，m表示左子树的结点数，n表示右子树的结点数
if(b!=NULL)
{
k=1;
m=NodeCount11(b->lchild);  //遍历求左子树的结点数
n=NodeCount11(b->rchild);  //遍历求右子树的结点数
return k+m+n;
}
else return 0;  //空树节点数为0
}
int NodeCout1(BTree&bt)  //遍历求结点个数
{
return NodeCount11(bt.r);
}
//基于中序遍历的思想
int NodeCount21(BTNode *b)
{
int m,n,k;  //k表示根结点，m表示左子树的结点数，n表示右子树的结点数
if(b!=NULL)
{
m=NodeCount21(b->lchild);  //遍历求左子树的结点数
k=1;
n=NodeCount21(b->rchild);  //遍历求右子树的结点数
return k+m+n;
}
else return 0;  //空树节点数为0
}
int NodeCout2(BTree&bt)  //遍历求结点个数
{
return NodeCount21(bt.r);
}
//基于后序遍历的思想
int NodeCount31(BTNode *b)
{
int m,n,k;  //k表示根结点，m表示左子树的结点数，n表示右子树的结点数
if(b!=NULL)
{
m=NodeCount31(b->lchild);  //遍历求左子树的结点数
n=NodeCount31(b->rchild);  //遍历求右子树的结点数
k=1;
return k+m+n;
}
else return 0;  //空树节点数为0
}
int NodeCout3(BTree&bt)  //遍历求结点个数
{
return NodeCount31(bt.r);
}
//基于递归的思想
int NodeCount41(BTNode*b)
{
if(b==NULL)
return 0;
else 
return (NodeCount41(b->lchild)+NodeCount41(b->rchild)+1);
}
int NodeCount4(BTree &bt)
{
return NodeCount41(bt.r);
}


//从左到右输出一棵二叉树的所有叶子值
//先序遍历
void DispLeaf11(BTNode* b)
{
if(b!=NULL)
{
if(b->lchild==NULL&&b->rchild==NULL)
cout<<b->data<<" ";  //根节点为叶子结点时输出
DispLeaf11(b->lchild);  //输出左子树的叶子结点
DispLeaf11(b->rchild);  //输出右子树的叶子结点
}
}
void DispLeaf1(BTree& bt)
{
DispLeaf11(bt.r);
}
//中序遍历
void DispLeaf21(BTNode* b)
{
if(b!=NULL)
{
DispLeaf21(b->lchild);  //输出左子树的叶子结点
if(b->lchild==NULL&&b->rchild==NULL)
cout<<b->data<<" ";  //根节点为叶子结点时输出
DispLeaf21(b->rchild);  //输出右子树的叶子结点
}
}
void DispLeaf2(BTree& bt)
{
DispLeaf21(bt.r);
}
//后序遍历
void DispLeaf31(BTNode* b)
{
if(b!=NULL)
{
DispLeaf31(b->lchild);  //输出左子树的叶子结点
DispLeaf31(b->rchild);  //输出右子树的叶子结点
if(b->lchild==NULL&&b->rchild==NULL)
cout<<b->data<<" ";  //根节点为叶子结点时输出
}
}
void DispLeaf3(BTree& bt)
{
DispLeaf31(bt.r);
}
//递归（实际上和先序遍历的代码相同）
void DispLeaf41(BTNode* b)
{
if(b!=NULL)
{
if(b->lchild==NULL&&b->rchild==NULL)
cout<<b->data<<" ";  //根节点为叶子结点时输出
DispLeaf41(b->lchild);  //输出左子树的叶子结点
DispLeaf41(b->rchild);  //输出右子树的叶子结点
}
}
void DispLeaf4(BTree& bt)
{
DispLeaf41(bt.r);
}


//交换所有子树的值
//先序遍历
void Swap11(BTNode *&b)
{
if(b!=NULL)
{
swap(b->lchild,b->rchild);  //交换根节点b的左右孩子指针
Swap11(b->lchild);  //递归交换左子树
Swap11(b->rchild);  //递归交换右子树
}
}
void Swap1(BTree &bt)
{
Swap11(bt.r);
}
//后序遍历
void Swap21(BTNode *&b)
{
if(b!=NULL)
{
Swap21(b->lchild);  //递归交换左子树
Swap21(b->rchild);  //递归交换右子树
swap(b->lchild,b->rchild);  //交换根节点b的左右孩子指针
}
}
void Swap2(BTree &bt)
{
Swap21(bt.r);
}
//注意这个算法不能利用中序遍历进行交换，中序遍历会让每个跟结点交换两次，实际上什么都没交换
// void Swap31(BTNode *&b)
// {
// if(b!=NULL)
// {
// Swap31(b->lchild);  //递归交换左子树
// swap(b->lchild,b->rchild);  //交换根节点b的左右孩子指针
// Swap31(b->rchild);  //递归交换右子树
// }
// }
// void Swap3(BTree &bt)
// {
// Swap31(bt.r);
// }


//若各个结点值不同，根据结点值求结点所在层次
//递归
int Level1(BTNode* b,char x,int h)
{
if(b==NULL)
return 0;
else if(b->data==x)
return h;
else{
int l=Level1(b->lchild,x,h+1);  //在下一层的左子树中寻找
if(l!=0)  //如果在左子树中找到了
return l;
else
return Level1(b->rchild,x,h+1);  //在下一层的右子树中寻找
}
}
int level(BTree& bt,char x)
{
return Level1(bt.r,x,1);
}


//求第k层的节点数
void KCount1(BTNode* b,int h,int k,int &cnt)
{
if(b==NULL) return ;  //空树返回
if(h==k) cnt++;  //若当前在第k层，cnt增1
if(h<k)  //如果当前层次低于k
{
KCount1(b->lchild,h+1,k,cnt);
KCount1(b->rchild,h+1,k,cnt);
}
}
int KCount(BTree& bt,int k)  //先序遍历求二叉树第k层结点个数
{
int cnt=0;
KCount1(bt.r,1,k,cnt);
return cnt;
}


//各结点值不同，求值为x的结点的所有祖先
//解法一，递归的思路
bool Ancestor11(BTNode* b,char x,vector<char>& res)
{
if(b==NULL)
return false;
if(b->lchild!=NULL&&b->lchild->data==x)  //若结点b的左孩子为x
{
res.push_back(b->data);  //把b压入，停止递归
return true;
}
if(b->rchild!=NULL&&b->rchild->data==x)  //若结点b的右孩子为x
{
res.push_back(b->data);  //把b压入，停止递归
return true;
}
if(Ancestor11(b->lchild,x,res)||Ancestor11(b->rchild,x,res))  
//在如果当前结点的左孩子右孩子都不是x，那就继续在左子树和右子树里面继续找
{
res.push_back(b->data);  //如果在左子树或者右子树里面找到了就把当前结点存进去
return true;
}
return false;  //如果什么都没找到就return false仍然需要退出这个递归，相对于一棵树找到头了
}
void Ancestor1(BTree& bt,char x,vector<char>& res)
{
Ancestor11(bt.r,x,res);
reverse(res.begin(),res.end());  //逆置res->按照根结点到结点x双亲的顺序  //?烦什么病又报错
}

//解法二，先序遍历的思路
void Ancestor21(BTNode* b,char x,vector<char>path,vector<char>&res)
{
if(b==NULL) return;  //空树返回
path.push_back(b->data);  //存入当前的数据
if(b->data==x)  //如果这个就是要找的
{
path.pop_back();  //把这个删除
res=path;  //复制path到res
return;  //找到路径后返回
}
Ancestor21(b->lchild,x,path,res);  //在左子树查找
Ancestor21(b->rchild,x,path,res);  //在右子树查找
//结束递归有两种可能，一是到头了还没找到，那就继续找，二是找到了，实际上还要继续寻找，不过这个结果已经存在相应的res中了
//所以这个算法添加了一个全局变量res
}
void Ancestor2(BTree& bt,char x,vector<char>& res)
{
vector<char>path;
Ancestor21(bt.r,x,path,res);
}