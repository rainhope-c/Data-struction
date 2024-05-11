// 【问题描述】
//    给定两个n×n的矩阵a和b，求它们的积，结果矩阵中每个元素值模3。
// 【输入形式】
//    每个测试用例的第一行为n（1≤n≤800），接下来n行每行n个整数，表示矩阵a，第i行的第j个整数为aij，类似地，再接下来的n行为矩阵b（0≤aij，bij≤10^9）
// 【输出形式】
//    对于每个测试用例，输出n行每行n个整数表示a×b的结果。
// 【样例输入】
// 2
// 0 1
// 2 3
// 4 5
// 6 7
// 【样例输出】
// 0 1
// 2 1
// 【样例说明】
//      测试数据的文件名为in.txt
// 【评分标准】
//     该题目有10个测试用例，每通过一个测试用例，得10分。

//第一步读入数据
//第二步做乘法
//第三步输出

#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
#include <cmath>

using namespace std;

int main()
{
    ifstream infile("in.txt");
    int n;
    infile>>n;
    vector<vector<int>> ArrayA(n, vector<int>(n)); 
    vector<vector<int>> ArrayB(n, vector<int>(n));
    //创建相应两个数组A和B
    infile.ignore(numeric_limits<streamsize>::max(), '\n');  //忽略一下换行符
    //输入A
    for(int i=0;i<n;i++)
    {
    for(int j=0;j<n;j++)
    {
    infile>>ArrayA[i][j];
    }

    }
    //输入B
    for(int i=0;i<n;i++)
    {
    for(int j=0;j<n;j++)
    {
    infile>>ArrayB[i][j];
    }
    }


    //我的想法是再创建一个数组C来存储结果
    //发现的规律是C[i][j]=
    vector<vector<int>>ArrayC(n,vector<int>(n));
    for(int i=0;i<n;i++)
    {
    for(int j=0;j<n;j++)
    {
    int sum=0;
    for(int k=0;k<n;k++)
    {
    sum=(sum+ArrayA[i][k]*ArrayB[k][j])%3;
    }
    ArrayC[i][j]=sum;
    }
    }

    for(int i=0;i<n;i++)
    {
    for(int j=0;j<n;j++)
    {
    cout <<ArrayC[i][j]<<" ";
    }
    cout <<endl;
    }
    //抓取一下样例的数据
    // for(int i=0;i<n;i++)
    // {
    // for(int j=0;j<n;j++)
    // {
    // cout <<ArrayA[i][j]<<" ";
    // }
    // cout <<endl;
    // }
    // cout<<endl<<endl;
    // for(int i=0;i<n;i++)
    // {
    // for(int j=0;j<n;j++)
    // {
    // cout <<ArrayA[i][j]<<" ";
    // }
    // cout <<endl;
    // }
    //懂了，好像是溢出了
    return 0;
}