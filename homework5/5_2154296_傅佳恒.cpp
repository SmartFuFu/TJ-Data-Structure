#include<iostream>
#include<conio.h>
using namespace std;
template <class Type>
class Queue;

template <class Type>
class QueueNode {
	friend class Queue<Type>;
private:
	Type data;                    //队列结点数据
	QueueNode<Type>* link;        //结点链指针
	QueueNode(Type d = 0, QueueNode* l = NULL) : data(d), link(l) { }
};

template <class Type>
class Queue {
private:
	QueueNode<Type>* front, * rear; //队列指针
public:
	Queue() : rear(NULL), front(NULL) { }       //构造函数
	~Queue();                                   //析构函数
	void EnQueue(const Type& item);             //将新元素item插入到队列的队尾
	Type DeQueue();                             //删去队头结点，并返回队头元素的值
	Type GetFront();                            //返回队列头的值
	void MakeEmpty();                           //将链表置空
	int IsEmpty() const
	{
		return front == NULL;
	}
};

//队列的析构函数
template <class Type>
Queue<Type>::~Queue() {
	QueueNode<Type>* p;
	while (front != NULL) { //逐个结点释放
		p = front;
		front = front->link;
		delete p;
	}
}

//将新元素item插入到队列的队尾
template <class Type>
void Queue<Type>::EnQueue(const Type& item) {

	if (front == NULL)
		front = rear = new QueueNode<Type>(item, NULL);
	else {
		rear->link = new QueueNode<Type>(item, NULL);
		rear = rear->link;
	}
}

//删去队头结点，并返回队头元素的值
template <class Type>
Type Queue<Type>::DeQueue() {
	QueueNode<Type>* p = front;
	Type retvalue = p->data; //保存队头的值
	front = front->link; //新队头
	delete p;
	return retvalue;
}

//返回队列头的值
template <class Type>
Type Queue<Type>::GetFront()
{
	return front->data;
}

//将链表置空
template <class Type>
void Queue<Type>::MakeEmpty()
{
	QueueNode<Type>* p;
	while (front != NULL) { //逐个结点释放
		p = front;
		front = front->link;
		delete p;
	}
	front = rear = NULL;
}

void wait_for_enter()
{
	cout << endl
		<< "按回车键继续";
	while (_getch() != '\r')
		;
	cout << endl
		<< endl;
}

int main()
{
	int N;
	Queue<int> A;
	Queue<int> B;
	cout << "银行业务系统开始运行" << endl;
	while (1) {
		cout << "请输入顾客总数N：";
		cin >> N;
		if (!cin.good())
			cout << "您输入类型有误，请输入一个正整数" << endl;
		else if (N <= 0)
			cout << "请输入一个正整数" << endl;
		else
			break;
		cin.clear();
		cin.ignore(1024, '\n');
	}

	cout << "下面请输入" << N << "个正整数，依次为" << N << "位顾客的编号：";
	for (int i = 0; i < N; ++i) {
		int num;
		cin >> num;
		if (num % 2 == 1) {
			A.EnQueue(num);
		}
		else {
			B.EnQueue(num);
		}
	}

	cout << "输出序列为：";
	while (!A.IsEmpty() || !B.IsEmpty()) {
		int data;
		if (!A.IsEmpty()) {
			data = A.DeQueue();
			cout << data << " ";
		}
		if (!A.IsEmpty()) {
			data = A.DeQueue();
			cout << data << " ";
		}
		if (!B.IsEmpty()) {
			data = B.DeQueue();
			cout << data << " ";
		}
	}
	cout << endl;
	wait_for_enter();
	return 0;
}
