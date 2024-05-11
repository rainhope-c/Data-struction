//第一步，把输入从文件中得出，输入m和n
//第二步，得到m的n进制数，保存在一个数组中（动态数组好），num[0]是最高位
//第三步，用一个for循环把这个数组输出，注意输出间隔是空格
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

//思路是求余
//f(m)==0  跳出循环
//f(m)!=0 取余，把这个余数存储在数组中

//先不用递归完成这个任务
vector<int> f(int m,int n)
{
vector<int>nums(1000);
int i=0;
while(m!=0)
{
nums[i]=m%n;
m=m/n;
i++;
}
nums.resize(i);
return nums;
}
//接下来想办法用递归完成任务
// int NSC(int m,int n,ofstream file)
// {
// int x=m%n;
// m=m/n;
// file<<x<<" ";
// if(m!=0)
// m=NSC(m,n,file);
// else if(m==0)
// return 0;

// }
void NSC(int m, int n, ofstream& file) {
    if (m != 0) {
        int x = m % n;
        m = m / n;
        NSC(m, n, file);
        file << x << " ";
    }
    else return; 
}

void printarray(vector<int>a)
{
for(int i=0;i<a.size();i++)
cout<<a[a.size()-i-1];
return ;
}


int main()
{
//先完成第一步，把文件中的内容输入
ifstream infile;
infile.open("in.txt");
ofstream outfile;
outfile.open("out.txt");
int m,n;
infile>>m>>n;

NSC(m,n,outfile);
// vector <int> nums;
// nums=f(m,n);

// for(int i=0;i<nums.size();i++)
// outfile<<nums[nums.size()-i-1]<<" ";

// for(int i=0;i<nums.size();i++)
// cout<<nums[nums.size()-i-1]<<" ";

return 0;
}