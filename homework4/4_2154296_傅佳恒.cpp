#include<iostream>
#include<conio.h>
using namespace std;

template <class Type>
class Stack;

template <class Type>
class StackNode {
	friend class Stack<Type>;
private:
	Type data;                   //结点数据
	StackNode<Type>* link;       //结点链指针
	StackNode(Type d = 0, StackNode<Type>* l = NULL) : data(d), link(l) { }
};

template <class Type> class Stack {
public:
	Stack() : top(NULL) { }
	~Stack();                        //析构函数，等于置空
	void Push(const Type& item);     //将数据压入栈顶
	Type Pop();                      //将栈顶数据弹出
	Type GetTop();                   //取栈顶数据
	void MakeEmpty();                //将栈置空
	bool IsEmpty() const
	{
		return top == NULL;
	}
private:
	StackNode<Type>* top; //栈顶指针
};

//析构函数，等于置空
template <class Type>
Stack<Type>::~Stack() {
	StackNode<Type>* p;
	while (top != NULL) //逐结点回收
	{
		p = top;
		top = top->link;
		delete p;
	}
}
// 将数据压入栈顶
template <class Type>
void Stack<Type>::Push(const Type& item) {
	top = new StackNode<Type>(item, top);
}

//将栈顶数据弹出
template <class Type>
Type Stack<Type>::Pop() {
	StackNode<Type>* p = top;
	Type retvalue = p->data;
	top = top->link;
	delete p;
	return retvalue;
}

//读取结点数据
template <class Type>
Type Stack<Type>::GetTop() {
	return top->data;
}

//清空栈
template <class Type>
void Stack<Type>::MakeEmpty()
{
	StackNode<Type>* p;
	while (top != NULL) //逐结点回收
	{
		p = top;
		top = top->link;
		delete p;
	}
}


//用以存放表达式的数组
char expression[100] = { '\0' };

//暂停，按回车键继续
void wait_for_enter()
{
	cout << endl
		<< "按回车键继续";
	while (_getch() != '\r')
		;
	cout << endl
		<< endl;
}

//返回判断运算符优先级
int find_priority(char A) {
	if (A == '(')
		return 1;
	else if (A == '+' || A == '-')
		return 2;
	else if (A == '*' || A == '/')
		return 3;
	else if (A == ')')
		return 4;
	else
		return 0;//表示该运算符并不支持
}
//判断是否为数
bool isnum(int cur) {
	return (expression[cur] >= '0' && expression[cur] <= '9') || expression[cur] == '.';
}

//打印数据并移动游标
void print_num_and_move(int& cur)
{
	char num[20] = { '\0' };
	int i = 0;
	if (isnum(cur)) {
		while (isnum(cur)) {
			num[i] = expression[cur];
			++i;
			++cur;
		}
		--cur;
		cout << num << " ";
	}
}

//判断+-是否为正负号
bool isfront(int cur)
{
	if (cur == 0 && isnum(cur + 1))
		return 1;
	else if (cur > 0 && !isnum(cur - 1) && isnum(cur + 1))
		return 1;
	return 0;
}

//清除表达式空格
void delete_blank() {
	int MAX;
	int i = 0;
	for (; expression[i] != '\0'; ++i) {}
	MAX = i - 1;
	for (int j = 0; expression[j] != '\0'; ++j) {
		if (expression[j] == ' ') {
			for (int k = j; k < MAX; ++k) {
				expression[k] = expression[k + 1];
			}
			expression[MAX] = '\0';
			MAX--;
		}
	}
}

int main()
{
	cout << "请输入一个中缀表达式（仅支持运算符加减乘除及左右括号）：";
	cin.get(expression, 100);   //读入带空格的表达式
	//delete_blank();            //将表达式中所有空格删除
	cout << "正在将中缀表达式转化为后缀" << endl;
	cout << "转化后表达式为：";
	Stack<char> sign;
	sign.MakeEmpty();
	for (int cur = 0; expression[cur] != '\0'; ++cur) {
		char c = expression[cur];
		switch (c) {
			case'-':
				if (isfront(cur)) {
					cout << "-";
					print_num_and_move(++cur);
				}
				else {
					if (sign.IsEmpty() || sign.GetTop() == '(') {
						sign.Push('-');
					}
					else {
						while (!sign.IsEmpty() && sign.GetTop() != '(') {
							char d = sign.Pop();
							cout << d << " ";
						}
						sign.Push('-');
					}
				}
				break;
			case'+':
				if (!isfront(cur)) {
					if (sign.IsEmpty() || sign.GetTop() == '(')
						sign.Push('+');
					else {
						while (!sign.IsEmpty() && sign.GetTop() != '(') {
							char d = sign.Pop();
							cout << d << " ";
						}
						sign.Push('+');
					}
				}
				break;
			case'*':
				if (sign.IsEmpty() || find_priority('*') > find_priority(sign.GetTop())) {
					sign.Push(c);
				}
				else {
					//弹出不小于*/优先级的运算符，仅有*或/
					while (!sign.IsEmpty() && (sign.GetTop() == '*' || sign.GetTop() == '/')) {
						char d = sign.Pop();
						cout << d << " ";
					}
					sign.Push(c);
				}
				break;
			case'/':
				if (sign.IsEmpty() || find_priority('/') > find_priority(sign.GetTop())) {
					sign.Push(c);
				}
				else {
					//弹出不小于*/优先级的运算符，仅有*或/
					while (!sign.IsEmpty() && (sign.GetTop() == '*' || sign.GetTop() == '/')) {
						char d = sign.Pop();
						cout << d << " ";
					}
					sign.Push(c);
				}
				break;
			case'(':
				sign.Push('(');
				break;
			case')':
				while (sign.GetTop() != '(') {
					char d = sign.Pop();
					cout << d << " ";
				}
				sign.Pop();
				break;
			default://当是数字的情形
				print_num_and_move(cur);
				break;
		}
	}
	while (!sign.IsEmpty()) {
		char d = sign.Pop();
		cout << d << " ";
	}
	cout << endl;
	cout << "输出结束" << endl;
	wait_for_enter();
	return 0;
}