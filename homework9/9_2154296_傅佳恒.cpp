#include<iostream>
#include <conio.h>
using namespace std;
const int maxVertices = 50;
//用邻接表存图
template<class NameType, class DistType>
struct KeyEdgeNode
{
	int tail;
	int head;
	DistType cost;
};

//邻接表上边结点的类定义
template<class NameType, class DistType>
struct Edge
{
	int dest;                              //边的另外一个顶点定义
	DistType cost;                         //边上的权值
	Edge<NameType, DistType>* link;        //下一条边链指针
	Edge() {}                              //构造函数
	Edge(int num, DistType weight) :dest(num), cost(weight), link(NULL) {}//构造函数
};

template<class NameType, class DistType>
struct Vertex
{
	NameType data;                    //顶点所代表数据
	Edge<NameType, DistType>* adj;    //边链表头指针
};

template<class NameType, class DistType>
class Graphlnk
{
private:
	Vertex<NameType, DistType> NodeTable[maxVertices];   //邻接表
	int numEdges;                                        //边的数量
	int numVertices;                                     //顶点数量
	int caculatekey(int v);                              //递归计算关键活动所用时间

public:
	KeyEdgeNode<NameType, DistType> KeyEdge[maxVertices]; //记录关键活动的数组
	int numKeyEdgeNode;                                   //关键活动数量

	Graphlnk();                                           //构造函数
	~Graphlnk();                                          //析构函数，删除边上所有顶点
	int getnumEdges() { return numEdges; }                //获取图中边的数目
	int getnumVertices() { return numVertices; }          //获取图中顶点数目
	int getVertexPos(NameType vertex);                    //获取顶点的位置
	NameType getValue(int i);                             //获取对应位置的顶点值
	DistType getWeight(int v1, int v2);                   //获取对应边的权值
	bool insertVertex(NameType vertex);                   //插入一个顶点
	bool insertEdge(int v1, int v2, DistType cost);       //插入一条边
	int getFirstNeighbor(int v);                          //获取当前顶点的第一个邻接顶点
	int getNextNeighbor(int v, int w);                    //获取当前结点的指定邻接顶点的下一个邻接顶点
	int caculatekey();                                    //调用递归函数计算关键路径的取值
	template<class NameType, class DistType>
	friend bool CriticalPath(Graphlnk<NameType, DistType>& T);  //友元函数声明，计算关键路径
};

//构造函数
template<class NameType, class DistType>
Graphlnk<NameType, DistType>::Graphlnk()
{
	numVertices = 0;
	numKeyEdgeNode = 0;
	numEdges = 0;
	for (int i = 0; i < maxVertices; ++i) {
		NodeTable[i].adj = NULL;
	}
	for (int i = 0; i < maxVertices; ++i) {
		KeyEdge[i].tail = -1;
		KeyEdge[i].head = -1;
		KeyEdge[i].cost = 0;
	}
}

//析构函数
template<class NameType, class DistType>
Graphlnk<NameType, DistType>::~Graphlnk()
{
	for (int i = 0; i < numVertices; ++i) {
		Edge<NameType, DistType>* p = NodeTable[i].adj;
		if (p != NULL) {       //依次删除每个结点
			NodeTable[i].adj = p->link;
			delete p;
			p = NodeTable[i].adj;
		}
	}
}

//获取对应顶点位置
template<class NameType, class DistType>
int Graphlnk<NameType, DistType>::getVertexPos(NameType vertex)
{
	for (int i = 0; i < numVertices; i++) {
		if (NodeTable[i].data == vertex)
			return i;
	}
	return -1;
}

//获取对应位置顶点的值
template<class NameType, class DistType>
NameType Graphlnk<NameType, DistType>::getValue(int i)
{
	return NodeTable[i].data;
}

//获取对应边上的权值
template<class NameType, class DistType>
DistType Graphlnk<NameType, DistType>::getWeight(int v1, int v2)
{
	if (v1 != -1 && v2 != -1) {
		Edge<NameType, DistType>* p = NodeTable[v1].adj;
		while (p != NULL && p->dest != v2) {
			p = p->link;
		}
		if (p != NULL)
			return p->cost;
	}
	return 0;
}

