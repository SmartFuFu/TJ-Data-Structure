#include<iostream>
#include<conio.h>
using namespace std;

//最小堆
template <class Type>
class MinHeap {
public:
	MinHeap(int maxSize = 10);
	MinHeap(Type arr[], int n);
	~MinHeap() { delete[] heap; }
	bool Insert(const Type& x);
	bool RemoveMin();
	bool IsEmpty() const
	{
		return CurrentSize == 0;
	}
	bool IsFull() const
	{
		return CurrentSize == MaxHeapSize;
	}
	void MakeEmpty() { CurrentSize = 0; }
	int size() { return CurrentSize; }
	Type getmin();
private:
	Type* heap;
	int CurrentSize;                      //当前堆的大小,直接指向的是将要插入元素位置
	int MaxHeapSize;                      //当前堆的容量
	void FilterDown(int i, int m);
	void FilterUp(int i);
};

template <class Type>
MinHeap<Type>::MinHeap(int maxSize)
{
	MaxHeapSize = maxSize;
	CurrentSize = 0;
	heap = new Type[maxSize];
}

template <class Type>
MinHeap<Type>::MinHeap(Type arr[], int n)
{
	MaxHeapSize = n;
	CurrentSize = n;
	heap = new Type[n];
	for (int i = 0; i < n; i++) {
		heap[i] = arr[i];
	}
	int currentPos = (CurrentSize - 2) / 2;
	while (currentPos >= 0) {
		FilterDown(currentPos, CurrentSize - 1);
		currentPos--;
	}
}

//最小堆的向下调整算法
template<class Type>
void MinHeap<Type>::FilterDown(int start, int EndOfHeap)
{
	int i = start;
	int j = 2 * i + 1; //j为i中左子女的结点
	Type temp = heap[start];   //最开始的元素
	while (j <= EndOfHeap) {
		//选取两子女中的较小者
		if (j<EndOfHeap && heap[j]>heap[j + 1])
			++j;
		if (temp <= heap[j])
			break;
		else {
			heap[i] = heap[j];
			i = j;
			j = 2 * j + 1;
		}
	}
	heap[i] = temp;
}

template<class Type>
void MinHeap<Type>::FilterUp(int start)
{
	int j = start;
	int i = (j - 1) / 2;     //i为j的双亲
	Type temp = heap[start];
	while (j > 0) {
		if (heap[i] <= temp)
			break;
		else {
			heap[j] = heap[i];
			j = i;
			i = (i - 1) / 2;
		}
	}
	heap[j] = temp;
}

template<class Type>
bool MinHeap<Type>::Insert(const Type& x)
{
	if (CurrentSize == MaxHeapSize)
		return 0;
	heap[CurrentSize] = x;
	FilterUp(CurrentSize);
	++CurrentSize;
	return 1;
}

template<class Type>
bool MinHeap<Type>::RemoveMin()
{
	if (CurrentSize == 0)
		return 0;
	heap[0] = heap[CurrentSize - 1];
	CurrentSize--;
	FilterDown(0, CurrentSize - 1);
	return 1;
}

template<class Type>
Type MinHeap<Type>::getmin()
{
	return heap[0];
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
	int length;
	cout << "请输入木头将要切成的块数：";
	cin >> N;
	MinHeap<int> wood(N);

	cout << "接下来请输入" << N << "个正整数，代表每一段木块的长度：" << endl;
	for (int i = 0; i < N; ++i) {
		cin >> length;
		wood.Insert(length);
	}


	int sum = 0;

	while (wood.size() > 1)
	{
		int k1 = wood.getmin();
		wood.RemoveMin();
		int k2 = wood.getmin();
		wood.RemoveMin();
		sum += (k1 + k2);
		wood.Insert(k1 + k2);
	}

	cout << "锯木头的最小花费为" << sum << endl;

	wait_for_enter();
	return 0;
}