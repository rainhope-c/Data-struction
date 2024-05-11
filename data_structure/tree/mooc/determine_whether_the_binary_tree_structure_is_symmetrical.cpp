//假设二叉树采用二叉链存储结构，设计一个算法判断一棵二叉树bt是否对称。所谓对称是指其左右子树的结构是对称的。
//怎么设计这个算法呢？

//将二叉树的根节点的左右子树序列化，然后比较序列化后的遍历结果



//二叉树的基本算法

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
	BTree(BTNode* rr)  //构造函数，创建一个空树
	{
		r = rr;
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
	// void DestoryBTrer(BTNode* b)
	// {
	// 	if (b != NULL)
	// 	{
	// 		DestoryBTrer(b->lchild);
	// 		DestoryBTrer(b->rchild);
	// 		delete b;
	// 	}
	// }
	// ~BTree()
	// {
	// 	DestoryBTrer(r);
	// 	r = NULL;
	// }
};

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
//后序遍历序列化

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


bool compstr(string lstring,string rstring)
{
int lsl=lstring.length(); int rsl=rstring.length();
if(lsl!=rsl)
	return false;  //长度都不一样结果肯定不同
for(int i=0;i<lsl;i++)
{
if(lstring[i]!=lstring[i]&&(lstring[i]=='#'||rstring[i]=='#'))  //如果两个不同并且其中一个是#，则不同
	return false;
}
return true;
}


int main()
{
	string test("A(B(D(H,I),E(,G)),C(F(K,),G(L,M)))");
	BTree tree;
	tree.CreatBTree(test);
	BTree lchildt,rchildt;
	lchildt=BTree(tree.r->lchild);
	rchildt=BTree(tree.r->rchild);
	// lchildt.DispBTree();
	// rchildt.DispBTree();
	string re1=PreOrderSeq(lchildt);	
	string re2=PostOrderSeq(rchildt);//想办法把re2反过来就行
	reverse(re2.begin(), re2.end());	
	bool isSame=compstr(re1,re2);
	if(isSame)
		cout <<"1";
	else
		cout<<"0";
    return 0;
}