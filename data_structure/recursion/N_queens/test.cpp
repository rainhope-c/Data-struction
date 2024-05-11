#include<iostream>
#include <fstream>
 
using namespace std;

class Solution{
public:
    bool colMark[64] = { 0 };
    bool naMark[64] = { 0 };
    bool pieMark[64] = { 0 };
    int total = 0;
    int N = 0;
    int ans[64] = { 0 };

    void totalNQueens(int i)
    {
        
        if (i > N)              //判断是否已经枚举完了N行
        {
            total++;
            return;             //返回到第N行
        }
        for (int j = 1; j <= N; ++j) //这里的j表示  本行的第j列
        {
            if ((!colMark[j]) && (!naMark[j - i + N]) && (!pieMark[i + j]))
            {
            //判断这个格子所在的两个斜线和所在列是否为空
                colMark[j] = true;
                naMark[j - i + N] = true;
                pieMark[i + j] = true;
                ans[i] = j;
                totalNQueens(i + 1);
                colMark[j] = false;      // 走之前别忘了恢复标记
                naMark[j - i + N] = false;
                pieMark[i + j] = false;
            }
        }
    }
};
int totalNQueenss(int n)
{
    Solution thiss;
    thiss.N=n;
    thiss.totalNQueens(1);
    return thiss.total;
}



int main()
{
    ifstream infile("in.txt");
    int N;
    infile >> N;
    int cnt=0;
    cnt=totalNQueenss(N);
    cout << cnt;
    return 0;
}