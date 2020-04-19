#include "pch.h"



#include <vector>
#include<iostream>
#include<algorithm>
#include <numeric>
#include <string>

#include <vector>
#include <fstream>
#include <unordered_map>
#include <random>

using namespace std ;


void incr(int &i) { static int n = 1; i = n++; }//no return
void outvec(int i) { cout << i << endl; }



int main()
{
	vector <int> v(6);
	for_each(v.begin(), v.end(), incr);
	for_each(v.begin(), v.end(), outvec);

	//vector <double> v2 { 1,2,3 };
	double sum;
	double v2[3]= { 1,2,3 };
	sum = accumulate(v2,v2+3,0.0,minus<int>());// first ,last, init value,rule
	//sum = accumulate(v2.begin(),v2.end(),0,minus<int>());
	cout << "sum"<<sum << endl;

	
	cout << _MSC_VER << endl;
	//transform(v2,v2+3,v2,std::bind2nd(times<int>(),2));
	

	//char *p = "hello";
	string p ( "hello" );

	cout << p << endl;



	vector <std::string> words;
	string temp_str, file_name;
	cout << "What File do you want?\n";
	cin >> file_name;

	ifstream fin(file_name);
	while (fin >> temp_str) // Will read up to eof()
		words.push_back(temp_str);

	fin.close();
	//unordered_map<std::string,int>  word_map_t;
	//cout << "word_map_t"<<word_map_t[0] << endl;
	//vector <size_t> test;
	//cout << test[0] << endl;
	unordered_map<std::string, size_t>  word_map;

	for (const auto &w : words)
	{	
		cout << "w" << w << "\t" << &w << "\t" << word_map[w] << endl;
		++word_map[w];
		cout << "w" << w << "\t" << &w << "\t" << word_map[w] << endl;
	}

	for (const auto &pair : word_map)
		cout << pair.second
		<< " occurrences of word '"
		<< pair.first << "'\n";





	return 0;
}