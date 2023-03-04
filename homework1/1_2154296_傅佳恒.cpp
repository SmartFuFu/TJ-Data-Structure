#include<iostream>
#include<string>
#include <conio.h>
#include <fstream>
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
	Student(int i) :id(i), name("\0"), gender(male), age(0), type("\0") {}

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
	else if (stu.gender == stu.female)
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
	ListNode() :next(NULL), pre(NULL) {}
	ListNode(Type _data, ListNode<Type>* i = NULL, ListNode<Type>* j = NULL) :data(_data), next(i), pre(j) {}
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
/*
提供测试数据如下：
10001 傅佳恒 男 18 软件工程师
10023 张某人 男 29 软件设计师
10022 刘某人 女 16 软件架构师
10011 沈某人 女 31 软件工程师
10098 王某人 男 34 软件架构师
10002 牛子宝 男 10 软件工程师
10388 蛇蛇宝 女 45 软件工程师
10222 蕾蕾   女 22 软件设计师
10009 小喵喵 男  9 软件测试师
*/
void wait_for_enter()
{
	cout << endl
		<< "按回车键继续";
	while (_getch() != '\r')
		;
	cout << endl
		<< endl;
}

class Databank
{
private:
	List<Student> table;
public:
	Databank() {}
	~Databank() {}

	void buildup();                       //数据库初始化
	void show();                          //展示考生名单
	void search();                        //查找考生信息
	void insertRightPostion(Student& da); //在合适位置插入考生信息
	void insert();                        //插入考生信息
	void remove();                        //删除考生信息
	void update();                        //更改考生信息
	void statistics();                    //统计考生信息
};

void Databank::buildup()
{
	cout << "首先请建立考生信息系统！" << endl;
	int studentnumber = 0;
	cout << "请输入考生人数：" << endl;
	while (true)
	{
		cin >> studentnumber;
		if (cin.fail() || studentnumber < 0)
		{
			cout << "请输入一个正整数！" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
		else
			break;
	}
	if (studentnumber == 0) {
		cout << "考生人数为0，建立数据库时没有考生" << endl;
		return;
	}
	cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别！" << endl;
	Student da;
	for (int i = 0; i < studentnumber; i++) {
		cin >> da;
		if (table.find(da) != NULL) {
			cout << "考号为" << da.id << "对应的学生已经存在" << endl;
		}
		else {
			this->insertRightPostion(da);
		}
	}
	this->show();
}

void Databank::show()
{
	if (table.isEmpty()) {
		cout << "该考试系统中暂无数据,请添加后重试" << endl;
		return;
	}

	for (int i = 0; i < 40; ++i)
		cout << "—";
	cout << endl;

	cout << "考号            姓名            性别            年龄            报考类别" << endl;

	for (int i = 0; i < 40; ++i)
		cout << "—";
	cout << endl;

	ListNode<Student>* p = table.first->next;
	while (p != NULL) {
		cout << p->data << endl;
		p = p->next;
	}

	for (int i = 0; i < 40; ++i)
		cout << "—";
	cout << endl;
	cout << "当前操作系统中共有" << table.size << "条数据" << endl;
	for (int i = 0; i < 40; ++i)
		cout << "—";
	cout << endl;
}

void Databank::search()
{
	cout << "请输入要查找的考生号：";
	int sid;
	cin >> sid;
	Student N(sid);
	ListNode<Student>* p = table.find(sid);
	if (p == NULL) {
		cout << "不存在考号为" << sid << "的考生！" << endl;
	}
	else {
		cout << "您查找到的考生信息为：" << endl;
		cout << p->data << endl;
	}
	cout << "查找完毕" << endl;
}

void Databank::insertRightPostion(Student& da)
{
	if (table.isEmpty()) {
		table.pushback(da);
	}
	else {
		ListNode<Student>* p = table.first->next;
		while (p != NULL) {
			if (da.id < p->data.id) {
				table.insert(p, da);
				return;
			}
			p = p->next;
		}
		table.pushback(da);
	}
}

void Databank::insert()
{
	cout << "请输入要插入的考生的考号：";
	int sid;
	cin >> sid;
	Student N(sid);
	ListNode<Student>* p = table.find(sid);
	if (p == NULL) {
		cout << "请按顺序输入该考生的姓名，性别，年龄及报考类别" << endl;
		input(cin, N);
		cout << "您将要插入的考生信息为：" << endl;
		cout << N << endl;
		insertRightPostion(N);
		cout << "插入完毕" << endl;
	}
	else {
		cout << "考号为" << sid << "的学生已经存在" << endl;
	}
}

void Databank::remove()
{
	cout << "请输入要删除的考生的考号：";
	int sid;
	cin >> sid;
	Student N(sid);
	ListNode<Student>* p = table.find(sid);
	if (p == NULL) {
		cout << "不存在考号为" << sid << "的考生！" << endl;
	}
	else {
		cout << "您删除的考生信息为：" << endl;
		cout << p->data << endl;
		table.remove(p);
		cout << "删除完毕" << endl;
	}
}

void Databank::update()
{
	cout << "请输入你将要修改的考生考号：";
	int sid;
	cin >> sid;
	Student N(sid);
	ListNode<Student>* p = table.find(sid);
	if (p == NULL) {
		cout << "不存在考号为" << sid << "的考生！" << endl;
	}
	else {
		cout << "您修改的考生信息为：" << endl;
		cout << p->data << endl;
		cout << "请按顺序输入该考生更改后的姓名，性别，年龄及报考类别" << endl;
		input(cin, N);
		p->data = N;
		cout << "修改完毕" << endl;
	}
}

void Databank::statistics()
{
	ListNode<Student>* p = table.first->next;
	int _gender[2] = { 0 };
	int _age[20] = { 0 };
	while (p != NULL) {
		++_gender[p->data.gender];
		++_age[p->data.age / 10];
		p = p->next;
	}
	cout << "男女比如下：" << endl;
	cout << "男生有" << _gender[0] << "人" << endl;
	cout << "女生有" << _gender[1] << "人" << endl << endl;
	cout << "各年龄段如下：" << endl;
	for (int i = 0; i < 20; i++) {
		if (_age[i] != 0) {
			cout << "年龄为" << i * 10 << "~~" << (i + 1) * 10 - 1 << "岁有" << _age[i] << "人" << endl;
		}
	}
	cout << "统计完毕" << endl << endl;
}

int main()
{
	Databank Db;
	Db.buildup();
	char p = '\0';
	while (1) {
		cout << endl;
		cout << "请选择你要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计数据，0为退出系统）：";
		cin >> p;
		switch (p)
		{
			case '1':
				Db.insert();
				break;
			case'2':
				Db.remove();
				break;
			case'3':
				Db.search();
				break;
			case'4':
				Db.update();
				break;
			case'5':
				Db.statistics();
				break;
			case'0':
				cout << "操作系统关闭" << endl;
				return 0;
				break;
			default:
				cout << "输入的指令不合法，请重新输入" << endl;
		}
		cout << "当前操作系统中数据如下" << endl;
		Db.show();
		wait_for_enter();
	}
	return 0;
}