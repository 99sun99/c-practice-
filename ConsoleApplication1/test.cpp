#include "pch.h"
#include <iostream>
#include <limits>
//#include "time.h"
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()

using namespace std;

//#define MAXV 1000
const int MAXV = 50;


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
	bool adjacent( int , int );
	void neighbors(int );
	int get_node_value(int);       //returns the value associated with the node x
	void set_node_value(int,int);//sets the value associated with the node x to a 
	int  get_edge_value(int, int);
};

Graph::Graph(bool directed) 
{
	this->directed = directed;
	for (int i = 0; i < MAXV ; i++) {   //forget to initialize a ptr
		this->edges[i] = nullptr;
		this->distance[i] = std::numeric_limits<int>::max();
	}


	float a;
	int b=0;
	while (b == 0)
	{
		a = (float)(rand() % 100 + 1) / 100;
		b = 50 * a;
	}
	
	this->density = b;
	//cout << "density is " << density << endl;



}

Graph::~Graph() {
	//to do
}

int Graph::get_edge_value(int x, int y)
{
	int val = std::numeric_limits<int>::max();


	//cout << " no path between x and y so val is 0" << endl;
	
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


void Graph::insert(int x, int y, int weight,bool directed)
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
	//if (x > 0 && x < MAXV  && y > 0 && y < MAXV ) {  
	//	EdgeNode *edge = new EdgeNode(y, weight);
	//	edge->next = this->edges[x];
	//	this->edges[x] = edge;
	//	if (!directed) { //if no direction , y->x is the same weight
	//		insert_edge(y, x, weight, true);
	//	}
	//}
	int k = 0;
	bool reload = false;
	
	while (k < this->density )
	{
		int x = rand() % 50 ;
		int y = rand() % 50 ;
		int weight = rand() % 100 + 1;
		
		

		if (this->edges[x] != nullptr)// check the dupicated pair
		{
			EdgeNode * curr= this->edges[x];
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
	bool mark =false;
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
				else if(curr != prev)
				{
					prev->next = curr->next;
					delete curr;//also delete others
					break;

				}

			}

			//delete prev; 
			prev = curr;
			curr = curr->next;
		}
		if (mark)
		{
			cout << "delete the node " << y << endl;
			
		}
		else
		{
			cout << "there is no "<< y<< " to be deleted here" << endl;
		}
		
		this->neighbors(x);
}

void Graph::print() {
	for (int v = 0; v < MAXV ; v++) {
		if (this->edges[v] != nullptr) {
			cout << "Vertex " << v << " has neighbors: " << endl;
			EdgeNode *curr = this->edges[v];
			while (curr != nullptr)
				//while (curr)
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
				//while (curr)
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
	if(x==0)
	{
		return false ;

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
	for (int i = 0; i < MAXV ; ++i)
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
	EdgeNode *current ;
	//current = this->edges[0];
	int i = 1;
	int count = 0;
	while(this->edges[i] != nullptr)
	//for(int i=1;i< (MAXV + 1); i++)

	{	
		//current = g->edges[i];
		//if (g->edges[i] != nullptr)
		
			//EdgeNode *current = this->edges[i];
		    current = this->edges[i];

			while (current != nullptr)
			{
				//current = current->next;
				++count;
				current = current->next;

			}


		

		i++;
	}

	return count;
}

void init_vars(bool discovered[], int distance[], int parent[]) 
{
	for (int i = 0; i < MAXV ; i++) {
		discovered[i] = false;
		distance[i] = std::numeric_limits<int>::max();
		parent[i] = -1;
	}
}



void dijkstra_shortest_path(Graph *g, int parent[], int distance[], int start) {

	bool discovered[MAXV ];
	EdgeNode *curr;
	int v_curr;
	int v_neighbor;
	int weight;
	int smallest_dist;

	init_vars(discovered, distance, parent);

	distance[start] = 0;
	v_curr = start;

	while (discovered[v_curr] == false) {

		discovered[v_curr] = true;
		curr = g->edges[v_curr];

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
		for (int i = 0; i < (MAXV ); i++) {
			if (!discovered[i] && (distance[i] < smallest_dist)) {
				v_curr = i;
				smallest_dist = distance[i];
			}
		}
	}
}

void print_shortest_path(int v, int parent[]) {
	if (v > 0 && v < MAXV  && parent[v] != -1) {
		cout << "shortest" << parent[v] << " ";
		print_shortest_path(parent[v], parent);
	}
}

void print_distances(int start, int distance[]) {
	for (int i = 0; i < MAXV ; i++) {
		if (distance[i] != std::numeric_limits<int>::max()) {
			cout << "Shortest distance from " << start << " to " << i << " is: " << distance[i] << endl;
		}
	}
}

int main() {

	Graph *g = new Graph(false);
	int parent[MAXV ];
	int distance[MAXV ];
	int start = 1;
	

	
	g->set_edge();
	g->print();








	


	return 0;
}