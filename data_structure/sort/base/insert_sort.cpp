//注意这些代码的排序结果都是递增排列
//插入排序
//插入排序的总体思路是把待排序区分为有序区和无序区 然后按照一定的顺序把无需求的东西插入到有序区中
//插入排序包括直接插入排序 折半插入排序和希尔排序等

#include <iostream>
#include <vector>

using namespace std;

//直接插入排序
//每次从无序区拿出第一个元素放在有序区的相应位置 进行n-1次排序
void InsertSort(vector<int>&R,int n)  //直接插入排序
{   
    for(int i=0;i<n;i++)
    {
        if(R[i]<R[i-1])  //如果无序区要添加的这个元素（第一个元素）位置不对
        {
            int tmp=R[i];  //取出这个元素
            int j=i-1;
            do
            {
                R[j+1]=R[j];
                j--;
            } while(j>=0 && R[j]>tmp);  //在没找到合适的插入位置之前 不断把这些元素后移
            R[j+1]=tmp;  //在j+1出插入R[i]
        }
    }
}
//我们可以通过定义cmp函数来简化函数 
//-> 这样的话我们只需要修改cmp中的大于号或者小于号就能把结果的递增修改为递减
bool cmp(int x,int y)
{
    if(x<y) return true;
    else    return false;
}
void InsertSort1(vector<int>& R,int n)
{
    for(int i=0;i<n;i++)
    {
        if(cmp(R[i],R[i-1]))
        {
            int tmp=R[i];
            int j=i-1;
            do
            {
                R[j+1]=R[j];
                j--;
            } while (j>=0 && !cmp(R[j],tmp));
            R[j+1]=tmp;
        }
    }
}
//时间复杂度
//最好->O(n) 最坏->O(n^2) 平均->O(n^2)


//折半插入排序
//寻找所要插入位置的思路是折半查找（因为有序区已经是递增序列了）
void BinInsertSort(vector<int>& R,int n)
{
    for(int i=1;i<n;i++)
    {
        if(R[i]<R[i-1])
        {
            int tmp=R[i];

            int low=0,high=i-1;
            while(low<=high)
            {
                int mid=(low+high)/2;  //取中间位置
                if(tmp<R[mid])
                    high=mid-1;
                else    
                    low=mid+1;  
            }
            for(int j=i-1;j>=high+1;j--)  //元素右移
                R[j+1]=R[j];
            R[high+1]=tmp;
        }
    }
}
//折半排序的平均时间复杂度为O(n^2)

//希尔排序
//希尔排序的思路是把所有数据进行分组，在每组内部进行直接插入排序 然后这个组越来越小
//每相隔d为一组 算法的最后一趟d=1进行直接插入排序 所以结果一定是正确的
void ShellSort(vector<int>& R,int n)  //取d1=n/2 di+1=d/2时的希尔排序算法
{
    int d=n/2;  //置初值
    while(d>0)
    {
        for(int i=d;i<n;i++)  //每相隔d的位置为一组，对每组元素进行直接插入排序
        {
            if(R[i]<R[i-d])
            {
                int tmp=R[i];
                int j=i-d;
                do
                {
                    R[j+d]=R[j];
                    j=j-d;  
                } while (j>=0 && R[j]>tmp);
                R[j+d]=tmp;
            }
        }
        d=d/2;  //减小增量
    }
}
//希尔排序的时间复杂度一般认为是n^1.58
//注意希尔排序是一种不稳定的排序方法（如果大小相同的元素不在同一组可能会发生位置交换）

