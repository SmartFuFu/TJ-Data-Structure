#include<iostream>
#include <conio.h>
using namespace std;
const int maxVertices = 50;


template<class T>
class MinSpanTree;

//用邻接矩阵存储图的类定义
template<class NameType, class DistType>
class Graphmtx
{
private:
	NameType VerticesList[maxVertices];        //顶点列表
	DistType Edge[maxVertices][maxVertices];   //邻接矩阵
	int numEdge;                               //当前边的条数
	int numVertices;                           //当前点的个数
public:
	Graphmtx();                                                 //构造函数
	int getVertexNum() { return numVertices; }                  //获取当前的顶点个数
	int getEdgeNum() { return numEdge; }                        //获取当前的边的个数
	int getVertexPos(NameType vertex);                          //取顶点v在图中的顶点位置
	NameType getValue(int i);                                   //取顶点i的值
	DistType getWeight(int v1, int v2);                         //取边v1v2的权值
	int getFirstNeighbor(int v);                                //获取v的第一个邻接顶点
	int getNextNeighbor(int v, int w);                          //获取v的邻接顶点中w的下一个邻接顶点
	bool insertVertex(NameType vertex);                         //插入一个顶点
	bool insertEdge(int v1, int v2, DistType cost);             //插入两端顶点为v1v2，权值为cost的一条边
	bool removeVertex(int v);                                   //删除v顶点
	bool removeEdge(int v1, int v2);                            //删除v1v2边

	template<class NameType, class DistType>
	friend void printMST(Graphmtx<NameType, DistType>& A, MinSpanTree<DistType>& B);    //友元函数打印最小生成树
	template<class NameType, class DistType>
	friend void Prim(Graphmtx<NameType, DistType>& A, MinSpanTree<DistType>& B, NameType C);   //友元函数声明，Prim算法生成最小生成树

};

//构造函数
template<class NameType, class DistType>
Graphmtx<NameType, DistType>::Graphmtx()
{
	numVertices = 0;
	numEdge = 0;
	for (int i = 0; i < maxVertices; ++i) {
		for (int j = 0; j < maxVertices; ++j) {
			Edge[i][j] = (i == j) ? 0 : INT_MAX;
		}
	}
}

//获取顶点位置
template<class NameType, class DistType>
int Graphmtx<NameType, DistType>::getVertexPos(NameType vertex)
{
	for (int i = 0; i < numVertices; i++) {
		if (VerticesList[i] == vertex)
			return i;
	}
	return -1;
}

//获取顶点值
template<class NameType, class DistType>
NameType Graphmtx<NameType, DistType>::getValue(int i)
{
	return (i >= 0 && i <= numVertices) ? VerticesList[i] : 0;
}

//获取边的权值
template<class NameType, class DistType>
DistType Graphmtx<NameType, DistType>::getWeight(int v1, int v2)
{
	return Edge[v1][v2];
}

//获取v的第一个邻接顶点
template<class NameType, class DistType>
int Graphmtx<NameType, DistType>::getFirstNeighbor(int v)
{
	if (v != -1) {
		for (int col = 0; col < numVertices; ++col) {
			if (Edge[v][col] > 0 && col < INT_MAX)
				return col;
		}
	}
	return -1;
}

//获取v的邻接顶点中w的下一个邻接顶点
template<class NameType, class DistType>
int Graphmtx<NameType, DistType>::getNextNeighbor(int v, int w)
{
	if (v != -1 && w != -1) {
		for (int col = w + 1; col < numVertices; ++col) {
			if (Edge[v][col] > 0 && col < INT_MAX)
				return col;
		}
	}
	return -1;
}

//插入一个顶点
template<class NameType, class DistType>
bool Graphmtx<NameType, DistType>::insertVertex(NameType vertex)
{
	if (numVertices == maxVertices)
		return 0;
	VerticesList[numVertices] = vertex;
	numVertices++;
	return 1;
}

