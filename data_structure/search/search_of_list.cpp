//线性表的查找
//线性表是顺序存储结构 不适合数据修改 因此顺序表是静态查找表
//主要有三种方法——顺序查找、折半查找和分块查找

#include <iostream>
#include <vector>

using namespace std;

//首先是顺序查找 就是直接遍历
int SeSearch1(vector<int>& R,int k)
{
    int n=R.size();  //元素个数
    int i=0;
    while(i<n &&R[i!=k])
        i++;  //从前往后查找
    if(i>=n) return -1;  //没找到就返回-1
    else return i;
}
int SeSearch2(vector<int>& R,int k)
{
    int n=R.size();
    R.push_back(k);  //末尾添加一个哨兵
    int i=0;
    while(R[i]!=k) i++;  //遍历查找
    if(i==n) return -1;
    else return i;
}

//然后是折半查找 用于顺序表的查找
int BinSearch1(vector<int>& R,int k)
{
    int n=R.size();
    int low=0,high=n-1;  //查找的范围
    while(low<=high)  //当前区间非空的时候
    {
        int mid=(low+high)/2;  //找到中间位置
        if(k==R[mid])   return mid;  //找到了就返回
        else if(k<R[mid])  //如果比中间的小就在左边查找
            high=mid-1;
        else    low=mid+1;  //如果比中间的大就在右边找
    }
    return -1;  //如果没找到就返回-1
}
int BinSearch2(vector<int>&R,int k)  //递归的算法
{
    return BinSearch21(R,0,R.size()-1,k);
}
int BinSearch21(vector<int>R,int low,int high,int k)
{
    if(low<=high)
    {
        int mid=(low+high)/2;  //查找区间的中间位置
        if(k==R[mid])   return mid;  //查找成功就返回
        else if(k<R[mid])    return BinSearch21(R,low,mid-1,k);  //递归调用
        else    return BinSearch21(R,mid+1,high,k);
    }
    else    return -1;
}

//最后是索引查找

//索引查找指在存储数据的同时再存储一个索引表 在查找的时候先查找关键词找到相应的地址然后再地址内部寻找
