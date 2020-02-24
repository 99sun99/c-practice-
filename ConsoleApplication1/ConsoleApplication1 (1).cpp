#include "pch.h"

#include <iostream>
#include <vector>


using namespace std;

const int N = 40;
template <class T>


inline void sum(int& accumulation, int n, vector<int> data,T &a)
{

	int i;
	T b;
	b = a;
	cout <<"b is"<< b<<endl;
	accumulation = 0;

	for (int i = 0; i < n; ++i)

		accumulation = accumulation + data.at(i);
}

int main(int argc, char** argv)
{
	int i;

	int accum = 0;
	int c = 3;

	vector<int> data(N);//if no n we use push_back()
	for (int i = 0; i < N; ++i)

		data[i] = i;
	

	sum(accum, N, data,c);

	cout << "sum is " << accum << endl;

	return 0;

}