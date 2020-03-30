#include "pch.h"
#include <iostream>
#include <limits>
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()
#include <vector>
#include <cmath>
#include <queue>

using namespace std;


const int MAXV = 50;




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


void my_priority_queue::chgPrioirity(int val, int pos)
{
	int k = 0;

	if (this->arr.size() < pos + 1)
	{
		cout << "There is no such a position " << endl;
		return;
	}

	this->arr[pos] = std::numeric_limits<int>::min();



	while (pos > 0)
	{

		if (arr[parent(pos)] > arr[pos])
		{
			swap(arr[this->parent(pos)], arr[pos]);
		}
		pos = this->parent(pos);
	}

	minPrioirty();
	Insert(val);
}


vector<int> my_priority_queue::get_vector()
{
	return arr;
}

int  my_priority_queue::minPrioirty()
{
	int min;
	int k = 0;
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


		while (k < arr.size())
		{
			temp = arr[k];

			if (left(k) < arr.size())
			{
				if (arr[k] > arr[left(k)])
				{
					swap(arr[k], arr[left(k)]);
				}
			}

			if (right(k) < arr.size())
			{
				if (arr[k] > arr[right(k)])
				{
					swap(arr[k], arr[right(k)]);
				}

			}
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
	return(2 * i + 1);
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
	int i = 0;
	this->arr.push_back(val);
	int k = arr.size() - 1;
	int  pNode;
	int current;


	while (arr.size() > 1)
	{

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
	int t = -1;
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
		cout << endl;

	}



}





//I didn't use priority queue in the Dijikstra. I only wrote it as the homework required.

class EdgeNode {
public:
	int key;
	int weight;
	EdgeNode *next;
	//EdgeNode();
	EdgeNode(int, int);
};


EdgeNode::EdgeNode(int key, int weight) {
	this->key = key;
	this->weight = weight;
	this->next = nullptr;
}

class Graph {
	bool directed;
	int distance[MAXV];
	int density;
	int Max_V;
	int Max_E;
public:
	//bool directed;
	EdgeNode *edges[MAXV];
	//EdgeNode *edges;
	Graph(bool);
	~Graph();
	//void insert_edge(int, int, int, bool);//add() set_edge_value and set value, sets the value associated to the edge (x,y) to v
	void insert(int, int, int, bool);
	void set_edge();
	void delete_edge(int, int);
	void print();
	int V(); //returns the number of vertices in the graph
	int E(); //returns the number of edges in the graph
	bool adjacent(int, int);
	void neighbors(int);
	int get_node_value(int);       //returns the value associated with the node x
	void set_node_value(int, int);//sets the value associated with the node x to a 
	int  get_edge_value(int, int);
};

Graph::Graph(bool directed)
{
	Max_V = MAXV;
	Max_E = (pow(Max_V, 2) - Max_V) / 2;//undirected Max Edges' number;
	this->directed = directed;
	for (int i = 0; i < MAXV; i++) {   //forget to initialize a ptr
		this->edges[i] = nullptr;
		this->distance[i] = std::numeric_limits<int>::max();
	}

	srand(time(0));
	float a;
	int b = 0;
	while (b == 0)
	{
		a = (float)(rand() % 100 + 1) / 100;

		b = Max_E * a;
	}

	this->density = b;
	cout << "The total numbers of vertexes and edges are " << Max_V << " and " << Max_E << "." << endl;
	cout << "The density is " << a << ". " << density << " edges are selected as edges." << endl;

}

Graph::~Graph() {
	//to do
}

int Graph::get_edge_value(int x, int y)
{
	int val = std::numeric_limits<int>::max();



	if (this->edges[x] != nullptr)
	{
		EdgeNode *curr = this->edges[x];
		while (curr != nullptr)
		{
			if (y == curr->key)
			{
				val = curr->weight;
				break;
			}
			curr = curr->next;
		}
	}
	return val;
}


int Graph::get_node_value(int x)
{
	int dis;
	dis = this->distance[x];

	return dis;
}

void Graph::set_node_value(int x, int a)
{
	this->distance[x] = a;

}


void Graph::insert(int x, int y, int weight, bool directed)
{
	if (x > -1 && x < MAXV  && y > -1 && y < MAXV) {
		EdgeNode *edge = new EdgeNode(y, weight);
		edge->next = this->edges[x];
		this->edges[x] = edge;
		if (!directed) { //if no direction , y->x is the same weight
			insert(y, x, weight, true);
		}
	}

}

void Graph::set_edge() {

	int k = 0;
	bool reload = false;
	srand(time(0));
	EdgeNode * curr = new EdgeNode(0, 0);

	while (k < this->density)
	{
		int x = rand() % 50;
		int y = rand() % 50;
		int weight = rand() % 10 + 1;



		if (this->edges[x] != nullptr)// check the dupicated pair
		{
			curr = this->edges[x];
			while (curr != nullptr)
			{
				if (curr->key == y)
				{
					reload = true;
				}
				curr = curr->next;
			}

			if (!reload)
			{
				insert(x, y, weight, directed);
				k++;
			}
			delete curr;
		}
		else
		{
			insert(x, y, weight, directed);
			k++;
		}


		reload = false;
	}

}



void Graph::delete_edge(int x, int y)
{
	EdgeNode *curr = this->edges[x];
	EdgeNode *prev = this->edges[x];
	bool mark = false;
	while (curr != nullptr)
	{
		if (curr->key == y)
		{
			mark = true;

			if (curr == prev)
			{
				this->edges[x] = curr->next;
				delete curr;
				break;
			}
			else if (curr != prev)
			{
				prev->next = curr->next;
				delete curr;//also delete others
				break;

			}

		}

		prev = curr;
		curr = curr->next;
	}
	if (mark)
	{
		cout << "delete the node " << y << endl;

	}
	else
	{
		cout << "there is no " << y << " to be deleted here" << endl;
	}

	this->neighbors(x);
}

void Graph::print() {
	for (int v = 0; v < MAXV; v++) {
		if (this->edges[v] != nullptr) {
			cout << "Vertex " << v << " has neighbors: " << endl;
			EdgeNode *curr = this->edges[v];
			while (curr != nullptr)
			{
				cout << "key:\t" << curr->key << "\t weight \t" << curr->weight << endl;
				curr = curr->next;
			}
		}
	}
}

void Graph::neighbors(int x)
{

	if (this->edges[x] != nullptr) {
		cout << "Vertex " << x << " has neighbors: " << endl;
		EdgeNode *curr = this->edges[x];
		while (curr != nullptr)
		{
			cout << "key:" << curr->key << endl;
			curr = curr->next;
		}
	}
	else
	{

		cout << "no neighbours around" << endl;
	}
}

bool Graph::adjacent(int x, int y)
{
	if (x == 0)
	{
		return false;

	}
	else
	{
		if (this->edges[x] == nullptr)
		{
			return false;
		}
		else
		{
			EdgeNode *curr = this->edges[x];
			while (curr != nullptr)
			{
				if (curr->key == y)
				{
					return true;
				}
				curr = curr->next;
			}
			return false;

		}
	}
}

int Graph::V()
{
	int count = 0;
	for (int i = 0; i < MAXV; ++i)
	{
		if (this->edges[i] != nullptr)
		{
			++count;
		}


	}
	return count;
}

int Graph::E()
{
	EdgeNode *current;

	int count = 0;

	for (int i = 0; i < MAXV; i++)

	{

		if (this->edges[i] != nullptr)
		{
			current = this->edges[i];

			while (current != nullptr)
			{
				
				++count;
				current = current->next;


			}
		}
	}

	count /= 2;
	return count;
}



class ShortestPath
{
	Graph *Dgraph;
	int start;
	vector <int> distance;
	vector <int> parent;
	vector <bool> discovered;

public:
	ShortestPath();
	~ShortestPath();
	void shortest_path(int);
	void path(int);
	void path_size(int);
};

ShortestPath::ShortestPath()
{

	Dgraph = new Graph(false);
	Dgraph->set_edge();
	cout << "The graph contains " << Dgraph->V() << " vertexs and " << Dgraph->E() << " edges. Vertexes start from 0." << endl;
	for (int i = 0; i < MAXV; i++)
	{
		distance.push_back(std::numeric_limits<int>::max());
		parent.push_back(-1);
		discovered.push_back(false);
	}

}

ShortestPath::~ShortestPath()
{}

void ShortestPath::shortest_path(int start)
{
	//vector <int> Spath = {start};
	EdgeNode *curr;
	int v_curr;
	int v_neighbor;
	int weight;
	int smallest_dist;
	this->start = start;

	distance[start] = 0;
	v_curr = start;



	while (discovered[v_curr] == false) {

		discovered[v_curr] = true;
		curr = Dgraph->edges[v_curr];

		while (curr != nullptr) {

			v_neighbor = curr->key;
			weight = curr->weight;

			if ((distance[v_curr] + weight) < distance[v_neighbor]) {
				distance[v_neighbor] = distance[v_curr] + weight;
				parent[v_neighbor] = v_curr;
			}
			curr = curr->next;
		}


		//set the next current vertex to the vertex with the smallest distance
		smallest_dist = std::numeric_limits<int>::max();


		for (int i = 0; i < (MAXV); i++) {
			if (!discovered[i] && (distance[i] < smallest_dist)) {
				v_curr = i;
				smallest_dist = distance[i];
			}
		}
	}






}


void ShortestPath::path(int end)

{

	if (end > -1 && end < MAXV  && parent[end] != -1) {
		cout << parent[end] << " ";
		path(parent[end]);
	}


}
void ShortestPath::path_size(int end)
{


	if (distance[end] != std::numeric_limits<int>::max())
	{
		cout << "The shortest distance between " << start << " and " << end << " is: " << distance[end] << endl;
	}
	else
	{
		cout << " the two vertexes are not connected!";
	}

}


int main() {

	int begin = 0;
	int end = 10;
	int i;

	ShortestPath *Dtest = new ShortestPath();
	Dtest->shortest_path(begin);


	for (i = 0; i < 30; i++)
	{
		srand(i);
		end = rand() % 50 + 1;

		cout << endl;
		cout << "The shortest path from " << begin << " to " << end << " is: ";
		Dtest->path(end);
		cout << endl;

		Dtest->path_size(end);


	}







	return 0;
}