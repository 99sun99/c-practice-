#include "pch.h"
#include<iostream>
#include <numeric>//accumulate
#include <vector>
#include <algorithm>

using namespace std;

int main()

{

	vector<int> data(5, 1);

	int sum{ 0 };

	cout << sum << endl;

	for (auto element : data)

		sum += element;

	cout << sum << endl;

	for (auto p = ++data.begin(); p != --data.end(); ++p)

		sum += *p;

	cout << sum << endl;

	sum = 0;

	data.push_back(2);

	data.push_back(3);

	for (auto element : data)

		sum += element;

	cout << sum << endl;

	cout << accumulate(data.begin(), data.end(), data[0]) << endl;

}



//int main()
//{
//
//
//
//	int a = 2, b = -3, c = 2;
//
//	bool tval1 = false, tval2 = true;
//
//	char ch = 'b';
//
//
//	cout << c % 5/2 << endl;
//	cout << -a*c++ << endl;
//	cout << -a * c << endl;
//
//
//
//	return 0;
//}