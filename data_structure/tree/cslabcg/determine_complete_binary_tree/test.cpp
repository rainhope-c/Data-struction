// 【问题描述】
//     假设二叉树中的每个结点值为单个整数，采用二叉链结构存储，设计算法判断给定的二叉树是否是完全二叉树。假定每棵二叉树节点不超过2000个。
// 【输入形式】
//     每个测试是一颗二叉树的括号表示法字符串
// 【输出形式】
//      如果是完全二叉树，输出“1”；如果不是完全二叉树，输出“0”
// 【样例输入】
//     1(2(4,5),3)
// 【样例输出】
//      1
// 【样例说明】
//    测试数据的文件名为in.txt                                                      【评分标准】
//    该题目有10个测试用例，每通过一个测试用例，得10分。

//在CSDN上看到一个很好的思路是，层次遍历这个二叉树，当开始出现空结点后看下一个遍历结果

//二叉树的基本算法

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
				int d = 0;
				char ch=str[i];
				while (ch >= '0' && ch <= '9')
				{
					d = 10 * d + (ch - '0');
					i++;
					ch = str[i];
				}
				i--;
				p = new BTNode(d);  //创建一个新的结点
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

};



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
// bool isBaohe(BTNode*node)
// {
// if(node->lchild!=NULL&&node->rchild!=NULL)  //如果这个结点的左右孩子都健在，就饱和(叶子结点能不能当成饱和结点处理？)
// 	return true;
// return false;  //否则不饱和
// }
// bool isCompleteTree(BTree& bt)  //这个函数用于判断是否为完全二叉树
// {
// //反正思路就是找到第一个不饱和结点
// //这个结点之后的结点都必须没有孩子
// //这个结点只能是有左孩子没有右孩子或者没有孩子
// //这么看依然是层次遍历的思路
// if(bt.r==NULL)
// 	return true;  //空树直接返回
// BTNode* p;
// queue<BTNode*> qu;  //定义一个队列
// qu.push(bt.r);  //根节点入队

// bool findtarget=0;  //标记有没有找到第一个不饱和的结点

// while(!qu.empty())  //当队不空就一直循环
// {
// p=qu.front();  qu.pop();  //去除队列最前面的结点p
// //在这一部分进行操作
// if(isBaohe(p))  //如果当前结点饱和
// {if(findtarget)  //如果前面已经找到不饱和结点了
// 	return false;  //那就不是完全二叉树
// }
// //如果前面没有找到不饱和结点
// //那这个就是第一个不饱和结点
// //判断这个不饱和结点是否满足
// //如果只有右孩子那就不对
// else{  //如果当前结点不饱和，如果前面没有找到其他不饱和结点
// //并且这个结点满足完全二叉树的条件，那这个节点就是第一个不饱和结点
// if(p->lchild!=NULL&&p->rchild==NULL)
// 	return false;
// if(findtarget)  //如果前面找到了不饱和结点
// //那这个结点只能是叶子结点
// {
// 	if(p->lchild!=NULL||p->rchild!=NULL)
// 		return false;
// }
// if(!findtarget)
// 	findtarget=1;  //表示找到不饱和结点了

// }
// if(p->lchild!=NULL)  //当有左孩子时将其进队
//  qu.push(p->lchild);
// if(p->rchild!=NULL)  //当有右孩子时将其进队
//  qu.push(p->rchild);
// }
// return true;
// }

//判断是否为完全二叉树---》用层序遍历的思想一层一层找不饱和节点，也就是需要借队列
bool isCompleteTree(BTree& bt)
{
    if(bt.r==NULL)
    {
        return true;
    }
    queue<BTNode*> qu;
    qu.push(bt.r);
    //是叶子节点或者只有左孩子的节点，也就是这两种不饱和的节点出现之后还需要判断后面的节点是否有孩子
    // 如果只有右孩子的不饱和节点一定不是完全二叉树
    // 一开始让不饱和节点置为false，找到之后设为true
    bool isLeafOrLeft=false;
    while(!qu.empty()) {
        BTNode* p = qu.front(); qu.pop();
        //得到第一个不饱和节点之后
        if (isLeafOrLeft) {
             //从第一个不饱和结点之后，所有节点不能有孩子
            if (p->lchild!=NULL || p->rchild!=NULL) {
                return false;
            }
       }//没找到不饱和节点就继续按照层序遍历寻找
       else {
            //P节点左右孩子都存在
            if (p->lchild!=NULL&&p->rchild!=NULL) {
                qu.push(p->lchild);
                qu.push(p->rchild);
            } else if (p->lchild!=NULL) {
                //只有左孩子:找到不饱和节点，标记isLeafOrLeft=true
                qu.push(p->lchild);
                isLeafOrLeft = true;
            } else if (p->rchild!=NULL) {
                //只有右孩子:找到不饱和节点，一定不是完全二叉树，返回false
                return false;
            } else {
                //cur是叶子节点：找到不饱和节点：标记isLeafOrLeft=true
                isLeafOrLeft = true;
            }
        }
    }
    return true;
}
//搞了一上午问题在于这个树的结点不是char而是int...



int main()
{
    ifstream infile("in.txt");
    string tem;
    getline(infile,tem);
    BTree target;
    target.CreatBTree(tem);
	// cout<<"创建树为："<<endl;
    // target.DispBTree();
	// cout<<endl;
    bool is=isCompleteTree(target);
    if(is)  cout<<"1";
    else    cout <<"0";
    return 0;
}