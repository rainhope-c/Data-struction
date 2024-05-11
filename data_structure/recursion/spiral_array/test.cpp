// 【问题描述】
// 给定一个正整数n，生成一个包含1到n^2所有元素，且元素按顺时针顺序螺旋排列的正方形矩阵。
// 要求设计如下函数：
// class Solution{
// public:
//  vector<vector<int>> generateMatrix(int n)
//  {  …   }
// };
// 【输入形式】
//         输入一个正整数n。
// 【输出形式】 
//      输出一个正方形矩阵，其中元素按顺时针顺序螺旋排列，元素的值为1~n2之间的正整数。
// 【样例输入】
//      3
// 【样例输出】[
// [ 1, 2, 3 ],
// [ 8, 9, 4 ],
// [ 7, 6, 5 ]
// ]
// 【样例说明】
//       输入一个正整数3，输出元素值为1~9的3×3方阵，其元素按顺时针顺序螺旋排列。测试数据存放在in.txt文件中。


//第一步，读这个n
//第二步，生成相应螺旋矩阵
//第三步，想办法输出


#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void Spiral(int x, int y, int start, int n, vector<vector<int>>&a)
{
	if (n <= 0)return;
	if (n == 1)
	{
		a[x][y] = start;
		return;
	}
	for(int j = x;j < x + n - 1;j++) 
	{	a[y][j] = start;
		start++;
	}
	for (int i = y;i < y + n - 1;i++) 
	{
		a[i][x + n - 1] = start;
		start++;
	}
	for (int j = x + n - 1;j > x;j--) 
	{
		a[y + n - 1][j] = start;
		start++;
	}
	for (int i = y + n - 1;i > y;i--)  
	{
		a[i][x] = start;
		start++;
	}
	Spiral(x + 1, y + 1, start, n - 2, a);
}
class Solution{
public:
 vector<vector<int>> generateMatrix(int n)
 {  
 	vector<vector<int>> result(n, vector<int>(n));  //创建一个n*n的整型数组
	Spiral(0,0,1,n,result);
	return result;
}
};

void printarray(vector<vector<int>>result,int n)
{
	    cout<<"["<<endl;
    for(int i=0;i<n-1;i++)
    {
        cout<<"[";
        for(int j=0;j<n-1;j++)
        {
            cout<<result[i][j]<<",";
        }
        cout<<result[i][n-1]<<"]"<<","<<endl;		
    }
	cout<<"[";
	for(int j=0;j<n-1;j++)
    {
        cout<<result[n-1][j]<<",";
    }
    cout<<result[n-1][n-1]<<"]"<<endl;	
    cout<<"]";
}

int main()
{
    ifstream infile;
    infile.open("in.txt");    
    int n;
    infile>>n;
    vector<vector<int>> result(n, vector<int>(n));  //创建一个n*n的整型数组
	Solution q;
	result=q.generateMatrix(n);
    //接下来想办法输出
	printarray(result,n);
	return 0;
}
