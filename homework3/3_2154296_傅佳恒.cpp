#include <conio.h>
#include<ctime>
#include<iostream>
using namespace std;
/*****************************************************************************************************/
template<class T1, class T2>
struct Pair {
	T1 first;
	T2 second;
	//构造函数
	Pair() {};
	Pair(T1 _first, T2 _second) {
		this->first = _first;
		this->second = _second;
	}
	Pair(const Pair<T1, T2>& T) {
		this->first = T.first;
		this->second = T.second;
	}
	//重载等号运算符
	Pair& operator=(const Pair<T1, T2>& T) {
		this->first = T.first;
		this->second = T.second;
		return *this;
	}
	//重载判断两个队是否相等
	bool operator==(const Pair<T1, T2>& T) {
		return this->first == T.first && this->second == T.second;
	}
	//重载判断两个队是否不等
	bool operator!=(const Pair<T1, T2>& T) {
		return this->first != T.first || this->second != T.second;
	}

};
//重载运算符，两个pair相加，返回一个pair
template<class T1, class T2>
Pair<T1, T2> operator+(const Pair<T1, T2>& TONG, const Pair<T1, T2>& JI) {
	return Pair<T1, T2>(TONG.first + JI.first, TONG.second + JI.second);
}

/*****************************************************************************************************/
template<class Type>
class List;

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
	Type getdata_num(int n);     //获取第n个结点数据

	//功能函数
	ListNode<Type>* find(const Type& d);             //查找是否有当前的元素，查找不到时返回NULL，查找到返回指向该结点的指针
	void remove(ListNode<Type>* node);               //将对应结点在链表中删除
	void remove_number(int n);                       //将链表中第n个结点删除
	void insert(ListNode<Type>* node, Type da);      //在对应结点前插入元素为da的结点
	void pushback(Type data);                        //在链表末尾插入结点元素为data的元素

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

