// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>

using namespace std;

const int N = 40;


void sum(int*p, int n, int d[])

{

	int i;

	*p = 0;

	for (int i = 0; i < n; ++i)

		*p = *p + d[i];

}

int main()

{
	

	int i;

	int accum = 0;

	int data[N];
	double data1[N];
	double summary = 0;

	for(int i = 0; i < N; ++i)

		//data[i] = i;

		data1[i] =static_cast<double> (i) ;



	//sum(&accum, N, data);
	for (int i = 0; i < N; ++i)
		summary += data1[i];

	cout << "sum is " << 2 << "summary"<<summary<< endl;

	return 0;

}