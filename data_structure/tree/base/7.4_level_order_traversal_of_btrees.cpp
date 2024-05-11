//二叉树的层次遍历
//层次遍历是根节点->左子树->右子树->左子树的左子树->左子树的右子树->右子树的左子树->右子树的右子树->....
//发现这个过程有点像队列
//根节点入队->根结点出队->根结点的左右子树入队....这是一个递归遍历队列的过程

//我直接把这些基本算法复制粘贴
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
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

//二叉树的层次遍历
void LevelOrder(BTree& bt)  //二叉树的层次遍历
{
BTNode* p;
queue<BTNode*> qu;  //定义一个队列
qu.push(bt.r);  //根节点入队

while(!qu.empty())  //当队不空就一直循环
{
p=qu.front();  qu.pop();  //去除队列最前面的结点p
cout<<p->data;  //访问结点p
if(p->lchild!=NULL)  //当有左孩子时将其进队
 qu.push(p->lchild);
if(p->rchild!=NULL)  //当有右孩子时将其进队
 qu.push(p->rchild);
}
}

//层次遍历的应用
//利用层次遍历求第k层的结点数
struct QNode  //队列元素类
{
int lev;  //结点的层次
BTNode* node;  //节点指针
QNode(int l,BTNode* p)
{
lev=l;
node =p;
}
};
//解法一 
int KCount1(BTree& bt,int k)
{
int cnt=0;  //cnt表示第k层结点数
queue<QNode> qu;  //定义一个队列
qu.push(QNode(1,bt.r));  //根节点入队
while(!qu.empty())  //队不空就循环
{
QNode p=qu.front();  qu.pop();  //出队一个结点
if(p.lev>k)
 return cnt;  //当入队的这个结点的高度大于k，表明k层已经完全遍历了，直接返回结果
if(p.lev==k)
 cnt++;
else{  //当前结点层次小于k
if(p.node->lchild!=NULL)  //有左孩子时左孩子进队
 qu.push(QNode(p.lev+1,p.node->lchild));
if(p.node->rchild!=NULL)  //当有右孩子时右孩子进队
 qu.push(QNode(p.lev+1,p.node->rchild));
}
}
return cnt;
}
//解法二
//利用的是最右边的根结点的右子树是下一层的最后一个结点进行遍历
int KCount2(BTree& bt,int k)
{
int cnt=0;  //cnt表示第k层结点个数
queue<BTNode* >qu;  //定义一个队列qu
int curl=1;   //用这个curl来表示当前
BTNode* last=bt.r,*p,*q;  //第一层最右结点
qu.push(bt.r);  //根结点进队
while(!qu.empty())  //队不空循环
{
if(curl>k)  //当层号大于k时返回cnt，不再继续
 return cnt;
p=qu.front(); qu.pop();  //出队一个结点
if(curl==k)
 cnt++;
if(p->lchild!=NULL)  //有左孩子时进队
{q=p->lchild;
qu.push(q);
}
if(p->rchild!=NULL)  //有右孩子时进队
{q=p->rchild;
qu.push(q);
}
if(p==last)  //当了last就是到底了，这个层次的结点处理完毕
{
last=q;  //让last指向下一层的最右节点
curl++;
}
}
return cnt;
}
//解法三
int KCount3(BTree& bt,int k)
{
if(k<1) return 0;
queue<BTNode* >qu;  //定义一个队列
int curl=1;  //当前层次从1开始
qu.push(bt.r);  //根节点入队
while(!qu.empty())
{
if (curl==k)
    return qu.size();
int n=qu.size();
for(int i=0;i<n;i++)  //对当前层次的结点进行遍历
{
BTNode* p=qu.front(); qu.pop();
if(p->lchild!=NULL)
    qu.push(p->lchild);
if(p->rchild!=NULL)
    qu.push(p->rchild);
}
curl++;
}
return 0;
}