#include<iostream>
#include<conio.h>
using namespace std;

template <class Type>
class List;
template <class Type>
class ListNode;


/*****************************************************************************************************/
template<class Type>
class ListNode
{
public:
	Type data;
	ListNode<Type>* next;
	ListNode<Type>* pre;

	//构造函数
	ListNode() :next(NULL), pre(NULL) {}
	ListNode(Type _data, ListNode<Type>* i = NULL, ListNode<Type>* j = NULL) :data(_data), next(i), pre(j) {}
	//友元声明
	friend class List<Type>;
};

/*****************************************************************************************************/
template<class Type>
class List
{
private:
	ListNode<Type>* first;      //链表头指针
	ListNode<Type>* last;       //链表尾指针
	int size;                   //链表元素大小
public:
	//构造及析构函数
	List();
	List(const List<Type>& DA);       //复制构造函数，逐一链入结点
	void makeEmpty();
	~List();

	//链表操作
	int getsize();               //返回链表当前链表的数量，表头不计入在内
	bool isEmpty();              //判断链表是否为空，为空时返回值为1，否则返回0
	ListNode<Type>* getfirst();  //返回链表的表头结点

	//功能函数
	ListNode<Type>* find(const Type& d);             //查找是否有当前的元素，查找不到时返回NULL，查找到返回指向该结点的指针
	void remove(ListNode<Type>* node);               //将对应结点在链表中删除
	void insert(ListNode<Type>* node, Type da);      //在对应结点前插入元素为da的结点
	void pushback(Type data);                        //在链表末尾插入结点元素为data的元素

	//友元声明
	template <class Type>
	friend List<Type> intersection(const List<Type>& line1, const List<Type>& line2);
};

template<class Type>
List<Type>::List()
{
	first = new ListNode<Type>;
	last = first;
	size = 0;
}

template<class Type>
List<Type>::List(const List<Type>& DA)
{
	first = new ListNode<Type>;
	last = first;
	size = 0;
	ListNode<Type>* p = DA.first->next;
	while (p != NULL) {
		pushback(p->data);
		p = p->next;
	}
}

template<class Type>
void List<Type>::makeEmpty()
{
	size = 0;
	ListNode<Type>* p = first->next;
	ListNode<Type>* q;
	while (p != NULL) {
		q = p;
		p = p->next;
		delete q;
	}
	first->next = NULL;
	last = first;
}

template<class Type>
List<Type>::~List()
{
	makeEmpty();
	delete first;
}

//返回当前链表元素的数量
template<class Type>
int List<Type>::getsize()
{
	return size;
}

//判断链表是否为空
template<class Type>
bool List<Type>::isEmpty()
{
	return (first == last);
}

//返回链表表头结点
template<class Type>
ListNode<Type>* List<Type>::getfirst()
{
	return first;
}

//查找是否有指定取值的结点
template<class Type>
ListNode<Type>* List<Type>::find(const Type& d)
{
	ListNode<Type>* p = first->next;
	while (p != NULL) {
		if (p->data == d) {
			return p;
		}
		p = p->next;
	}
	return p;
}

//将指定结点在链表中删除
template<class Type>
void  List<Type>::remove(ListNode<Type>* node)
{
	--size;
	if (node == last) {
		last = node->pre;
		last->next = NULL;
	}
	else {
		node->next->pre = node->pre;
		node->pre->next = node->next;
	}
	delete node;
	return;
}

//在链表的指定位置插入指定元素的结点
template<class Type>
void List<Type>::insert(ListNode<Type>* node, Type da)
{
	++size;
	node->pre->next = new ListNode<Type>(da, node, node->pre);
	node->pre = node->pre->next;
}

//在链表的末尾插入指定元素的结点
template<class Type>
void List<Type>::pushback(Type da)
{
	++size;
	ListNode<Type>* newnode = new ListNode<Type>(da, NULL, last);
	last->next = newnode;
	last = newnode;
}

/*****************************************************************************************************/
void wait_for_enter()
{
	cout << endl
		<< "按回车键继续";
	while (_getch() != '\r')
		;
	cout << endl
		<< endl;
}

template<class Type>
List<Type> intersection(const List<Type>& line1, const List<Type>& line2)
{
	List<Type> result;
	ListNode<Type>* p = line1.first->next;
	ListNode<Type>* q = line2.first->next;
	while (p != NULL && q != NULL) {
		if (p->data == q->data) {
			result.pushback(p->data);
			p = p->next;
			q = q->next;
		}
		else if (p->data > q->data) {
			q = q->next;
		}
		else if (p->data < q->data) {
			p = p->next;
		}
	}

	return result;
}


int main()
{

	List<int> line1, line2;
	cout << "请输入第一个非降序正整数数列(以-1为输入结束标志)：" << endl;
	int i = 0;
	while (1) {
		cin >> i;
		if (i == -1)
			break;
		line1.pushback(i);
	}
	cout << "请输入第二个非降序正整数数列(以-1为输入结束标志)：" << endl;
	i = 0;
	while (1) {
		cin >> i;
		if (i == -1)
			break;
		line2.pushback(i);
	}

	List<int>line3 = intersection(line1, line2);

	cout << "交集表示如下：" << endl;
	if (line3.isEmpty()) {
		cout << "NULL" << endl;
	}
	else {
		ListNode<int>* p = line3.getfirst();
		p = p->next;
		while (p != NULL) {
			cout << p->data << " ";
			p = p->next;
		}
		cout << endl;
	}

	wait_for_enter();

	return 0;
}