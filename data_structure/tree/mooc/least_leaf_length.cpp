// 假设二叉树中每个结点值为单个字符，采用二叉链存储结构存储。设计一个算法求二叉树bt的最小枝长。所谓最小枝长是指的是根结点到最近叶子结点的路径长度。
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
			return max(Heightl(b->lchild), Heightl(b->rchild)) + 1;
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

    //求最短枝长
	int leastlengthl(BTNode* b)  
	{
		if (b == NULL)  //空树的高度是0
			return 0;
		else
			return min(leastlengthl(b->lchild), leastlengthl(b->rchild)) + 1;
	}
    int leastlength()
	{
		return leastlengthl(r);
	}
};




int main()
{
    string tem("A(B(D(,G),C(E,F)),I)");
    BTree target;
    target.CreatBTree(tem);
	cout<<"创建树为："<<endl;
    target.DispBTree();
    cout<<endl;
    int lea=target.leastlength();
    int max=target.Height();
    cout<<"这棵树的高度为："<<max<<endl;
    cout<<"最短枝长为："<<lea<<endl;

    return 0;
}