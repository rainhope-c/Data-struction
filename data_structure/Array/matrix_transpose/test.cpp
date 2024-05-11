//实现二维数组的转置
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

void reverse(int &a,int &b)
{
    int c=a;
    a=b;
    b=c;
}

bool fun(vector<vector<int>>&array,int m,int n)  //实现功能的函数
{
    if(m!=n)
    {
        return false;
    }
    else
    {
        for(int i=0;i<m;i++)
        {
            for(int j=i;j<m;j++)
            {
            reverse(array[i][j],array[j][i]);
            }
        }
        return true;
    }
}

int main()
{
    std::cout<<"请输入行数和列数"<<endl;
    int m,n;
    cin>>m>>n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  //忽视换行符
    vector<vector<int>> array(m, vector<int>(n));  //创建一个m*n的整型数组
    cout<<"请输入数组"<<endl;
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            int x=0;
            cin>>x;
            array[i][j]=x;
        }
    }
    cout<<endl<<"原数组为:"<<endl;
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            cout<<array[i][j]<<" ";
        }
        cout<<endl;
    }
    //接下来进行就地转置
    //同样的是实现转置比较容易但是就地就比较麻烦
    fun(array,m,n);
    cout<<endl<<"逆置后为:"<<endl;
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            cout<<array[i][j]<<" ";
        }
        cout<<endl;
    }



    return 0;
}
