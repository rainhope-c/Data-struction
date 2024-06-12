//归并排序
//归并排序就是把待排序列分成几个小序列 对这个小序列进行排序后把他们归并起来
//主要的归并排序算法是二路归并算法、

#include <iostream>
#include <vector>

using namespace std;

void Merge(vector<int>& R,int low,int mid,int high)
//把R[low..mid]和R[mid+1..high]两个有序段归并为一个有序段R[low..high]
{
    vector<int> R1;
    R1.resize(high-low+1);  //设置R1的长度为high-low+1
    int i=low,j=mid+1,k=0;  //k是R1的下标，i j分别是第1/2段的下标
    while(i<mid && j<high)  //在第一段和第二段都没查找完的时候进行循环
    {
        if(R[i]<=R[j])
        {
            R1[k]=R[i];
            i++;    k++;
        }
        else{
            R1[k]=R[j];
            j++;    k++;
        }
    }
    while(i<=mid)  //把第一段的剩下部分复制到R1中
    {
        R1[k]=R[i];
        i++;    k++;
    }
    while(j<=high)  //把第二段的剩下复制到R1中
    {
        R1[k]=R[j];
        j++;  k++;
    }
    for(k=0,i=low;i<=high;k++,i++)  //把R1复制回R中
        R[i]=R1[k];
}
//一趟二路归并
void MergePass(vector<int>& R,int length)
{
    int n=R.size(),i;
    for(i=0;i+2*length-1<n;i+=2*length)  //归并length长的两个相邻子表
        Merge(R,i,i+length-1,i+2*length-1);
    if(i+length<n)  //余下两个子表 后者长度小于length
        Merge(R,i,i+length-1,n-1);  //归并这两个子表
}
//二路归并排序
void MergeSort1(vector<int>& R,int n)
{
    for(int length=1;length<n;length=2*length)  //进行log2n次归并
        MergePass(R,length);
}
//最好、最坏和平均时间复杂度都是O(nlog2n)
//注意空间复杂度是O(n)

//自顶向下的二路归并
void MergeSort2(vector<int>& R,int n)
{
    _MergeSort2(R,0,n-1);
}
void _MergeSort2(vector<int>& R,int s,int t)  
{
    if(s>=t) return;
    int m=(s+t)/2;
    _MergeSort2(R,s,m);
    _MergeSort2(R,m+1,t);
    Merge(R,s,m,t);
}