//插入顶点
template<class NameType, class DistType>
bool Graphlnk<NameType, DistType>::insertVertex(NameType vertex)
{
	if (numVertices == maxVertices)
		return 0;
	NodeTable[numVertices].data = vertex;
	NodeTable[numVertices].adj = NULL;
	numVertices++;
	return 1;
}

//插入边
template<class NameType, class DistType>
bool Graphlnk<NameType, DistType>::insertEdge(int v1, int v2, DistType cost)
{
	if (v1 < 0 || v1 >= numVertices || v2 < 0 || v2 >= numVertices)
		return 0;
	if (this->getWeight(v1, v2) != 0)
		return 0;
	Edge<NameType, DistType>* p = new Edge<NameType, DistType>;
	p->cost = cost;
	p->dest = v2;
	p->link = NodeTable[v1].adj;
	NodeTable[v1].adj = p;
	numEdges++;
	return 1;
}

//获取当前顶点的第一个邻接顶点
template<class NameType, class DistType>
int Graphlnk<NameType, DistType>::getFirstNeighbor(int v)
{
	if (v != -1) {
		Edge<NameType, DistType>* p = NodeTable[v].adj;
		if (p != NULL)
			return p->dest;
	}
	return -1;
}

//获取当前顶点指定邻接顶点的下一个邻接顶点
template<class NameType, class DistType>
int Graphlnk<NameType, DistType>::getNextNeighbor(int v, int w)
{
	if (v != -1) {
		Edge<NameType, DistType>* p = NodeTable[v].adj;
		while (p != NULL && p->dest != w)
			p = p->link;
		if (p != NULL && p->link != NULL)
			return p->link->dest;
	}
	return -1;
}

//计算关键路径上的权值和
template<class NameType, class DistType>
int Graphlnk<NameType, DistType>::caculatekey()
{
	return caculatekey(KeyEdge[0].tail);
}

//递归计算关键路径上的权值和
template<class NameType, class DistType>
int Graphlnk<NameType, DistType>::caculatekey(int v)
{
	for (int i = 0; i < numKeyEdgeNode; ++i) {
		if (KeyEdge[i].tail == v) {
			return caculatekey(KeyEdge[i].head) + KeyEdge[i].cost;
		}
	}
	return 0;
}

