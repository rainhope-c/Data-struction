//线索二叉树
//叶子结点和一些其他结点存在空链域，利用这些链域存放在某种遍历次序下该结点的前驱结点和后继结点的指针，这些指针称为线索
//在原二叉链中增加了ltag和rtag两个标志域
#include <iostream>
#include <stack>

using namespace std;

struct BthNode  //线索二叉树的结点类型
{
    char data;  //存放结点值
    BthNode * lchild,* rchild;  //左右孩子结点或者线索的指针
    int ltag,rtag;  //左右标记，tag=0表明指针指向孩子，tag=1表示指针指向线索
    BthNode() {}  //默认构造函数
    BthNode(char d)  //重载构造函数
    {
        data=d;
        ltag=rtag=0;
        lchild=rchild=NULL;
    }
};

class ThreadTree  //中序线索二叉树
{
    BthNode *r;  //二叉树的根结点
    BthNode *root;  //线索二叉树的头结点指针
    BthNode *pre;  //用于中序线索化，指向中序前驱结点
public:
    ThreadTree()  //构造函数，用于初始化
    {
        r=NULL;  //初始二叉树为空树
        root=NULL;  //初始线索二叉树为空树
    }
    ~ThreadTree()  //析构函数
    {
    if(r!=NULL) DestoryBTree1(r);  //释放原二叉树的所有结点
    if(root!=NULL) delete root;  //释放root
    }
    void DestoryBTree1(BthNode* b)
    {
    if(b->ltag==0)  //b为左孩子，释放左子树
        DestoryBTree1(b->lchild);
    if(b->rtag==0)  //b为右孩子
        DestoryBTree1(b->rchild);
    delete b;  //删除b
    }


    void CreateBTree(string str)  //创建以r为根结点的二叉树存储结构
    {
    	stack<BthNode*>st;  //定义一个栈st
		BthNode* p;
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
				p = new BthNode(str[i]);  //创建一个新的结点
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

	void DispBTree()  //将二叉链转换为括号表达式并输出
	{
		DispBTreel(r);
	}
	void DispBTreel(BthNode* b)  //被DispBTree函数调用
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
    
    void CreateThread()  //创建以root为头结点的中序线索二叉树
    {
        root=new BthNode();  //创建头结点root
        root->ltag=0;   root->rtag=1;  //头结点的域置初值
        root->rchild=r;
        if(r==NULL)  //r为空树时
        {
            root->lchild=root;
            root->rchild->rchild=NULL;
        }
        else
        {
            root->lchild=r;
            pre=root;  //结点pre指向结点p的前驱结点，供添加线索使用
            Thread(r);  //中序遍历线索化二叉树
            pre->rchild=root;  //最后处理加入指向根结点的线索
            pre->rtag=1;
            root->rchild=pre;  //头结点右线索化
        }
    }
    void Thread(BthNode *&p)  //对结点p的二叉树中序线索化
    {
        if(p!=NULL)
        {
            Thread(p->lchild);  //左子树线索化
            if(p->lchild==NULL)  //前驱线索
            {
                p->lchild=pre;  //给结点p添加前驱线索
                p->ltag=1;
            }
            else p->ltag=0;
            if(pre->rchild==NULL)
            {
                pre->rchild=p;  //给节点pre添加后续线索
                pre->rtag=1;
            }
            else pre->rtag=0;
            pre=p;
            Thread(p->rchild);
        }
    }
    void ThInOrder()  //中序线索二叉树的中序遍历
    {
        BthNode *p=root->lchild;  //p指向根结点
        while(p!=root)
        {
            while(p!=root&&p->ltag==0)
                p=p->lchild;  //找到结点p
            cout<<p->data;  //访问结点p
            while(p->rtag==1&&p->rchild!=root)  //如果是线索就一直找下去
            {
                p=p->rchild;
                cout<<p->data;  //访问结点p
            }
            p=p->rchild;  //如果不是线索，转向访问其右子树            
        }
    }
};
