//利用getline把若干行未知数量的int整形数据存储在数组中

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

int main() {
    string line;
    vector<int> numbers;

    // 逐行读取输入，直到到达文件末尾
    while (getline(cin, line)) {
        // 使用字符串流从当前行读取整数
        istringstream iss(line);  //利用istringstream把读取到的这一行字符串line转化为输入流以便从中读取数据
        int num;
        // 将整数逐个读取并添加到容器中
        while (iss >> num) {
            numbers.push_back(num);
        }
    }

    // 打印读取的整数
    cout << "读取的整数：" << endl;
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
