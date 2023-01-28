#ifndef HEAP_H
#define HEAP_H
#include <iostream>

using namespace std;
#include <vector>



class Heap
{
public:
	vector<int> arr;
	int size;
	int maxSize;
	Heap() {
		size = 0;
		maxSize = 50;
	}
	void heapify(int i, int sizeToBeHeapified);
	void buildHeap();
	void heapSort();
	void pop();
	int top();
	void push(int data);
	~Heap() {}
	void print();
};
#endif // HEAP_H
