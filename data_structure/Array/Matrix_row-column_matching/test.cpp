//第一步是从“in.txt”中输入
//第二步是进行匹配处理
//第三步是把结果输出

#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

using namespace std;

int main()
{
    ifstream infile;
    infile.open("in.txt");
    ofstream outfile;
    outfile.open("out.txt");

    //输入部分
    if(!infile||!outfile)
    {
    cout<<"打开失败";
    return 0;
    }
    int m,n=0;

    infile>>m>>n;  
    infile.ignore(numeric_limits<streamsize>::max(), '\n');  //忽视换行符
    vector<vector<int>> array(m, vector<int>(n));  //创建一个m*n的整型数组
    //接下来想办法把这个数组输入
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            int x=0;
            infile>>x;
            array[i][j]=x;
        }
        //每次输入结束一行之后都需要再重新忽视换行符
        infile.ignore(numeric_limits<streamsize>::max(), '\n');  //忽视换行符
    }

    //现在应该是已经完成输入了
    //接下来求出所有行和所有列的和
    //我的想法是一个数组存储所有行的和 另一个数组存储所有列的和 然后寻找它们相等的有多少
    vector<int>sumOfRow(m);  //行的和
    vector<int>sumOfColumn(n);  //列的和
    //先求行的和
    for(int i=0;i<m;i++)
    {
        int sum=0;
        for(int j=0;j<n;j++)
        {   
            sum+=array[i][j];  //求出这一行的所有数的和
        }
        sumOfRow[i]=sum;  //把这个和存储起来
    }
    //再求列的和，思路同上
    for(int i=0;i<n;i++)
    {
        int sum=0;
        for(int j=0;j<m;j++)
        {
            sum+=array[j][i];
        }
        sumOfColumn[i]=sum;
    }

    //应该是求出来了
    //接下来求相等的值
    int cnt=0;  //这个计数从0开始
    //用全部的行的和全部的列的和进行比较
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(sumOfRow[i]==sumOfColumn[j])
                cnt++;
        }
    }
    //应该是没问题
    //接下来是结果输出
    outfile<<cnt;

    return 0;

}