//获取第n个结点数据
template<class Type>
Type List<Type>::getdata_num(int n)
{
	if (isEmpty()) {
		cout << "链表为空，操作错误" << endl;
		exit(1);
	}
	if (n > size) {
		cout << "所需删除数据超过链表当前大小，操作错误" << endl;
		exit(1);
	}
	if (n <= 0) {
		cout << "所输入的值为负数，操作错误" << endl;
		exit(1);
	}
	ListNode<Type>* p = first;
	for (int i = 0; i < n; ++i) {
		p = p->next;
	}
	return p->data;
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

//将链表中第n个结点删除
template<class Type>
void List<Type>::remove_number(int n)
{
	if (isEmpty()) {
		cout << "链表为空，操作错误" << endl;
		return;
	}
	if (n > size) {
		cout << "所需删除数据超过链表当前大小，操作错误" << endl;

	}
	if (n <= 0) {
		cout << "所输入的值为负数，操作错误" << endl;
		return;
	}
	ListNode<Type>* p = first;
	for (int i = 0; i < n; ++i) {
		p = p->next;
	}
	this->remove(p);
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
	int IsEmpty() const
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

//枚举类型，墙，空白，路
enum maze_type
{
	WALL = 0, BLANK, WAY
};

typedef Pair<int, int> position;

//存放迷宫的二维数组
int MAX_X;                  //地图行
int MAX_Y;                  //地图列
maze_type** maze_map;       //地图数组
Stack<position> PATH;

const position direction[4] = { {0,1},{1,0},{0,-1},{-1,0} };

void wait_for_enter()
{
	cout << endl
		<< "按回车键继续";
	while (_getch() != '\r')
		;
	cout << endl
		<< endl;
}

//判断位置P是否在地图内
bool isIN(position P)
{
	return P.first <= MAX_X && P.first > 0 && P.second <= MAX_Y && P.second > 0;
}
//判断位置P是否为空白
bool isBLANK(position P)
{
	return isIN(P) && maze_map[P.first][P.second] == BLANK;
}
//判断位置P是否为墙
bool isWALL(position P)
{
	return isIN(P) && maze_map[P.first][P.second] == WALL;
}
//初始化地图，使地图全为空白
void init_BLANK()
{
	for (int i = 1; i <= MAX_X; ++i) {
		for (int j = 1; j <= MAX_Y; ++j) {
			maze_map[i][j] = BLANK;
		}
	}
}
//初始化地图，使地图全为墙
void init_WALL()
{
	for (int i = 1; i <= MAX_X; ++i) {
		for (int j = 1; j <= MAX_Y; ++j) {
			maze_map[i][j] = WALL;
		}
	}
}
//打印地图
void print_map()
{
	cout << "迷宫及路径示意如下($表示路径，#表示墙体)：" << endl;
	printf("    ");
	for (int i = 0; i <= MAX_Y + 1; ++i) {
		printf(" %2d ", i);
	}
	printf("\n");
	//第0行
	printf("  0 ");
	for (int i = 0; i <= MAX_Y + 1; ++i) {
		printf("  # ");
	}
	printf("\n\n");
	//地图行
	for (int i = 1; i <= MAX_X; i++) {
		printf(" %2d ", i);
		printf("  # ");
		for (int j = 1; j <= MAX_Y; j++) {
			if (maze_map[i][j] == WALL)
				printf("  # ");
			else if (maze_map[i][j] == BLANK)
				printf("    ");
			else if (maze_map[i][j] == WAY)
				printf("  $ ");
		}
		printf("  # \n\n");
	}
	//最后一行
	printf(" %2d ", MAX_X + 1);
	for (int i = 0; i <= MAX_Y + 1; ++i) {
		printf("  # ");
	}
	printf("\n");
}
//打印路径
void print_path() {
	cout << "求解出的路径如下：" << endl;
	position temp;
	int k = 0;
	Stack<position> realPATH;
	realPATH.MakeEmpty();
	while (!PATH.IsEmpty()) {
		realPATH.Push(PATH.Pop());
	}
	while (!realPATH.IsEmpty()) {
		temp = realPATH.Pop();
		if (k == 0) {
			cout << " (" << temp.first << "," << temp.second << ") ";
			k++;
		}
		else
			cout << "---> (" << temp.first << "," << temp.second << ") ";
	}
}
//利用Prim算法搭建地图
void Prim()
{

	List<position> T;
	//从<1,1>位置开始进行生成
	position A{ 1,1 };
	T.pushback(A);
	init_WALL();//将地图全变为墙
	while (!T.isEmpty()) {//当链表为空时停止循环
		//随机将链表中一个元素记录下来，并删除
		int i = rand() % T.getsize() + 1;
		position current = T.getdata_num(i);
		T.remove_number(i);
		//计算该位置四周可达到的位置数
		int road = 0;
		for (int i = 0; i < 4; ++i)
		{
			position nextPos = current + direction[i];
			if (isBLANK(nextPos))
				road++;
		}
		//若位置小于1，那么为单一路径，将墙打破
		if (road <= 1) {
			maze_map[current.first][current.second] = BLANK;
			//考察新位置四周，将新位置四周墙放入链表
			for (int i = 0; i < 4; ++i)
			{
				position nextPos = current + direction[i];
				if (isWALL(nextPos))
					T.pushback(nextPos);
			}
		}
	}
}

//利用递归算法求解迷宫
int travelmaze(position current, position goal) {
	if (current == goal) {
		maze_map[current.first][current.second] = WAY;
		return 1;
	}
	else {
		for (int i = 0; i < 4; i++) {
			position temp = current + direction[i];
			if (isBLANK(temp)) {
				maze_map[temp.first][temp.second] = WAY;
				PATH.Push(temp);
				if (travelmaze(temp, goal)) {
					return 1;
				}
				maze_map[temp.first][temp.second] = BLANK;
				PATH.Pop();
			}
		}
	}
	return 0;
}

//使用非递归算法求解迷宫
bool dfs(position start, position goal) {
	//构造一个标记的数组
	bool** mark;
	mark = new bool* [MAX_X + 1];
	for (int i = 1; i <= MAX_X; ++i) {
		mark[i] = new bool[MAX_Y + 1];
	}
	for (int i = 1; i <= MAX_X; ++i) {
		for (int j = 1; j <= MAX_Y; ++j) {
			mark[i][j] = 0;
		}
	}
	PATH.Push(start);
	mark[start.first][start.second] = 1;
	position temp;
	while (!PATH.IsEmpty()) {
		temp = PATH.GetTop();
		if (temp == goal)
			break;
		bool is_next_way = 0;
		for (int i = 0; i < 4; i++) {
			position next = temp + direction[i];
			if (isBLANK(next) && !mark[next.first][next.second]) {
				PATH.Push(next);
				maze_map[next.first][next.second] = WAY;
				mark[next.first][next.second] = 1;
				is_next_way = 1;
				break;
			}
		}
		if (!is_next_way) {
			maze_map[temp.first][temp.second] = BLANK;
			PATH.Pop();
		}
	}
	//清除申请的空间
	for (int i = 1; i <= MAX_X; ++i) {
		delete[] mark[i];
	}
	delete[] mark;
	if (PATH.IsEmpty())
		return 0;
	else
		return 1;
}

int main()
{
	srand(time(NULL));     //随机数种子

	//输入数据
	cout << "请根据提示输入数据" << endl;
	cout << "输入你所要生成的迷宫行与列，行与列间以空格分隔" << endl;
	cout << "其中，行与列的取值范围为5至25" << endl;
	while (1) {
		cout << "请输入：";
		cin >> MAX_X >> MAX_Y;
		if (!cin.good())
			cout << "你输入的数据类型有误" << endl;
		else if (MAX_X < 5 || MAX_Y < 5)
			cout << "你输入的迷宫太小啦，幼儿园小朋友都嫌弃你" << endl;
		else if (MAX_X > 25 || MAX_Y > 25)
			cout << "你输入的迷宫太大啦，以大学生的智商是走不出来的" << endl;
		else
			break;
		cin.clear();
		cin.ignore(1024, '\n');
	}
	cout << "你输入的迷宫大小为：" << MAX_X << "行" << MAX_Y << "列" << endl;

	//申请空间
	maze_map = new maze_type * [MAX_X + 1];
	for (int i = 1; i <= MAX_X; ++i) {
		maze_map[i] = new maze_type[MAX_Y + 1];
	}

	//生成迷宫
	cout << "下面利用普里姆算法（Prim算法）随机生成一个迷宫" << endl;
	Prim();
	print_map();

	//输入迷宫终点
	cout << "骑士将从位置<1,1>开始闯荡迷宫，先任命你为骑士团长，请你输入骑士去往的目的地" << endl;
	position goal;
	while (1) {
		cout << "请输入坐标（行与列中间用空格分开）：";
		cin >> goal.first >> goal.second;
		if (!cin.good())
			cout << "你输入的坐标类型可能不正确哦，骑士团长连整型都不知道，可以开了" << endl;
		else if (!isIN(goal))
			cout << "你输入的坐标不在地图上哦,这个骑士有点笨，不能为你开疆拓土" << endl;
		else if (isWALL(goal))
			cout << "这是墙啊，你以为骑士是崂山道士吗?" << endl;
		else if (goal.first == 1 && goal.second == 1)
			cout << "让骑士原地转圈圈的骑士团长不是好团长" << endl;
		else
			break;
		cin.clear();
		cin.ignore(1024, '\n');
	}

	//计算迷宫路径
	int choice = 0;
	cout << "请选择算法让骑士找到路（1.递归算法 2.非递归算法）" << endl;
	while (1) {
		cout << "请输入：";
		cin >> choice;
		if (!cin.good())
			cout << "你输入了错误的类型" << endl;
		else if (choice != 1 && choice != 2)
			cout << "请输入1或2" << endl;
		else
			break;
		cin.clear();
		cin.ignore(1024, '\n');
	}

	position temp{ 1,1 };
	PATH.MakeEmpty();
	maze_map[temp.first][temp.second] = WAY;
	if (choice == 1) {
		cout << "下面利用递归算法求解路径" << endl;
		PATH.Push(temp);
		travelmaze(temp, goal);
	}
	else {
		cout << "下面利用非递归算法求解路径" << endl;
		dfs(temp, goal);
	}

	//打印路径
	print_map();
	print_path();

	//清除申请空间
	for (int i = 1; i <= MAX_X; ++i) {
		delete[] maze_map[i];
	}
	delete[] maze_map;
	wait_for_enter();
	return 0;
}


