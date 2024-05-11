//第一步 从标准输入中获取输入的样例
//第二步 利用递归实现这个样例数串的全排列，还需要注意一下它这个输出的顺序，这个顺序还得一样
//第三步 把这个结果输出
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

void Swap(int& a, int& b)   //函数Swap是交换函数，实现将a和b的值互换
{
	int c = a;
	a = b;
	b = c;
    return;
}
void Perm(vector<int> num,int k,int m)  //Perm是实现全排列的函数，num是这个数组，k~m是需要进行全排列的数据范围
{
  
	if (k == m)
	{
		for (int i = 0; i <= m; ++i)
			cout<<num[i]<<" ";
		cout<<endl;
	}
	else
	{
		for (int j = k; j <= m; ++j)
		{
			Swap(num[j], num[k]);
			Perm(num, k + 1, m);
			Swap(num[j], num[k]);
		}
    }
}


int main()
{
    //先完成第一步，把这些整形数据读取进来
    string line;
    vector<int> numbers;
    ifstream infile;
    infile.open("in.txt");
    getline(infile, line);
    istringstream iss(line);
    int num;
    // 将整数逐个读取并添加到容器中
    while (iss >> num) {
        numbers.push_back(num);
    }
    Perm(numbers,0,numbers.size()-1);
    return 0;
}