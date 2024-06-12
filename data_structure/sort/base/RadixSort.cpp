//基数排序 这个和前面的哈希表好像啊
#include <iostream>

using namespace std;

int const MAXR=100;
template <typename T>
struct LinkNode
{
    T data;  //存放数据元素
    LinkNode<T>* next;  //指向下一个节点的域

    LinkNode(): next(NULL){}  //构造函数
    LinkNode(T d):data(d),next{NULL} {}   //重载构造函数
};
template <typename T>
class LinkList
{
public:
    LinkNode<T>* head;
    LinkList():head(NULL){}
};
int geti(int key,int r,int i)  //求技术基数为r的正整数key的第i位
{
    int k=0;
    for(int j=0;j<=i;j++)
    {
        k=key%r;
        key=key/r;
    }
    return k;
}
//最低位优先基数排序算法
void RadixSort(LinkList<int>& L,int d,int r)
{
    LinkNode<int>* front[MAXR];  //创建链表队头数组
    LinkNode<int>* rear[MAXR];  //创建链表队尾数组
    LinkNode<int>* p,* t;
    for(int i=0;i<d;i++)  //从低位到高位循环
    {
        for(int j=0;j<r;j++)
            front[j]=rear[j]=NULL;  //初始化为NULL
        p=L.head->next;
        while(p!=NULL)
        {
            int k=geti(p->data,r,i);  //提取关键字第k个位并存在入第k个链队
            if(front[k]==NULL)  //第k个链队如果还没有元素
            {
                front[k]=p; rear[k]=p;
            }
            else
            {
                rear[k]->next=p;    rear[k]=p;
            }
            p=p->next;
        }
        LinkNode<int>* h=NULL;  //重新用h来手机全部结点
        for(int j=0;j<r;j++)
            if(front[j]!=NULL)  //如果第j个链队不是空的
            {
                if(h==NULL)
                {
                    h=front[j];
                    t=rear[j];
                }
                else
                {
                    t->next=front[j];
                    t=rear[j];
                }
            }
            t->next=NULL;
            L.head->next=h;
    }
}