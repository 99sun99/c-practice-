#include"pch.h"
#include<iostream>//include istream ostream
#include<iterator>
#include<fstream>//file stream
//#include<istream>
#include<algorithm>
#include<vector>
#include<string>
#include<typeinfo>
#include <sstream> 
//#include "string.h"

using namespace std;



int  main(int argc , char *argv )
{
	
		//ifstream word_file("word.txt");
		ifstream word_file("kruskal_init.txt");
		//istream_iterator<string> start(word_file), end; //if you want to iterate sth ,that must stream , string or file
		//istream_iterator<string> start, end;
		//vector<string> words(start,end);
		vector<string> article;
		string line;
		vector<vector<int>>  p;
		int a, b, c;
		//string e;
		//string subs;
		cout << "\n\n words as read \n";
		
		if (word_file.is_open())
		{

			cout << "getline" << endl;

			while (getline(word_file,line)) //get every line
			{
				
				article.push_back(line);
				//cout << line << endl;
			}
			word_file.close();
		}

		cout <<"word_file"<< typeid(word_file).name() << endl;
		cout << typeid(article.at(1)).name() << endl;//typename

		cout << article.at(1) << endl;
		a = stoi(article.at(0));
		//[a,b,c]= stoi(article.at(1)); //can't
		cout << sizeof(a) << endl;
		b= stoi(article.at(1));
		//istream_iterator<string> start(article.at(1)), end;
		//vector<string> words(start, end);
		cout << b<< endl; 

		
		for (int i = 0; i < article.size(); i++)
		{

			istringstream iss(article.at(i)); //traverse every line into words
			
			vector<int> temp;
			do {
				string subs;
				iss >> subs;//stoi  one by one
				try
				{
					//a = stoi(subs);
					//cout << a << endl;
					temp.push_back(stoi(subs));
					
				}
				catch (...)
				{
					//cout << " " << endl;
					continue;
				}
			} while (iss);

			p.push_back(temp);


		}

		cout << p.size() << endl;
		cout << p[0].size() << endl;
		cout << p[1].size() << endl;
			

		//for (auto str1 : words)

		//{
		//	cout << str1 << "\t";
		//}
		//


		//sort(words.begin(), words.end());
		//cout << "\n\n words as sorted \n";
		//for (auto str1 : words)

		//{
		//	cout << str1 << "\t";
		//}
		//cout << endl;

		return 0;
}