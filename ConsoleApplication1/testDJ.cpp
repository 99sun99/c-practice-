#include "pch.h"
#include <iostream>
#include <limits>
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()
#include <vector>
#include <cmath>


using namespace std;

const int MAXV = 50;


class EdgeNode {
public:
	int key;
	int weight;
	EdgeNode *next;
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
	bool adjacent( int , int );
	void neighbors(int );
	int get_node_value(int);       //returns the value associated with the node x
	void set_node_value(int,int);//sets the value associated with the node x to a 
	int  get_edge_value(int, int);
};

Graph::Graph(bool directed) 
{
	Max_V = MAXV;
	Max_E = (pow(Max_V, 2) - Max_V) / 2;//undirected Max Edges' number;
	this->directed = directed;
	for (int i = 0; i < MAXV ; i++) {   //forget to initialize a ptr
		this->edges[i] = nullptr;
		this->distance[i] = std::numeric_limits<int>::max();
	}

	srand(time(0));
	float a;
	int b=0;
	while (b == 0)
	{
		a = (float)(rand() % 100 + 1) / 100;

		b = Max_E * a;
	}
	
	this->density = b;
	cout << "The total numbers of vertexes and edges are " << Max_V << " and " << Max_E << "." << endl ;
	cout << "The density is " << a <<". "<< density <<" edges are selected as edges."<< endl;

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

	int k = 0;
	bool reload = false;
	srand(time(0));
	EdgeNode * curr = new EdgeNode(0,0);

	while (k < this->density )
	{	
		int x = rand() % 50 ;
		int y = rand() % 50 ;
		int weight = rand() % 10 + 1;
		
		

		if (this->edges[x] != nullptr)// check the dupicated pair
		{
			curr= this->edges[x];
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
	//int i = 0;
	int count = 0;
	//while(this->edges[i] != nullptr)
	for(int i=0;i<MAXV;i++)

	{	
		//current = g->edges[i];
		//if (g->edges[i] != nullptr)
		
			//EdgeNode *current = this->edges[i];
		if (this->edges[i] != nullptr)
		{
			current = this->edges[i];

			while (current != nullptr)
			{
				//current = current->next;
				++count;
				current = current->next;
				

			}
		}
	}

	count /=  2;
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

void ShortestPath::shortest_path(int start )
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


void ShortestPath::path( int end)

{

	if (end > -1 && end < MAXV  && parent[end] != -1) {
		cout <<  parent[end] << " ";
		path(parent[end]);
	}


}
void ShortestPath::path_size( int end)
{
	//for (int i = 0; i < maxv; i++) {
	//	if (distance[i] != std::numeric_limits<int>::max()) {
	//		cout << "shortest distance from " << start << " to " << i << " is: " << distance[i] << endl;
	//	}
	//}

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

	int begin =0;
	int end = 10;
	int i;

	//ShortestPath *Dtest = new ShortestPath();
	//Dtest->shortest_path(begin);
	//srand(time(0));

	//for ( i = 0; i <30; i++)
	//{
	//	srand(i);
	//	end = rand() % 50 + 1 ;

	//	cout << endl;
	//	cout <<"The shortest path from " << begin << " to " << end << " is: ";
	//	Dtest->path(end);
	//	cout << endl;

	//	Dtest->path_size(end);
	//	

	//}

	//for ( i = 0; i < 20; i++)
	//{
	//	srand(i);
	//	end = rand() % 50 + 1;
	//	cout << i << "  ";
	//	Dtest->path_size(end);

	//}


	bool a = true;
	while (a == true)
	{
		a = false;
		cout << "la la la " << endl;
	}


	


	return 0;
}