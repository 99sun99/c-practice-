
#include "pch.h"
#include <iostream>
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()
#include <vector>
#include <queue>





using namespace std;



class my_priority_queue
{
	vector <int>  arr;

public:
	my_priority_queue();
	~my_priority_queue();
	void chgPrioirity(int, int);
	int  minPrioirty();
	bool contains(int);
	void Insert(int);
	int top();
	int size();
	int parent(int);
	int left(int);
	int right(int);
	void print();
	void swap(int&, int&);
	vector<int> get_vector();
};

vector<int> my_priority_queue::get_vector()
{
	return arr;
}

int  my_priority_queue::minPrioirty()
{
	int min;
	int k=0;
	int temp;

	if (arr.size() == 1)
	{
		min = arr.at(0);
		arr.pop_back();
	}
	else if (arr.size() == 1)
	{
		min = -1;
		cout << "empty heap" << endl;
	}
	else
	{
		min = arr.at(0);
		swap(arr[arr.size() - 1], arr[0]);
		arr.pop_back();
		
		
		while (k < arr.size() )
		{
			temp = arr[k];

			if ( left(k)<arr.size())
			{
				if (arr[k] > arr[left(k)])
				{
					swap(arr[k], arr[left(k)]);
				}
				
			}
			
			if (right(k)< arr.size())
			{
				if (arr[k] > arr[right(k)])
				{
					swap(arr[k], arr[right(k)]);
				}
				
			}


			//if(temp== arr[k])
			//{
			//	break;
			//}
			
				++k;
				
			
		}
	}

	return min;
}

bool my_priority_queue::contains(int val)
{
	bool result = false;
	vector <int>::const_iterator element = arr.cbegin();
	while (element != arr.cend())
	{
		if (val == *element)
		{
			result = true;
		}
		++element;
	}

	return result;
}




my_priority_queue::my_priority_queue()
{

}

my_priority_queue::~my_priority_queue()
{

}

int my_priority_queue::size()
{
	return arr.size();
}


int my_priority_queue::parent(int i)
{
	return((i - 1) / 2);
}

int my_priority_queue::left(int i)
{
	return(2*i+1);
}

int my_priority_queue::right(int i)
{
	return(2 * i + 2);
}

void my_priority_queue::swap(int &a, int &b)
{
	int tmp;

	tmp = a;
	a = b;
	b = tmp;



}

void my_priority_queue::Insert(int val)
{
	int i=0;
	this->arr.push_back(val);
	int k = arr.size()-1;
	int  pNode;
	int current;
	
	
		while (arr.size() > 1 )
		{
			//pNode = arr[this->parent(k)];
			//current = arr[k];
			//cout << this->parent(k) << "\t" << k << "\t" << pNode << "\t" << current<<"\t"<< arr.size() << endl;
			if (arr[this->parent(k)] > arr[k])
			{
				swap(arr[this->parent(k)], arr[k]);
			}
			k = this->parent(k);
			if (k == 0) { break; }
		}
	
}

int my_priority_queue::top()

{
	int t=-1;
	if (this->arr.size() > 0)
	{
		t = arr[0];
	}
	else
	{
		cout << "nothing in the heap" << endl;
	}

	return t;
}

void my_priority_queue::print()
{
	vector <int>::const_iterator element = this->arr.cbegin();
	if (this->arr.size() == 0)
	{
		cout << "nothing in the heap" << endl;
	}
	else
	{
		while (element != arr.cend())
		{

			cout << *element << "   "; ;
			++element;

		}
		cout<<endl;

	}



}

int main()
{
	int k = 0;
	int i = 0;
	int temp = 0;
	int max = 100;
	priority_queue <int, vector<int>, greater<int>>  PQ_lib;//min heap  ,priority_queue <int>  maxheap
	vector <int> comp1;
	vector <int> comp2;

	my_priority_queue* PQ = new my_priority_queue();

	
	//for (k; k < 60; k++)
	//{
	//	PQ = new my_priority_queue();

	//	srand(k);


	//	for (i=0; i < 60; i++)
	//	{
	//		PQ->Insert(rand() % 100 + 1);
	//		//cout << i << endl;
	//	}

	//	cout << PQ->top() << endl;
	//	PQ->print();


	//	delete PQ;
	//	
	//}


	srand(time(0));


	for (i = 0; i < max; i++)
	{
		temp = rand() % 100 + 1;
		PQ->Insert(temp);
		PQ_lib.push(temp);
	}

	
	for (i = 0; i < max; i++)

	{
		//cout << "top\t" << PQ->top() << endl;
		//PQ->print();
		//PQ->print();
		k = PQ->minPrioirty();
		temp = PQ_lib.top();
		//cout << "k\t" << k << "\t temp \t" << temp << endl;
		//if (k != temp)

		
		comp1.push_back(k);
		comp2.push_back(temp);
		PQ_lib.pop();
		
	}

	cout << static_cast <bool> (comp1 == comp2) << endl;






		return 0;
}


