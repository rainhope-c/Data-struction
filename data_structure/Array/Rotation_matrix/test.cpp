//老三步
//样例输入
//问题处理
//样例输出

//先来完成第一步

#include <iostream>
#include <limits>
#include <vector>
#include <fstream>

using namespace std;

int main()
{
    ifstream infile;
    infile.open("in.txt");
    //考虑一下打开失败
    if(!infile)
    {
        cout<<"打开失败";
        return 0;
    }
    int m=0;
    infile>>m;  //一个m*m的矩阵
    vector<vector<int>> array(m, vector<int>(m));  //创建一个m*m的整型数组
    infile.ignore(numeric_limits<streamsize>::max(), '\n');  //忽略一下换行符
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<m;j++)
        {
            int x=0;
            infile>>x;
            array[i][j]=x;
        }
        infile.ignore(numeric_limits<streamsize>::max(), '\n');  //忽略一下换行符
    }
    //完成数组的读取

    //接下来想办法完成旋转这个过程
    //怎么实现这个旋转是个问题
    //发现的规律是旋转后(x,y)->(y,m-1-x)
    //问题在于如何实现这个"原地旋转"
    //再创建一个新数组来完成这个过程比较简单，我先来搞一下
    // vector<vector<int>> result(m, vector<int>(m));  //再创建一个m*m的整型数组
    // for(int i=0;i<m;i++)
    // {
    //     for(int j=0;j<m;j++)
    //     {
    //         result[j][m-1-i]=array[i][j];
    //     }
    // }

    //这样是没问题的，那现在的难点在于，如何在同一个矩阵中“原地”旋转
    //那就得换个思路
    //在网上搜索到的思路是先上下互换再对角互换
    //先进行上下互换
    for (int i = 0; i < m/2; i++) 
    {
        for (int j = 0; j < m; j++) 
        {
            int temp = array[i][j];
            array[i][j] = array[m - i - 1][j];
            array[m - i - 1][j] = temp;
        }
    }
    //再实现对角互换
    for (int i = 0; i < m; i++) 
    {
        for (int j = i; j < m; j++) 
        {
            int temp = array[i][j];
            array[i][j] = array[j][i];
            array[j][i] = temp;
        }
    }

    for(int i=0;i<m;i++)
    {
        for(int j=0;j<m;j++)
        {
            cout<<array[i][j]<<" ";
        }
        cout<<endl;
    }

    return 0;

}
