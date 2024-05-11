#include <iostream>
#include <string>
using namespace std;

template <typename T>
struct LinkNode
{
	T data;
	LinkNode* next;

	LinkNode() :next(NULL) {}
	LinkNode(T d) :data(d), next(NULL) {}
};
template<typename T>
class stack
{
public:
	LinkNode<T>* rear;

	stack() :rear(NULL) {}
	~stack()
	{
		if (rear == NULL) return;
		LinkNode<T>* pre = rear, * p = pre->next;
		while (p != rear)
		{
			delete pre;
			pre = p;p = p->next;
		}
		delete pre;
	}

	bool empty()
	{
		return rear == NULL;
	}
	bool push(T e)
	{
		LinkNode<T>* p = new LinkNode<T>(e);
		if (empty())
		{
			rear = p;
			rear->next = rear;
		}
		else
		{
			p->next = rear->next;
			rear->next = p;
		}
		return true;
	}
	void pop()
	{
		LinkNode<T>* p;
		if (empty()) return;
		if (rear->next == rear)  //栈中只有一个元素
		{
			p = rear;
			rear = NULL;
		}
		else
		{
			p = rear->next;
			rear->next = p->next;
		}
		delete p;
	}
	T gettop()
	{
		if (empty()) return false;
		return rear->next->data;
	}
	T Getbottom()
	{
		return rear->data;
	}
};

class Express
{
	string exp;  //中缀表达式
	string postexp;  //后缀表达式
public:
	Express(string str)
	{
		exp = str;
		postexp = " ";
	}
	string getpostexp()
	{
		return postexp;
	}

	void Trans()   //把中缀表达式转化成后缀表达式
	{
		stack<char> opor;
		int i = 0;
		char ch, e;
		while (i < exp.length())
		{
			ch = exp[i];
			if (ch == '(')
			{
				opor.push(ch);
			}
			else if (ch == ')')
			{
				while (!opor.empty() && opor.gettop() != '(')
				{
					e = opor.gettop();
					opor.pop();
					postexp += e;
				}
				opor.pop();
			}
			else if (ch == '+' || ch == '-')
			{
				while (!opor.empty() && opor.gettop() != '(')
				{
					e = opor.gettop();
					opor.pop();
					postexp += e;
				}
				opor.push(ch);
			}
			else if (ch == '*' || ch == '/')
			{
				while (!opor.empty() && opor.gettop() != '(' && (opor.gettop() == '*' || opor.gettop() == '/'))
				{
					e = opor.gettop();
					opor.pop();
					postexp += e;
				}
				opor.push(ch);
			}
			else if (ch == ' ')  //考虑输入空格的情况就直接跳过
			{
				;//什么操作都不进行
			}
			else
			{
				string d;
				while (ch >= '0' && ch <= '9')
				{
					d += ch;
					i++;
					if (i < exp.length())
						ch = exp[i];
					else
						break;
				}
				i--;
				postexp += d;
				postexp += "#";
			}
			i++;
		}
		while (!opor.empty())
		{
			e = opor.gettop();
			opor.pop();
			postexp += e;
		}
	}
	int  GetValue()
	{
		stack<int>opand;
		int a, b, c, d;
		char ch;
		int i = 0;
		while (i < postexp.length())
		{
			ch = postexp[i];
			switch (ch)
			{
			case'+':
				a = opand.gettop(); opand.pop();
				b = opand.gettop(); opand.pop();
				c = a + b;
				opand.push(c);
				break;
			case'-':
				a = opand.gettop(); opand.pop();
				b = opand.gettop(); opand.pop();
				c = b - a;
				opand.push(c);
				break;
			case'*':
				a = opand.gettop(); opand.pop();
				b = opand.gettop(); opand.pop();
				c = b * a;
				opand.push(c);
				break;
			case'/':
				a = opand.gettop(); opand.pop();
				b = opand.gettop(); opand.pop();
				c = b / a;
				opand.push(c);
				break;
			default:
				d = 0;
				while (ch >= '0' && ch <= '9')
				{
					d = 10 * d + (ch - '0');
					i++;
					ch = postexp[i];
				}
				opand.push(d);
				break;
			}
			i++;
		}
		return opand.gettop();
	}
};


//现在是把整个逻辑都搞出来了
//下一步是输入



int main()
{
	string str;
	//= "(56-20)/(4+2)";
	//getline(cin, str, ' =' );
	getline(cin, str, '=');
	Express obj(str);
	//cout << "中缀表达式：" << str << endl;
	//cout << "转化为后缀为：" << endl;
	obj.Trans();
	//cout << obj.getpostexp() << endl;  //前面哪来的两个空格？
	//cout << "求值结果为" << endl;
	cout << obj.GetValue() << endl;
	return 0;
}