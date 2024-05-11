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



int main()
{
    string tem("A(B(D(,G),C(E,F)))");
    BTree target;
    target.CreatBTree(tem);
	cout<<"创建树为："<<endl;
    target.DispBTree();
    cout<<endl;
    return 0;
}