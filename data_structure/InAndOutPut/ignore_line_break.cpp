//当尝试直接使用  infile>>x  传递数据的时候，常遇到的问题是infile中出现一个换行符导致数据传递发生错误
//这个时候为了保证传输正确进行需要忽视infile中的换行符


// #include <limits>

// ifstream infile;
// infile.open("in.txt");
// infile.ignore(numeric_limits<streamsize>::max(), '\n');
//这个指令的含义是忽视直到文件输入的最大值中的全部换行符