//计算关键路径流程
template<class NameType, class DistType>
bool CriticalPath(Graphlnk<NameType, DistType>& T)
{
	int num = T.numVertices;       //顶点数
	int* ind = new int[num];        //入度数组
	for (int i = 0; i < num; ++i)
		ind[i] = 0;                //顶点预置为0
	 //统计各顶点入度
	for (int i = 0; i < num; ++i) {
		int j = T.getFirstNeighbor(i);
		while (j != -1) {
			ind[j]++;
			j = T.getNextNeighbor(i, j);
		}
	}

	DistType* Ve = new DistType[num];  //各事件最早开始时间
	DistType* Vl = new DistType[num];  //各事件最晚开始时间
	DistType* Ee = new DistType[T.numEdges + 1];  //各活动最早开始时间
	DistType* El = new DistType[T.numEdges + 1];  //各活动最晚开始时间

	for (int i = 0; i < num; i++) {    //各事件开始事件预置为0
		Ve[i] = 0;
	}

	int u = -1;       //暂存当前位置
	int top = -1;     //入度为0的顶点的栈指针
	int lnk = -1;     //记录上一个顶点的位置，反向拓扑排序

	for (int i = 0; i < num; ++i) {//栈的初始化，入度为0的顶点进栈
		if (ind[i] == 0) {
			ind[i] = top;
			top = i;
		}
	}

	//利用拓扑排序直接完成事件最早开始时间的计算
	for (int i = 0; i < num; ++i) {
		if (top == -1) {//栈中事件数小于实际事件数，无法进行拓扑排序
			delete[] ind;
			delete[] Ve;
			delete[] Vl;
			delete[] Ee;
			delete[] El;
			return 0;
		}
		u = top;          //存当前
		top = ind[top];   //退栈
		ind[u] = lnk;
		lnk = u;

		int v = T.getFirstNeighbor(u);
		while (v != -1) {
			DistType w = T.getWeight(u, v);
			if (Ve[u] + w > Ve[v]) { //计算Ve
				Ve[v] = Ve[u] + w;
			}
			--ind[v];
			if (ind[v] == 0) {  //入度减少到0时进栈
				ind[v] = top;
				top = v;
			}
			v = T.getNextNeighbor(u, v);
		}
	}

	for (int i = 0; i < num; ++i) {  //Vl初始化为最后一个事件的最早开始时间
		Vl[i] = Ve[lnk];
	}

	while (lnk != -1) {            //反拓扑顺序遍历序列，计算最小值
		int v = ind[lnk];
		lnk = v;
		if (lnk == -1)
			break;
		int k = T.getFirstNeighbor(v);
		while (k != -1) {
			DistType w = T.getWeight(v, k);
			if (Vl[k] - w < Vl[v])
				Vl[v] = Vl[k] - w;
			k = T.getNextNeighbor(v, k);
		}
	}

	KeyEdgeNode<NameType, DistType> ed;
	int j = 0;        //活动的编号
	for (int i = 0; i < num; i++) {
		int u = T.getFirstNeighbor(i);
		while (u != -1) {
			DistType w = T.getWeight(i, u);
			Ee[j] = Ve[i];                       //活动最早开始时间
			El[j] = Vl[u] - w;                   //活动最晚开始时间
			if (Ee[j] == El[j]) {                //最早最晚时间相同时为关键活动
				ed.tail = i;
				ed.head = u;
				ed.cost = w;
				T.KeyEdge[T.numKeyEdgeNode++] = ed;  //加入表中
			}
			j++;
			u = T.getNextNeighbor(i, u);     //取下一个邻接顶点
		}
	}
	delete[] ind;          //析构函数
	delete[] Ve;
	delete[] Vl;
	delete[] Ee;
	delete[] El;
	return 1;
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
	int M;
	Graphlnk<int, int> map;
	cout << "请输入任务交接点数量N及子任务数量M（中间以空格分离）:";
	cin >> N >> M;
	//将任务交接点插入图中
	for (int i = 1; i <= N; ++i) {
		map.insertVertex(i);
	}
	cout << "下面请输入" << M << "行数据，每行给出三个整数" << endl;
	cout << "分别是该任务开始和完成设计的交接点编号以及完成该任务所需要的时间" << endl;

	//依次将所有活动插入图中
	for (int i = 1; i <= M; ++i)
	{
		cout << "请输入第" << i << "行：";
		int k1;
		int k2;
		int cost;
		cin >> k1 >> k2 >> cost;
		k1 = map.getVertexPos(k1);
		k2 = map.getVertexPos(k2);
		map.insertEdge(k1, k2, cost);
	}

	if (CriticalPath<int, int>(map) == 0) {//计算结果返回值为False时，有回路，无法计算关键路径
		cout << "0" << endl;
		cout << "不可行方案" << endl;
	}
	else {
		cout << "项目所需时间为" << map.caculatekey() << endl;//计算项目所需时间
		cout << "关键活动为：" << endl;
		for (int i = 0; i < map.numKeyEdgeNode; ++i) {
			cout << map.getValue(map.KeyEdge[i].tail) << "->" << map.getValue(map.KeyEdge[i].head) << endl;
		}    //将关键活动打印出来
		cout << "输出结束" << endl;
	}

	wait_for_enter();
	return 0;
}
/*
提供测试数据如下：
7 8
1 2 4
1 3 3
2 4 5
3 4 3
4 5 2
4 6 6
5 7 5
6 7 2

提供测试数据如下：
9 11
1 2 6
1 3 4
1 4 5
2 5 1
3 5 1
4 6 2
5 7 9
5 8 7
6 8 4
7 9 2
8 9 4

提供测试数据如下：
4 5
1 2 4
2 3 5
3 4 6
4 2 3
4 1 2
*/