//插入两端顶点为v1v2，权值为cost的一条边
template<class NameType, class DistType>
bool Graphmtx<NameType, DistType>::insertEdge(int v1, int v2, DistType cost)
{
	if (v1 > -1 && v1<numVertices && v2>-1 && v2 < numVertices) {
		if (Edge[v1][v2] == 0 || Edge[v1][v2] == INT_MAX)
			numEdge++;
		Edge[v1][v2] = Edge[v2][v1] = cost;
		return 1;
	}
	return 0;
}

//删除一顶点及其相关的边
template<class NameType, class DistType>
bool  Graphmtx<NameType, DistType>::removeVertex(int v)
{
	if (v<0 || v>numVertices)
		return 0;//不在表内删除失败
	if (numVertices == 1)
		return 0;//只剩一个顶点不删除
	for (int i = 0; i < numVertices; i++) {
		if (Edge[v][i] > 0 && Edge[v][i] < INT_MAX)
			numEdge--;//边的条数减一
	}
	VerticesList[v] = VerticesList[numVertices - 1];//用最后一个顶点替代删除顶点的位置
	for (int i = 0; i < numVertices; i++) {
		Edge[i][v] = Edge[i][numVertices - 1];
		Edge[i][numVertices - 1] = INT_MAX;
	}//用最后一列替代当前列
	for (int i = 0; i < numVertices; i++) {
		Edge[v][i] = Edge[numVertices - 1][i];
		Edge[numVertices - 1][i] = INT_MAX;
	}//用最后一行替代当前行
	Edge[numVertices - 1][numVertices - 1] = 0;
	numVertices--;//顶点数减一
	return 1;
}


//删除边
template<class NameType, class DistType>
bool Graphmtx<NameType, DistType>::removeEdge(int v1, int v2)
{
	if (v1 > -1 && v1<numVertices && v2>-1 && v2 < numVertices) {
		if (Edge[v1][v2] && Edge[v1][v2] < numVertices) {
			Edge[v1][v2] = Edge[v2][v1] = numVertices;
			numEdge--;
			return 1;
		}
		else
			return 0;
	}
	else
		return 0;
}



template<class T>
class MSTEdgeNode {
private:
	int tail, head;//起点终点
	T cost;        //权值
public:
	friend class MinSpanTree<T>;
	MSTEdgeNode(int t = -1, int h = -1, T c = -1)
	{
		tail = t;
		head = h;
		cost = c;
	}//构造函数
	template<class NameType, class DistType>
	friend void printMST(Graphmtx<NameType, DistType>& A, MinSpanTree<DistType>& B);
	template<class NameType, class DistType>
	friend void Prim(Graphmtx<NameType, DistType>& A, MinSpanTree<DistType>& B, NameType C);
};

template<class T>
class MinSpanTree
{
private:
	MSTEdgeNode<T> edge[maxVertices];
	int currentsize;
public:
	MinSpanTree() { currentsize = 0; }
	void insert(MSTEdgeNode<T> item)
	{
		edge[currentsize] = item;
		currentsize++;
	}//插入最小生成树的边
	template<class NameType, class DistType>
	friend void printMST(Graphmtx<NameType, DistType>& A, MinSpanTree<DistType>& B);
	template<class NameType, class DistType>
	friend void Prim(Graphmtx<NameType, DistType>& A, MinSpanTree<DistType>& B, NameType C);
};

//打印最小生成树，将表中数据依次打印出来
template<class NameType, class DistType>
void printMST(Graphmtx<NameType, DistType>& A, MinSpanTree<DistType>& B)
{
	for (int i = 0; i < B.currentsize; ++i)
	{
		cout << A.getValue(B.edge[i].tail) << "-(" << B.edge[i].cost << ")->" << A.getValue(B.edge[i].head) << endl;
	}
}

