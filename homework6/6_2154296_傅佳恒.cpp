
//利用左长子右兄弟的方式存储多叉树
#include<iostream>
#include<conio.h>
#include<string>
using namespace std;


template <class Type>
class Tree;

//树的结点
template <class Type>
class TreeNode {
public:
	friend class Tree<Type>;
	friend void print_tree();      //友元函数，展示树
	friend void print_Mtree(string prefix, TreeNode<string>* p);
private:
	Type data;
	TreeNode<Type>* firstChild;   //左长子结点
	TreeNode<Type>* nextSibling;  //右兄弟结点
	TreeNode(Type value = 0, TreeNode<Type>* fc = NULL, TreeNode<Type>* ns = NULL) : data(value), firstChild(fc), nextSibling(ns) { }
};
//树
template <class Type>
class Tree {
public:
	Tree() { root = current = NULL; }      //构造函数，建立空树
	Tree(Type rootVal);                    //构造函数，建立以rootVal元素为根节点的树
	~Tree();                               //析构函数
	bool isEmpty();                        //是否为空树
	bool BuildRoot(Type rootVal);          //在空树的基础上，建立以rootVal元素为根节点的树
	bool Root();                           //让树的根结点称为当前结点
	bool Find(Type target);                //查找是否有结点值为target的结点,使之成为当前结点
	bool FirstChild();                     //在树中寻找当前结点的长子,使之成为当前结点
	bool NextSibling();                    //在树中寻找当前结点的兄弟,使之成为当前结点
	bool Parent();                         //在树中寻找当前结点的双亲,使之成为当前结点
	bool insert_child(Type data);                   //给当前结点添加孩子
	Type root_data();                      //返回祖先结点的取值
	Type current_data();                   //返回当前结点的取值
	bool current_available();              //判断当前结点是否可取值
	void change_current(Type d);           //改变当前结点取值
	bool delete_tree(Type data);             //删除以值为data的结点为根结点的所有树
	void delete_tree(TreeNode<Type>* p);     //删除以当前结点为根结点的所有树
	friend void print_tree();      //友元函数，展示树
	friend void print_Mtree(string prefix, TreeNode<string>* p);
private:
	TreeNode<Type>* root;                                  //根结点
	TreeNode<Type>* current;                               //当前结点
	bool Find(TreeNode<Type>* p, Type target);              //查找时所用递归
	bool FindParent(TreeNode<Type>* t, TreeNode<Type>* p);  //找双亲时递归
};
//构造函数，建立以rootVal元素为根节点的树
template <class Type>
Tree<Type>::Tree(Type rootVal)
{
	root = current = new TreeNode <Type>(rootVal);
}

//析构函数
template <class Type>
Tree<Type>::~Tree()
{
	delete_tree(root);
}

//是否为空树
template <class Type>
bool Tree<Type>::isEmpty()
{
	return root == NULL;
}

//在空树的基础上，建立以rootVal元素为根节点的树
template <class Type>
bool Tree<Type>::BuildRoot(Type rootVal)
{
	if (!isEmpty())
		return 0;
	else {
		root = current = new TreeNode <Type>(rootVal);
		return 1;
	}
}

//让树的根结点称为当前结点
template <class Type>
bool Tree<Type>::Root()
{
	if (root == NULL) {
		current = NULL;
		return 0;
	}
	else {
		root = current;
		return 1;
	}
}

//查找是否有结点值为target的结点,使之成为当前结点
template <class Type>
bool Tree<Type>::Find(Type target)
{
	if (isEmpty()) {
		return 0;
	}
	else
		return Find(root, target);
}
template<class Type>
bool Tree<Type>::Find(TreeNode<Type>* p, Type target)
{
	bool result = 0;
	if (p->data == target)
	{
		result = 1;
		current = p;
	}
	else {
		TreeNode<Type>* q = p->firstChild;
		while (q != NULL && !(result = Find(q, target)))
			q = q->nextSibling;
	}
	return result;
}

//在树中寻找当前结点的长子,使之成为当前结点
template<class Type>
bool Tree<Type>::FirstChild()
{
	if (current == NULL)
		return 0;
	else {
		current = current->firstChild;
		if (current == NULL)
			return 0;
		else
			return 1;
	}
}

//在树中寻找当前结点的兄弟,使之成为当前结点
template<class Type>
bool Tree<Type>::NextSibling()
{
	if (current == NULL)
		return 0;
	else {
		current = current->nextSibling;
		if (current == NULL)
			return 0;
		else
			return 1;
	}
}

