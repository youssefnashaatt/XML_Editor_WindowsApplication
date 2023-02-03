#include "heap.h"
#include<iostream>
using namespace std;
/*
void heapify(vector<int>& arrayToBeHeapified, int size, int i)
{

}
void buildHeap(vector<int>& arrayToBeHeapified,int size)
{
	for (int i = (size / 2)-1; i>-1; i--)
		heapify(arrayToBeHeapified, arrayToBeHeapified.size(), i);
}

void heapSort(vector<int>& arr,int size)
{

}
*/
void Heap::heapify(int i, int sizeToBeHeapified)
{
	
	int left = i * 2 + 1; // left child 
	int right = i * 2 + 2; // right child 
	int max = i; //setting the max at the begining by the root 
	if (left < sizeToBeHeapified && arr[left] > arr[max])
		max = left;
	if (right < sizeToBeHeapified && arr[right] > arr[max])
		max = right;
	// update root if needed
	if (max != i)  //max changed
	{
		swap(arr[i], arr[max]); // swap i (expected root) with the max
		heapify(max, sizeToBeHeapified);

	}
}
void Heap::buildHeap()
{
	for (int i = (size / 2) - 1; i > -1; i--)
		heapify(i, size);
}
void Heap::heapSort()
{
	buildHeap(); //building heap first
	// after sorting.. taking the root to be the last element and then heapify again until it ends
	for (int i = size - 1; i > -1; i--)
	{
		swap(arr[i], arr[0]);
		heapify(0, i);
	}
	//for (auto s : arr) cout << s << endl;

}
void Heap::pop()
{
	if (size == 0) cout << "empty !";
	else {
		size--; arr.pop_back();
	}
}
int Heap::top()
{
	return arr[size];
}
void Heap::push(int data)
{
	if (size == maxSize) {
		arr.resize(maxSize * 2); maxSize = maxSize * 2;
	}
	arr.push_back(data);
	size++;
	buildHeap();

}
void Heap::print()
{
	/*int temp = 0;
	while (temp < size)
	{
		cout << arr[temp] << endl;
		temp++;
	}*/
	for (auto n : arr) cout << n << endl;
}
