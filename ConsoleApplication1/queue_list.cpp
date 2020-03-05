//#include <bits/stdc++.h> 
#include "pch.h"
#include <iostream>
#include <vector>

using namespace std;

struct QNode {
	int data;
	QNode* next;
	QNode(int d)
	{
		data = d;
		next = nullptr;
	}
};

struct Queue {
	QNode *front, *rear;
	Queue()
	{
		front = rear = nullptr;
	}

	void enQueue(int x)
	{

		// Create a new LL node 
		QNode* temp = new QNode(x); //want to delete the primary address

		// If queue is empty, then 
		// new node is front and rear both 
		if (rear == nullptr) {
			front = rear = temp;
			return;
		}

		// Add the new node at 
		// the end of queue and change rear 
		rear->next = temp; //last in first out
		rear = temp;
	}

	// Function to remove 
	// a key from given queue q 
	void deQueue()
	{
		// If queue is empty, return nullptrptr. 
		if (front == nullptr)
			return;

		// Store previous front and 
		// move front one node ahead  last in first out
		QNode* temp = front;
		front = front->next;

		// If front becomes nullptrptr, then 
		// change rear also as nullptr 
		if (front == nullptr)
			rear = nullptr;

		delete (temp);//remove useless block, not *
	}
};

// Driven Program 
int main()
{

	Queue q;
	q.enQueue(10);
	q.enQueue(20);
	q.enQueue(24);
	q.enQueue(25);
	q.enQueue(28);
	q.deQueue();
	q.deQueue();
	q.enQueue(30);
	q.enQueue(40);
	q.enQueue(50);


	cout << "Queue Front : " << (q.front)->data << endl;   
	cout << "Queue Rear : " << (q.rear)->data;
}
// This code is contributed by rathbhupendra 
