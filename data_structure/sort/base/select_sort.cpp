//选择排序是每次从无序区中选择出最小元素防止到全局有序区中，只需要放在最后就行了
//选择排序主要有简单选择排序和堆排序两种

#include <iostream>
#include <vector>

using namespace std;

//简单选择排序 
//简单选择排序就是逐一比较找出最小元素
void SelectSort(vector<int>& R,int n)
{
    for(int i=0;i<n-1;i++)
    {
        int minj=i;
        for(int j=i+1;j<n;j++)  //在当前无序区R[i..n-1]中选最小元素R[minj]
            if(R[j]<R[minj])
                minj=j;  //minj为最小元素的下标
        if(minj!=i)
            swap(R[i],R[minj]);  //如果不是无序区的首元素就交换
    }
}
//最好、最坏、平均时间复杂度->O(n^2)

//堆排序 这是重头戏
//堆排序是利用堆的方法找到最大的元素然后放在有序区中
//首先什么是堆？堆可以理解为一种完全二叉树 这个二叉树是顺序存储的 我们的这个数组序列实际上是根据层次遍历得到的
//大根堆和小根堆的概念 我们是需要知道根据大根堆我们可以很容易进行选择排序
//实际上整个堆排序分为了两大块——根据序列建立大根堆+根据大根堆得到递增序列 
//那我们如何建立堆呢？实际上是利用“筛选”方法建立堆
//筛选方法又分为向上筛选和向下筛选两种
//首先来看自顶向下筛选——从根结点R[low]开始向下依次查找较大的孩子结点构成一个序列，使其中除了根结点之外的其他元素的子序列恰好是递减的
void siftdown(vector<int>& R,int low,int high)
//R[low..high]的自顶向下筛选
{
    int i=low;
    int j=2*i+1;  //R[j]是R[i]的左孩子
    int tmp=R[i];  //tmp临时保存根结点
    while(j<=high)  //只对R[low..high]进行筛选
    {
        if(j<high && R[j]<R[j+1])
            j++;  //如果右孩子较大就指向右孩子
        if(tmp<R[j])  //tmp的孩子更大
        {
            R[i]=R[j];  //将R[j]调整到双亲的位置
            i=j;    j=2*i+1;  //修改i和j的值以便进行继续筛选
        }
        else    break;  //如果孩子比较小就筛选结束
    }
    R[i]=tmp;  //原根结点放在最终位置
}
//向上筛选就是从某个叶子结点开始向上筛选
void siftup(vector<int>& R,int j)  //从叶子结点j向上筛选
{
    int i=(j-1)/2;  //i指向R[j]的双亲
    while(true)
    {
        if(R[j]>R[i])  //如果孩子比较大
            swap(R[i],R[j]);  //交换
        if(i==0)    break;  //到达根结点时结束
        j=i;    i=(j-1)/2;  //继续向上调整
    }
}
//下面是堆排序算法
void HeapSort(vector<int>& R,int n)  //堆排序
{
    for(int i=n/2-1;i>=0;i--)  //从最后一个分支结点开始循环建立初始堆
        siftdown(R,i,n-1);  //对R[i..n-1]进行筛选
    for(int i=n-1;i>0;i--)  //进行n-1趟排序 每一趟后无序区元素个数减一
    {
        swap(R[0],R[i]);  //对无序区中尾元素R[0]交换 扩大有序区
        siftdown(R,0,i-1);  //对剩下的无序区继续进行筛选
    }
}
//在堆初始化和根据大根堆进行排序这两个过程的时间复杂度都是O(nlog2n)，这个算法的时间复杂度在最好、最坏和平均情况下也都是O(nlog2n)

//下面是堆数据类型（优先队列）
template <typename T>
class Heap
{
    int n;  //堆中元素个数
    vector<T> R;  //用数组来存放堆中元素
public:
    Heap():n(0) {}  //默认构造函数
    void siftDown(int low,int high)  //R[low..high]的自顶向下筛选
    {
        int i=low;
        int j=2*i+1;  //R[j]是R[i]的左孩子
        T tmp =R[i];  //tmp临时保存根结点
        while(j<=high)
        {
            if(j<high && R[j]<R[j+1])
                j++;  //如果右孩子较大 就把j指向右孩子
            if(tmp<R[j])  //如果tmp的孩子比较大
            {
                R[i]=R[j];  //把R[j]调整在双亲的位置上
                i=j;    j=2*i+1;  //修改i和j以便继续向下筛选
            }
            else break;
        }
        R[i]=tmp;  //原节点放在最终位置
    }

    void siftUp(int j)
    {
        int i=(j-1)/2;  //i指向R[j]的双亲
        while(true)
        {
            if(R[i]<R[j])  //如果孩子比较大就交换
                swap(R[i],R[j]);
            if(i==0)    break;  //到达根结点的时候结束
            j=i;    i=(j-1)/2;  //继续向上调整
        }
    }

    //插入元素的思路是直接添加到序列尾部然后进行向上筛选
    void push(T e)
    {
        n++;  //元素数加一
        if(R.size()>=n)  //如果R中有1多余空间
            R[n-1]=e;
        else    R.push_back(e);  //如果没有多余空间
        if(n==1)    return ;   //e是根结点
        int j=n-1;  siftUp(j);  //从叶子结点R[j]向上筛选
    }
    
    //删除运算算法 堆只能删除非空堆的堆顶元素，即最大元素
    T pop()
    {
        if(n==1)
        {
            n=0; return R[0];  //如果原来只有一个元素 直接删除就行了
        }
        T e=R[0];  //取出堆顶的元素
        R[0]=R[n-1];  //用尾元素覆盖R[0]
        n--;  //元素个数减一
        siftDown(0,n-1);  //重新筛选
        return e;  //返回这个元素
    }

    //取出堆顶元素
    T gettop()
    {   return R[0];
    }

    //判断堆是否为空
    bool empty()
    {   return n==0;   }
};
