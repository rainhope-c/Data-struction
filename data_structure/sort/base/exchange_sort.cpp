//交换排序
//交换排序的总体思路是当找到两个元素反序时交换两个元素
//交换排序包括冒泡排序和快速排序

#include <iostream>
#include <vector>

using namespace std;
//冒泡排序寻找这两个进行比较的元素的思路为相邻的元素
//逐一比较相邻的两个元素 如果反序就交换 进行n-1次 并且每次都少比较一组(执行k次循环后前k个元素就已经是正确顺序了)
void BubbleSort(vector<int>R,int n)
{
    int i,j;
    int tmp;
    for(int i=0;i<n-1;i++)
    {
        for(j=n-1;j>i;j--)  //这个是从后面冒泡的
            if(R[j]<R[j-1])
            {
                tmp=R[j];
                R[j]=R[j-1];
                R[j-1]=tmp;
            }      
    }
}
//可以优化的部分是如果在一次循环中没有出现元素交换就说明顺序已经正确了 就可以直接结束
void BubbleSort1(vector<int>& R,int n)
{
    for(int i=0;i<n-1;i++)
    {
        bool exchange=0;
        for(int j=n-i;i>i;j--)
            if(R[j]<R[j-1])
            {
                swap(R[j],R[j-1]);
                exchange=1;
            }
        if(!exchange)   return ;  //如果没进行交换就直接结束了
    }
}
//最好->O(n) 最坏->O(n^2) 平均->O(n^2)

//快速排序
//有点二叉排列树的感觉 思路是每次选择一个基准元素 进行快速排序后这个基准元素左边是比它小的 右边是比它大的
//然后对左右序列分别再次进行快速排序
//要实现把基准元素放在中间就需要一个划分算法 这个花粉算法又有几种实现方法
int Partiton1(vector<int> & R,int s,int t)  //划分算法
{
    int base =R[s];  //取所要排列序列的首元素为基准
    int i=s,j=t;  //i/j分别指向首元素和尾元素
    while(i<j)
    {
        while(i<j && R[j]>base)
            j--;  //向后遍历 找到第一个小于或等于base的元素
        while(i<j &&R[j]<=base)
            i++;  //向前遍历 找到第一个大于base的元素
        if(i<j)
            swap(R[i],R[j]);  //将R[i]和R[j]交换
    }
    swap(R[s],R[j]);  //将基准R[s]和R[i]进行交换
    return i;
}
int Partiton1_1(vector<int> & R,int s,int t)  //划分算法1的改进版本
{
    int base=R[s];  //以首元素作为基准
    int i=s,j=t+1;  //j从t+1开始
    while(i<j)
    {
        j--;  //先移动避免重复比较 j初始化为t+1然后再减一下
        while(R[j]>base && i<j)
            j--;
        i++;  //先移动避免重复比较
        while(R[i]<=base && i<j)
            i++;
        if(i<j)  //i<j时交换
            swap(R[i],R[j]);  //保证i左侧小于或等于base j右侧大于base
    }
    swap(R[s],R[j]);  //交换肌醇和R[j]
    return j;
}
int Partiton2(vector<int> & R,int s,int t)  //划分算法
{
    int i=s,j=t;  //以表首元素为基准
    int base=R[s];
    while(j>i)
    {
        while(j>i && R[j]>base)
            j--;  //从后面找到第一个小于base的元素
        if(j>i)
        {
            R[i]=R[j];  //R[j]前移覆盖R[i]
            i++;
        }
        while(i<j && R[i]<=base)
            i++;  //从前往后找到第一个大于base的元素
        if(i<j)
        {   
            R[j]=R[i];  //R[i]后移覆盖R[j]
            j--;
        }
    }
    R[i]=base;  //基准归位
    return i;
}
int Partiton3(vector<int> & R,int s,int t)  //划分算法
{
    int i=s,j=s+1;
    int base=R[s];
    while(j<=t)
    {
        if(R[j]<=base)  //找到小于或者等于基准的元素R[j]
        {
            i++;  //扩大小于或等于base的元素区间
            if(i!=j)
                swap(R[i],R[j]);
        }
        j++;
    }
    swap(R[s],R[i]);
    return i;
}

//课下完善吧 划分算法老师都没讲

void _QuikSort(vector<int>& R,int s,int t)  //对R[s..t]进行快速排序
{
    if(s<t)
    {
        int i=Partiton1(R,s,t);   //这里可以任选划分算法
        _QuikSort(R,s,i-1);  //左子表
        _QuikSort(R,i+1,t);  //右子表
    }
}
void QuikSort(vector<int>& R,int n)
{
    _QuikSort(R,0,n-1);
}
//最好->O(nlog2n) 最坏->O(n^2) 平均->O(nlog2n)