//在树中寻找当前结点的双亲,使之成为当前结点
template<class Type>
bool Tree<Type>::Parent()
{
	if (current == NULL || current == root || isEmpty()) {
		current = NULL;
		return 0;
	}
	else {
		TreeNode<Type>* p = current;
		return FindParent(root, p);
	}
}
template<class Type>
bool Tree<Type>::FindParent(TreeNode<Type>* t, TreeNode<Type>* p)
{
	TreeNode<Type>* q = t->firstChild;
	while (q != NULL && q != p) {
		//循根的长子的兄弟链,递归在子树中搜索
		bool i;
		if ((i = FindParent(q, p)) != 0)
			return i;
		q = q->nextSibling;
	}
	if (q != NULL && q == p) {
		current = t;
		return 1;
	}
	else
		return 0;
}

//给当前结点添加孩子
template<class Type>
bool Tree<Type>::insert_child(Type data)
{
	if (current == NULL)
		return 0;
	else {
		TreeNode<Type>* p = current->firstChild;
		if (p == NULL)
			current->firstChild = new TreeNode<Type>(data);
		else {
			TreeNode<Type>* q = p->nextSibling;
			while (q != NULL) {
				p = q;
				q = q->nextSibling;
			}
			p->nextSibling = new TreeNode<Type>(data);
		}
		return 1;
	}
}

//返回祖先结点的取值
template<class Type>
Type Tree<Type>::root_data()
{
	return root->data;
}

//返回当前结点的取值
template<class Type>
Type Tree<Type>::current_data()
{
	return current->data;
}

//判断当前结点是否可取值
template<class Type>
bool Tree<Type>::current_available()
{
	return current != NULL;
}

//更改当前结点取值
template<class Type>
void Tree<Type>::change_current(Type d)
{
	if (current != NULL)
		current->data = d;
}

//删除以当前结点为根结点的所有树
template<class Type>
bool Tree<Type>::delete_tree(Type data)
{
	if (Find(data) == 0) {
		return 0;
	}
	TreeNode<Type>* del = current;
	if (current == root) {
		root = current = NULL;
	}
	else {
		TreeNode<Type>* p = current;
		Parent();
		TreeNode<Type>* q = current->firstChild;
		if (p == q) {
			current->firstChild = current->firstChild->nextSibling;
		}
		else {
			while (q->nextSibling != p && q->nextSibling != NULL) {
				q = q->nextSibling;
			}
			q->nextSibling = p->nextSibling;
		}
		p->nextSibling = NULL;
	}
	delete_tree(del);
	return 1;
}
template<class Type>
void Tree<Type>::delete_tree(TreeNode<Type>* p)
{
	if (p == NULL)
		return;
	else {
		delete_tree(p->firstChild);
		delete_tree(p->nextSibling);
		delete p;
		p = NULL;
	}
}


//利用树的结构存储家谱
Tree<string> family;

void wait_for_enter()
{
	cout << endl
		<< "按回车键继续";
	while (_getch() != '\r')
		;
	cout << endl
		<< endl;
}

//初始化一个家谱
void init()
{
	cout << "*****************************************" << endl;
	cout << "**            家谱管理系统             **" << endl;
	cout << "*****************************************" << endl;
	cout << "**  请选择要执行的操作：               **" << endl;
	cout << "**            A---完善家谱             **" << endl;
	cout << "**            B---添加家庭成员         **" << endl;
	cout << "**            C---解散局部家庭         **" << endl;
	cout << "**            D---更改家庭成员信息     **" << endl;
	cout << "**            E---展示家庭成员直系亲属 **" << endl;
	cout << "**            F---横向打印家谱         **" << endl;
	cout << "**            G---退出程序             **" << endl;
	cout << "*****************************************" << endl;
	cout << endl;

	string name;
	cout << "首先请建立一个家谱" << endl;
	cout << "请输入祖先的姓名：";
	cin >> name;
	family.BuildRoot(name);
	cout << "此家谱的祖先是" << family.root_data() << endl;
}
//画树
void print_tree()
{
	if (family.isEmpty()) {
		cout << "家族列表为空" << endl;
		return;
	}
	print_Mtree(" ", family.root);
}
void print_Mtree(string prefix, TreeNode<string>* p)
{
	if (p != NULL) {
		cout << prefix;
		if (p->nextSibling == NULL)
			cout << "└──";
		else
			cout << "├──";
		cout << " " << p->data << endl;
		TreeNode<string>* q = p->firstChild;
		for (; q != NULL; q = q->nextSibling) {
			if (p->nextSibling == NULL)
				print_Mtree(prefix + "    ", q);
			else
				print_Mtree(prefix + "│   ", q);
		}
	}
}
//将当前结点的第一代子女打印出来
void print_first_generation()
{
	cout << family.current_data() << "的第一代子孙是：";
	if (family.FirstChild()) {
		cout << family.current_data() << " ";
		while (family.NextSibling())
			cout << family.current_data() << " ";
		cout << endl;
	}
	else {
		cout << "无" << endl;
	}

}

