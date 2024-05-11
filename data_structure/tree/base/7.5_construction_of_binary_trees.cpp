//利用先序序列pres和中序遍历的字符串能构建这个二叉树
//下面还有序列化和反序列化
//上面是二叉树的基本算法

#include <iostream>
#include <vector>
#include <stack>
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



//先来实现用先序序列和中序序列还原二叉树
void CreayBTree1(BTree& bt,vector<char> pres,vector<char> ins)
{
	int n=pres.size();
	bt.r=CreatBTree11(pres,0,ins,0,n);
}
BTNode* CreatBTree11(vector<char>pres,int i,vector<char>ins,int j,int n)  
//这些参数分别是先序序列，这个子树的根节点在先序序列的位置。中序序列，这个子树的根节点在中序序列的位置，这个子树的全部结点数
{
if(n<=0) return NULL; 
char d =pres[i];  //取根节点的值
BTNode*b=new BTNode(d);  //创建根结点
int p=0;
while(ins[p]!=d) p++;   //循环在中序序列中找到根结点的位置
int k=p-j;  //左子树的结点个数k
b->lchild=CreatBTree11(pres,i+1,ins,j,k);  //递归构造左子树
b->rchild=CreatBTree11(pres,i+k+1,ins,p+1,n-k-1);  //递归构造右子树
return b;
}

//再来实现用后序序列和中序序列还原二叉树
void CreatBTree2(BTree& bt,vector<char> posts,vector<char> ins)
{
	int n=posts.size();
	bt.r=CreatBTree21(posts,0,ins,0,n);	
}
BTNode* CreatBTree21(vector<char>posts,int i,vector<char>ins,int j,int n)
{
if(n<=0) return NULL;
char d=posts[i+n-1];  //取后序序列尾元素即根植2d
BTNode* b=new BTNode(d);  //创建根结点（结点值为0）
int p=j;
while(ins[p]!=d) p++;  //在中序序列中找到索引p
int k=p-j;  //确定左子树中结点个数k
b->lchild=CreatBTree21(posts,i,ins,j,k);
b->rchild=CreatBTree21(posts,i+k,ins,p+1,n-k-1);
return b;
}


//所谓序列化，就是在空结点的地方填上'#'，这样就能实现只依靠先序序列/中序序列/后序序列就能构建二叉树
//下面的代码是先序遍历的序列化
string PreOrderSeq1(BTNode* b)
{
if(b==NULL) return "#";
string s(1,b->data);  //创建当前结点
s+=PreOrderSeq1(b->lchild);  //产生左子树的序列化序列
s+=PreOrderSeq1(b->rchild);  //产生右子树的序列化序列
return s;
}
string PreOrderSeq(BTree& bt)  //二叉树bt的序列化
{
return PreOrderSeq1(bt.r);
}
//下面这个是基于后序序列的序列化算法
string PostOrderSeq1(BTNode* b)
{
    if(b == NULL) return "#";  // 如果当前节点为空，则返回特定符号'#'表示空节点
    string s;  // 创建空字符串用于存储序列化结果
    // 递归序列化左子树
    s += PostOrderSeq1(b->lchild);
    // 递归序列化右子树
    s += PostOrderSeq1(b->rchild);
    // 将当前节点的数据值转换为字符串类型并拼接到序列化结果中
    s += b->data;
    return s;
}
string PostOrderSeq(BTree& bt)  // 二叉树bt的序列化
{
    return PostOrderSeq1(bt.r);
}


//序列化序列的反序列化
void CreateBTree3(BTree& bt,string s)
{
int i=0;
bt.r=CreateBTree31(s,i);
}
BTNode* CreateBTree31(string s,int& i)
//这个i相当于全局变量，因为需要借助这个i对这个序列进行遍历
{
if(i>s.length()) return NULL;  //i超界就直接返回
char d=s[i]; i++;  //取值
if(d=='#') return NULL;  //如果是#就说明是叶子结点
BTNode* b=new BTNode(d);  //创建根节点
b->lchild=CreateBTree31(s,i);
b->rchild=CreateBTree31(s,i);
return b;
}

//序列化适合构造结点值相同的二叉树