//Prim算法求最小生成树
template<class NameType, class DistType>
void Prim(Graphmtx<NameType, DistType>& A, MinSpanTree<DistType>& B, NameType C)
{
	int NumVertices = A.numVertices;               //当前顶点数目
	DistType* lowcost = new DistType[NumVertices];    //存放生成树顶点集合内顶点到到生生成树外各顶点的各边上的当前最小权值
	int* nearvex = new int[NumVertices];              //记录生成树顶点集合外各顶点距离离集合内哪个顶点最近(即权值最小)
	int begin = A.getVertexPos(C);            //起始顶点位置

	for (int i = 0; i < NumVertices; i++) {    //初始化数组
		lowcost[i] = A.Edge[begin][i];
		nearvex[i] = begin;
	}
	nearvex[begin] = -1;                 //将起始点放入树中
	MSTEdgeNode<DistType> e;             //辅助生成树节点
	for (int i = 1; i < NumVertices; ++i) {
		int min = INT_MAX;
		int v = -1;
		for (int j = 0; j < NumVertices; j++) {//查找权值最小边
			if (nearvex[j] != -1 && lowcost[j] < min) {
				v = j;
				min = lowcost[j];
			}
		}
		if (v != -1) {
			e.tail = nearvex[v];
			e.head = v;
			e.cost = lowcost[v];
			B.insert(e);
			nearvex[v] = -1;
			for (int j = 0; j < NumVertices; ++j) {//更新lowcost数组即nearvex数组
				if (nearvex[j] != -1 && A.Edge[v][j] < lowcost[j]) {
					lowcost[j] = A.Edge[v][j];
					nearvex[j] = v;
				}
			}
		}
	}
	delete[] lowcost;
	delete[] nearvex;
}
Graphmtx<char, int> map;
MinSpanTree<int> MST;
void wait_for_enter()
{
	cout << endl
		<< "按回车键继续";
	while (_getch() != '\r')
		;
	cout << endl
		<< endl;
}

//插入顶点
void insertV()
{
	int num;
	while (1) {
		cout << "请输入顶点的个数:";
		cin >> num;
		if (!cin.good()) {
			cout << "你输入了错误的类型" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
		else if (num >= 50 || num <= 0) {
			cout << "请输入小于50的正整数" << endl;
		}
		else
			break;
	}
	cout << "请依次输入各顶点的名称：" << endl;
	char A;
	for (int i = 0; i < num; ++i) {
		cin >> A;
		map.insertVertex(A);
	}

	cout << "输入结束" << endl;
}

//插入边
void insertE()
{
	int num = map.getVertexNum() * (map.getVertexNum() - 1) / 2;
	char a, b;
	int cost;
	int tail, head;
	cout << "构成完全图，需输入" << num << "条边" << endl;
	for (int i = 0; i < num; ++i) {
		cout << "请输入第" << i + 1 << "条边的两个顶点及边：";
		cin >> a >> b >> cost;
		tail = map.getVertexPos(a);
		head = map.getVertexPos(b);
		map.insertEdge(tail, head, cost);
	}
	cout << "输入结束" << endl;
}

//建立最小生成树
void buildMST()
{
	cout << "用Prim生成最小生成树" << endl;
	cout << "请输入起始顶点：";
	char C;
	cin >> C;
	Prim(map, MST, C);
	cout << "生成结束" << endl;

}

int main()
{
	cout << "=============================================" << endl;
	cout << "**             电网造价模拟系统            **" << endl;
	cout << "=============================================" << endl;
	cout << "**             A-创建电网顶点              **" << endl;
	cout << "**             B-添加电网的边              **" << endl;
	cout << "**             C-构造最小生成树            **" << endl;
	cout << "**             D-显示最小生成树            **" << endl;
	cout << "**             E-退出                      **" << endl;
	cout << "=============================================" << endl;



	while (1) {
		char choice;
		cout << endl;
		cout << "请选择操作：";
		cin >> choice;
		switch (choice) {
			case 'A'://插入顶点
				insertV();
				break;
			case 'B'://插入边
				insertE();
				break;
			case'C'://生成最小生成树
				buildMST();
				break;
			case'D':
				cout << "最小生成树如下" << endl;
				printMST(map, MST);//打印最小生成树
				break;
			case 'E':
				wait_for_enter();//结束运行
				return 0;
		}
	}
	return 0;
}

/*
提供测试数据如下：
A 4
a b c d

B
a b 8
b c 7
c d 5
d a 11
a c 18
b d 12

C
b

D
*/