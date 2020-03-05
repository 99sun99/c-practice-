// CPP program for array implementation of queue 
//#include <bits/stdc++.h> 
#include "pch.h" 

#include<iostream>

using namespace std;


// A structure to represent a queue 

class Queue
{
public:
	int front, rear, size;
	unsigned capacity;
	int* array;
};

//how to use pointers in the class
//for pointers: new!!!!!
int main()
{
	Queue queue;
	queue.array = new int[20];
	queue.array [0]=1;

	cout << queue.array[0] << endl;
	cout << *(queue.array) << endl;

	
	return 0;
}

// This code is contributed by rathbhupendra 
