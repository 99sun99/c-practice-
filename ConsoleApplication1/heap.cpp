// A C++ program to demonstrate common Binary Heap Operations 

//#include<climits> 
#include "pch.h"
#include <iostream>

using namespace std;

// Prototype of a utility function to swap two integers 
void swap(int *x, int *y);

// A class for Min Heap 
class MinHeap
{
//public:
	int *harr; // pointer to array of elements in heap 
	int capacity; // maximum possible size of min heap 
	int heap_size; // Current number of elements in min heap 

public:

	// Constructor 
	MinHeap(int capacity);

	// to heapify a subtree with the root at given index 
	void MinHeapify(int);

	int parent(int i) { return (i - 1) / 2; }

	// to get index of left child of node at index i 
	int left(int i) { return (2 * i + 1); }

	// to get index of right child of node at index i 
	int right(int i) { return (2 * i + 2); }

	// to extract the root which is the minimum element 
	int extractMin();

	// Decreases key value of key at index i to new_val 
	void decreaseKey(int i, int new_val);

	// Returns the minimum key (key at root) from min heap 
	int getMin() { return harr[0]; }

	// Deletes a key stored at index i 
	void deleteKey(int i);

	// Inserts a new key 'k' 
	void insertKey(int k);

	void print_array();
};

// Constructor: Builds a heap from a given array a[] of given size 


MinHeap::MinHeap(int cap)
{
	heap_size = 0;
	capacity = cap;
	harr = new int[cap];
}

// Inserts a new key 'k' 
void MinHeap::insertKey(int k)
{
	if (heap_size == capacity)
	{
		cout << "\nOverflow: Could not insertKey\n";
		return;
	}


	// First insert the new key at the end 
	heap_size++;
	int i = heap_size - 1;
	harr[i] = k;

	// Fix the min heap property if it is violated 
	while (i != 0 && harr[parent(i)] > harr[i])
	{
		swap(&harr[i], &harr[parent(i)]);
		i = parent(i);
	}
}

// Decreases value of key at index 'i' to new_val. It is assumed that 
// new_val is smaller than harr[i]. 
void MinHeap::decreaseKey(int i, int new_val)
{
	harr[i] = new_val;//directly del this val
	while (i != 0 && harr[parent(i)] > harr[i])
	{
		swap(&harr[i], &harr[parent(i)]);
		i = parent(i);
	}
}

// Method to remove minimum element (or root) from min heap 
int MinHeap::extractMin()
{
	if (heap_size <= 0)
		return INT_MAX;
	if (heap_size == 1)
	{
		heap_size--;
		return harr[0];
	}
	 
	// Store the minimum value, and remove it from heap 
	int root = harr[0];
	harr[0] = harr[heap_size - 1]; 
	heap_size--; 
	MinHeapify(0);  

	return root;
}


// This function deletes key at index i. It first reduced value to minus 
// infinite, then calls extractMin() 
void MinHeap::deleteKey(int i)
{
	decreaseKey(i, INT_MIN);
	extractMin();
}

// A recursive method to heapify a subtree with the root at given index 
// This method assumes that the subtrees are already heapified 
void MinHeap::MinHeapify(int i)
{
	int l = left(i);
	int r = right(i);
	int smallest = i;   
	if (l < heap_size && harr[l] < harr[i])
		smallest = l;
	if (r < heap_size && harr[r] < harr[smallest])
		smallest = r;
	if (smallest != i)
	{
		swap(&harr[i], &harr[smallest]);//you can not use a loop. You just need to recursive. 
		MinHeapify(smallest);
	}
}



void MinHeap::print_array()
{

	for (int i = 0; i < heap_size; ++i)
	{
		cout << harr[i] << " ";

	}

	cout<< endl;

}


// A utility function to swap two elements 
void swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

void normal_swap(int a, int b)
{
	cout << &a << "a1" << endl;
	int temp;
	temp = a;
	cout << &a << "a2" << endl;
	a = b;
	cout << &a << "a3" << endl;
	b = temp;
	cout << &a << "a4" << endl;



}




// Driver program to test above functions 
int main()
{
	MinHeap h(11);
	h.insertKey(3);
	h.insertKey(2);
	h.deleteKey(1);
	h.insertKey(15);
	h.insertKey(5);
	h.insertKey(4);
	h.insertKey(45);
	h.print_array();
	cout << h.extractMin() << " " << endl;
	h.print_array();
	cout << h.getMin() << "Min " << " "<<endl;
	cout << "fourth!!"<<h.harr[3] << h.harr[4]<< endl;
	h.print_array();
	h.decreaseKey(2, 1);
	h.print_array();
	cout << h.getMin();

	//int a = 1;
	//int b = 2;
	//int c;
	//cout <<"1"<< &a <<"   "<< &b << "   " << &c << endl;
	//c = a;
	//a = b;
	//b = c;
	//cout << "2" << &a << "   " << &b << "   " << &c << endl;


	//normal_swap(a, b);
	//cout << "3" << &a << "   " << &b << "   " << &c << endl;

	return 0;



	

}