//完善家谱
void improve_tree()
{
	string name;
	cout << "请输入要建立家庭的人的姓名：";
	cin >> name;
	if (!family.Find(name)) {
		cout << "没有在家谱中查找到该成员" << endl;
		return;
	}

	int num;
	while (1) {
		cout << "请输入" << name << "的儿女人数：";
		cin >> num;
		if (!cin.good()) {
			cout << "你输入了一个错误的数据类型" << endl;
		}
		else if (num <= 0) {
			cout << "请输入一个正整数" << endl;
		}
		else
			break;
		cin.clear();
		cin.ignore(1024, '\n');
	}

	string name1;
	for (int i = 0; i < num; i++) {
		cout << "请输入第" << i + 1 << "个子女的名字：" << endl;
		cin >> name1;
		family.insert_child(name1);
	}

	print_first_generation();
	print_tree();
}

//添加家庭成员
void append_child()
{
	string parent, child;
	cout << "请输入要添加儿子（或女儿）的人的姓名：";
	cin >> parent;
	if (!family.Find(parent)) {
		cout << "没有在家谱中查找到该成员" << endl;
		return;
	}

	cout << "请输入" << parent << "新添加儿子（或女儿）的姓名：";
	cin >> child;
	family.insert_child(child);

	print_first_generation();
	print_tree();
}

//删除局部家庭
void delete_family()
{
	string name;
	cout << "请输入要解散家庭的人的姓名：";
	cin >> name;
	if (!family.Find(name)) {
		cout << "没有在家谱中查找到该成员" << endl;
		return;
	}
	cout << "要解散家庭的人是：" << name << endl;
	family.delete_tree(name);
	cout << "已解散" << endl;
	print_tree();
}

//更改家庭成员姓名
void change_name()
{
	string first_name, sec_name;
	cout << "请输入更改姓名人目前的姓名：";
	cin >> first_name;
	if (!family.Find(first_name)) {
		cout << "没有在家谱中查找到该成员" << endl;
		return;
	}
	cout << "请输入更改后的姓名：";
	cin >> sec_name;
	family.change_current(sec_name);
	cout << first_name << "已更名为" << family.current_data() << endl;
	print_tree();
}

//展示家庭成员直系亲属
void print_data()
{
	string name;
	cout << "请选择你要查询直系亲属的姓名：";
	cin >> name;
	if (!family.Find(name)) {
		cout << "没有在家谱中查找到该成员" << endl;
		return;
	}
	if (family.Parent())
		cout << "该结点的双亲为：" << family.current_data() << endl;
	else
		cout << "该结点无双亲" << endl;

	family.Find(name);
	print_first_generation();
}




int main()
{
	init();
	char choice;
	while (1) {
		cout << endl;
		cout << "请选择你要执行的操作：";
		cin >> choice;

		switch (choice)
		{
			case 'A':
				improve_tree();

				break;
			case'B':
				append_child();
				break;
			case'C':
				delete_family();
				break;
			case'D':
				change_name();
				break;
			case'E':
				print_data();
				break;
			case'F':
				print_tree();
				break;
			case'G':
				cout << "程序运行结束" << endl;
				wait_for_enter();
				return 0;
				break;
			default:
				cout << "你输入了不合法的选项" << endl;
				break;

		}
		if (family.isEmpty())
		{
			cout << endl;
			cout << "族谱为空，无法进行操作" << endl;
			string name;
			cout << "首先请建立一个家谱" << endl;
			cout << "请输入祖先的姓名：";
			cin >> name;
			family.BuildRoot(name);
			cout << "此家谱的祖先是" << family.root_data() << endl;
		}

	}

	return 0;
}