#include <vector>
using namespace std;

//双亲存储结构
struct PNode  //结构单元
{
	char data;  //存放结点值，假设是char类型
	int parent;  //存放双亲索引

	PNode(char d, int p)  //构造函数
	{
		data = d;
		parent = p;
	}
};
//利用双亲存储结构求双亲比较容易，但是求孩子比较苦难，需要遍历整个树

//求指定索引为i的结点的层次
int Level(vector<PNode>t, int i)
{
	if (i < 0 || i >= t.size())return 0;
	int cnt = 1;
	while (t[i].parent != -1)  //没有达到根节点的时候循环
	{
		cnt++;
		i = t[i].parent;  //移动到双亲结点
	}
	return cnt;
}


//孩子链存储结构
//需要存储每个结点所有的孩子结点，用vector存储
struct SNode
{
	char data;  //结点值
	vector<SNode*>sons;  //指向孩子结点指针的向量

	SNode() {}  //构造
	SNode(char d) :data(d) {}  //重载构造
};
//求树的高度
int Height(SNode* t)
{
	if (t == NULL)return 0;
	int maxsh = 0;
	for (int i = 0;i < t->sons.size();i++)  //遍历所有子树
	{
		int sh = Height(t->sons[i]);  //求子树t->sons[i]的高度
		maxsh = max(maxsh, sh);  //求所有子树的最大高度
	}
	return maxsh + 1;
}

//长子兄弟链存储结构
//需要三个域：数据域，指向长子的指针域，指向该节点下一个兄弟的兄弟指针域
struct EBNode
{
	char data;  //结点的值
	EBNode* brother;  //指向兄弟
	EBNode* eson;  //指向长子结点
	EBNode() :brother(NULL), eson(NULL) {}   //构造函数
	EBNode(char d)  //重载构造函数
	{
		data = d;
		brother = eson = NULL;
	}
};
//求高度
int HeightEB(EBNode* t)
{
	if (t == NULL) return 0;  //空树的高度是0
	int maxsh = 0;  
	EBNode* p = t->eson;  //p指向t结点的长子
	while (p != NULL)
	{
		EBNode* q = p->brother;  //q临时保存结点q的兄弟结点
		int sh=HeightEB(p);  //递归求节点p的子树的高度
		maxsh = max(maxsh, sh);  //求结点t的所有子树的最大高度
		p = q;
	}
	return maxsh + 1;
}

