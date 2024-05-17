// 【问题描述】
//    如图所示是一棵有根树，图中每个结点用1～16的整数标识，结点8是树根。如果结点x位于根结点到结点y之间的路径中，则结点x是结点y的祖先。如果结点x是结点y和结点z的祖先，则结点x称为两个不同结点y和z的公共祖先。如果x是y和z的共同祖先并且在所有共同祖先中最接近y和z，则结点x被称为结点y和z的最近公共祖先，如果y是z的祖先，那么y和z的最近共同祖先是y。例如结点16和7的最近公共祖先是结点4，结点2和3的最近公共祖先是结点10，结点4和12的最近公共祖先是结点4。编写一个程序，找到树中两个不同结点的最近公共祖先。
// 【输入形式】
//   每个测试用例的第一行为树中结点数n（2≤n≤10,000），所有结点用整数1～n标识，接下来的n-1行中的每一行包含一对表示边的整数，第一个整数是第二个整数的父结点。请注意，具有n个结点的树具有恰好n-1个边。每个测试用例的最后一行为两个不同整数，需要计算它们的最近公共祖先。
// 【输出形式】
//    为每个测试用例输出一行，该行应包含最近公共祖先结点的编号。
// 【样例输入】
// 16                                                                         
// 1 14
// 8 5
// 10 16
// 5 9
// 4 6
// 8 4
// 4 10
// 1 13
// 6 15
// 10 11
// 6 7
// 10 2
// 16 3
// 8 1
// 16 12
// 16 7
// 【样例输出】
// 4
// 【样例说明】
//      测试数据的文件名为in.txt
// 【评分标准】
//     该题目有10个测试用例，每通过一个测试用例，得10分。

//没看太明白 但是好像是并查集？ 很有并查集的感觉 但是不完全是
//每个结点的孩子多 但是祖先是唯一的，可以用数组来存储这个祖先

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

vector<int> FindAllAnc(vector<int>tree,int x)
{
    vector<int>target;
    target.push_back(x);  //首先这个数自己也是他的祖先
    while(tree[x]!=0)
    {
        x=tree[x];  //x编程自己的祖先
        target.push_back(x);
    }  //最终都会找到最上面的那个
    return target;
}
int main()
{
    ifstream infile("in.txt");
    int n;
    infile>>n;
    vector<int>treeancester(n+1);  //创建有n个元素的int数组表示这n个元素的祖先
    for(int i=1;i<=n-1;i++)
    {
        int ancester,child;
        infile>>ancester>>child;
        treeancester[child]=ancester;  
    }
    //这样就完成了祖先树的创建
    // for(int i=1;i<=n;i++)
    // {
    // cout<<"第"<<i<<"个结点的祖先是"<<treeancester[i]<<endl;
    // }
    //接下来想办法找最近公共祖先
    //我的想法是找到每个结点的所有祖先，也不麻烦
    int x,y;
    infile>>x>>y;  //这两个是需要找祖先的
    vector<int>ancesterx=FindAllAnc(treeancester,x);  //存储x的全部祖先
    vector<int>ancestery=FindAllAnc(treeancester,y);  //存储y的全部祖先
    for(int i=0;i<ancesterx.size();i++)
    {
        for(int j=0;j<ancestery.size();j++)  //遍历寻找第一个公共祖先
        {
            if(ancesterx[i]==ancestery[j])
            {    cout<<ancesterx[i];
                return 0;
            }
        }
    }
}
