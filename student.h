#pragma once
#include<iostream>
#include<string>

using namespace std;

class Databank;

template <class Type> 
class List;

/*****************************************************************************************************/
class Student
{
private:
	int id;
	string name;
	enum { male, female } gender;
	int age;
	string type;
public:
	//构造函数
	Student() :id(0), name("\0"), gender(male), age(0), type("\0") {}
	Student(int i):id(i), name("\0"), gender(male), age(0), type("\0"){}

	//友元输入输出函数
	friend istream& operator>>(istream& is, Student& stu);
	friend ostream& operator<<(ostream& os, const Student& stu);
	friend void input(istream& is, Student& stu);

	//查找时只需判断id，重载==运算符
	bool operator==(const Student stu)
	{
		return this->id == stu.id;
	}

	friend class Databank;
};
//输入函数
istream& operator>>(istream& is, Student& stu)
{
	string _gender;
	//按顺序依次输入考号，姓名，性别，年龄，报考类别
	is >> stu.id;
	is >> stu.name;

	is >> _gender;
	if (_gender == "男")
		stu.gender = stu.male;
	else if (_gender == "女")
		stu.gender = stu.female;

	is >> stu.age;
	is >> stu.type;

	return is;
}
//输入函数
void input(istream& is, Student& stu)
{
	is >> stu.name;
	//按顺序依次输入姓名，性别，年龄，报考类别
	string _gender;
	is >> _gender;
	if (_gender == "男")
		stu.gender = stu.male;
	else if (_gender == "女")
		stu.gender = stu.female;

	is >> stu.age;
	is >> stu.type;
}
//输出函数
ostream& operator<<(ostream& os, const Student& stu)
{
	if (stu.gender == stu.male)
		printf("%-8d\t%-8s\t%-8s\t%-8d\t%-8s\t", stu.id, stu.name.c_str(), "男", stu.age, stu.type.c_str());
	else if(stu.gender == stu.female)
		printf("%-8d\t%-8s\t%-8s\t%-8d\t%-8s\t", stu.id, stu.name.c_str(), "女", stu.age, stu.type.c_str());
	return os;
}


/*****************************************************************************************************/
template<class Type>
class ListNode
{
private:
	Type data;
	ListNode<Type>* next;
	ListNode<Type>* pre;
public:
	//构造函数
	ListNode() :next(NULL), pre(NULL){}
	ListNode(Type _data, ListNode<Type>* i = NULL, ListNode<Type>* j = NULL):data(_data), next(i), pre(j){}
	//友元函数声明
	friend class Databank;
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
	void makeEmpty();
	~List();

	//链表操作
	int getsize();              //返回链表当前链表的数量，表头不计入在内
	bool isEmpty();             //判断链表是否为空，为空时返回值为1，否则返回0

	//功能函数
	ListNode<Type>* find(const Type& d);             //查找是否有当前的元素，查找不到时返回NULL，查找到返回指向该结点的指针
	void remove(ListNode<Type>* node);               //将对应结点在链表中删除
	void insert(ListNode<Type>* node, Type da);      //在对应结点前插入元素为da的结点
	void pushback(Type data);                        //在链表末尾插入结点元素为data的元素
	friend class Databank;
};

template<class Type>
List<Type>::List()
{
	first = new ListNode<Type>;
	last = first;
	size = 0;
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
void List<Type>::insert(ListNode<Type>* node,Type da)
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