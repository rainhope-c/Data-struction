#include <iostream>
using namespace std;
//顺序表的存储结构
const int initcap=5;  //顺序表的初始容量为5
template <typename T>
class SqList  //顺序表类模板
{
public:
    T* data;  //存放顺序表元素空间的指针
    int capacity;  //顺序表的容量
    int length;  //存放顺序表的长度

//构造函数
SqList()
{   data=new T[initcap];  //分配initcap大小的内存空间
    capacity=initcap;  //初始化容量
    length=0;  //初始时length等于0
}
//复制构造函数(深层复制)
SqList(const SqList<T>& s)
{
    capacity=s.capacity;  //复制容量
    length =s.length;  //复制长度
    data=new T[capacity];  //分配新的内存空间
    for(int i=0;i<length;i++)
        data[i]=s->data[i];  //逐一复制元素
}
//析构函数
~SqList()
{
    delete[] data;  //释放内存空间
}

//改变顺序表的容量为newcap
void recap(int newcap)  
{
    if(newcap<=0)  return;
    T* olddata=data;  //保存原始数据
    data=new T[newcap];  //开辟新的内存空间
    capacity=newcap;  //更新容量
    for(int i=0;i<length;i++)
        data[i]=olddata[i];  //元素复制
    delete [] olddata;  //释放原来的内存空间
}
//整理建立顺序表
void CreateList(T a[],int n)  //由数组a中元素整体建立顺序表
{
    for(int i=0;i<n;i++)
    {
        if(length==capacity)  //如果是长度等于容量了
            recap(2*length);  //扩大容量
        data[length]=a[i];  //数据存入
        length++;  //元素个数加一
    }

}
//将元素e添加到线性表末尾
void Add(T e)
{
    if (length==capacity)// 满容量时扩容
        recap(2*length);
    data[length]=e;  //添加元素e
    length++;
}
//求线性表的长度
int Getlength()
{
    return length;
}
//求线性表中序列为i的元素
bool GetElem(int i,T& e)
{
    if(i<0||i>length)
        return false;  //参数错误
    e=data[i];  //取出元素
    return true;
}
//设置线性表中序列为i的元素
bool SetElem(int i,T e)
{    if(i<0||i>length)
        return false;  //参数错误
    data[i]=e;  //取出元素
    return true;
}
//求线性表中第一个值为e的元素
int GetNo(T e)
{
    int i=0;
    while(i<length&&data[i]!=e)
        i++;  //遍历查找
    if(i>=length)   return -1;  //没找到
    else return i;  //找到了
}
//在线性表中插入e作为第i个元素
bool Insert(int i,T e)
{
    if(i<0||i>length)   return false; //参数错误
    if(length==capacity) recap(2*length);  //扩容
    for(int j=length;j>i;j--)
        data[j]=data[j-1];   //data[i]后每个元素都向后移一位
    data[i]=e;  //插入元素e
    length++;  //长度增加1
    return true;
}
//在线性表中删除第i个元素
bool Delete(int i)
{
    if(i<0||i>length)   return false;
    for(int j=i;j<length-1;j++)
        data[j]=data[j+1];  //data[i]后每个元素向前移动一次
    length--;
    if(capacity>initcap && length<=capacity/4)
        recap(capacity/2);  //满足缩容条件就容量减半
    return true;
}
//输出线性表所有元素
void DispList()
{
    for(int i=0;i<length;i++)
        cout<<data[i]<<" ";
    cout << endl;
}

};
int main()
{
    int i,e;
    SqList<int> L;
    cout<<"常见整数顺序表L"<<endl;
    L.Insert(0,2); 
    L.Insert(1,3); 
    L.Insert(2,1); 
    L.Insert(3,5); 
    L.Insert(4,4);
    L.Insert(5,1);  //添加元素
    L.Add(8);
    cout<<"顺序表L：";  L.DispList();
    cout<<"长度："<<L.length<<" 容量："<<L.capacity<<endl;
    i=3; L.GetElem(i,e);
    cout<<"序号为"<<i<<"的元素为："<<e<<endl;
    return 0;  
}
