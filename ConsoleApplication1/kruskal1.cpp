#include "pch.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <istream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <string>
#include<iterator>
#include <algorithm>
#include <set>

using namespace std;

const int MAXV = 20;





//I didn't use priority queue in the Dijikstra. I only wrote it as the homework required.


class KrusKal
{

	vector <bool> discovered;
	vector<vector<int>> tree;//(x,y,cost,group_number)
	vector<vector<int>> connected_first_round_tree;
	vector<vector<int>> ranked_data;

public:
	KrusKal();
	~KrusKal();
	void spanning_tree();
	void show_path();
	
	vector<vector<int>> Data_Process(string);

};




KrusKal::KrusKal()
{

	ranked_data = Data_Process("kruskal_init.txt");

	for (int i = 0; i < MAXV; i++)
	{
		discovered.push_back(false);
	}

}

KrusKal::~KrusKal()
{
}

vector<vector<int>> KrusKal::Data_Process(string original_file)
{
	vector<vector<int>> G_data;
	ifstream words_file(original_file);
	string line;
	vector<string> article;
	int maxv_pos;

	if (words_file.is_open())
	{
		while (getline(words_file, line))
		{
			article.push_back(line);
		}
		words_file.close();
	}
	else { std::cout << "can not open file" << endl; }


	for (int i = 0; i < article.size(); i++)
	{
		istringstream iss(article.at(i));

		vector <int> temp;

		do {
			string subs;
			iss >> subs;
			try {
				temp.push_back(stoi(subs));
			}
			catch (...)
			{
				continue;
			}


		} while (iss);

		if (temp.size() == 3)
		{
			G_data.push_back(temp);
		}

	}
	
	//use set container delete redundancy.because the graph is undirected
	set<vector<set<int>>> data_clean;

	for (int i = 0; i < G_data.size(); i++)
	{
		set <int> location;
		set <int> cost;
		vector<set<int>> element;

		location.insert(G_data[i][0] < G_data[i][1] ? G_data[i][0] : G_data[i][1]);
		location.insert(G_data[i][0] > G_data[i][1] ? G_data[i][0] : G_data[i][1]);
		cost.insert(G_data[i][2]);

		element.push_back(location);
		element.push_back(cost);

		data_clean.insert(element);
	}

	//cout << "data_clean\t " << data_clean.size() << "G_data\t" << G_data.size() << endl;
	//push the cleaned data back to the G_data
	G_data.clear();
	for (auto i : data_clean)
	{
		vector<int> element;
		for (auto j : i)
		{
			for (auto k : j)
			{
				element.push_back(k);

			}
		}
		G_data.push_back(element);
	}


	//cout << "data_clean\t " << data_clean.size() << "G_data after delete the redunduncy \t" << G_data.size() << endl;

	sort(G_data.begin(), G_data.end(), [](const vector<int>&a, const vector<int>&b) {return (a[2] < b[2]); });
	ranked_data = G_data;

	//for (auto i : ranked_data)
	//{
	//	cout << "ranked_data after cleaning the redunduncy \t" << i[0] << "\t" << i[1] << "\t" << i[2] << "\t" << endl;
	//}
	return ranked_data;
}

void KrusKal::spanning_tree()
{
	int max_group = 1;
	int group_mark = 1;
	vector<int> count_tree;


	int temp = ranked_data.size();
	for (int i = 0; i < temp; i++)
	{
		if (i > ranked_data.size() - 1)
		{
			continue;
		}

		int group_number;
		if (discovered[ranked_data[i][0]] == false || discovered[ranked_data[i][1]] == false)
		{
			group_number = tree.size();
			vector <int> temp{ ranked_data[i][0], ranked_data[i][1], ranked_data[i][2],  group_number };
			tree.push_back(temp);//(x,y,cost,group_number) 
			discovered[ranked_data[i][0]] = true;
			discovered[ranked_data[i][1]] = true;
		}
	}

	//delete the chosen element from the original set
	for (int i = 0; i < tree.size(); i++)
	{
		int del_pos = 0;
		bool Del_Pos = false;

		for (int j = 0; j < ranked_data.size(); j++)
		{
			if (tree[i][0] == ranked_data[j][0] && tree[i][1] == ranked_data[j][1] && tree[i][2] == ranked_data[j][2])
			{
				del_pos = j;

				//cout << "del_pos" << del_pos << endl;
				Del_Pos = true;
			}
		}

		if (Del_Pos == true)
		{
			ranked_data.erase(ranked_data.begin() + del_pos);
		}
	}

	//tree((coordination,coordination,cost, group_number))   if they contains one same coordination, then we group them together
	for (int i = 0; i < tree.size(); i++) //grouping
	{
		for (int j = 0; j < tree.size(); j++)
		{
			if (tree[i][0] == tree[j][0] || tree[i][0] == tree[j][1] || tree[i][1] == tree[j][0] || tree[i][1] == tree[j][1])
			{
				tree[j][3] = tree[i][3];
			}
		}

	}


	sort(tree.begin(), tree.end(), [](const vector<int>&a, const vector<int>&b) {return a.at(3)<b.at(3); });


	count_tree.push_back(tree[0][3]);
	for (int i = 0; i < tree.size(); i++)
	{
		if (tree[i][3] == count_tree.at(count_tree.size() - 1)) //if group names are same
		{

			tree[i][3] = count_tree.size();
		}
		else
		{
			count_tree.push_back(tree[i][3]);
			tree[i][3] = count_tree.size();
		}
	}

	max_group = tree[tree.size() - 1][3];

	//cout << "max_group " << max_group << endl;

	//for (auto h : tree)
	//{
	//	cout << "connected_first_round_tree"<<h[0] << "\t" << h[1] << "\t" << h[2] << "\t" << h[3] << endl;

	//}

	//now we connected all of elements but not all of them are connected. we need to traverse  all the group to connect every element.
	connected_first_round_tree = tree;

	//combine groups until they are grouped into one big group.

	while (max_group > 1)
	{
		vector <vector<int>> grouping_data;
		set <int> combiner;       


		//put the same group of coordination into one combiner , and then we find the least cost from combiner to the remaining set.s
		for (auto i : tree)
		{
			if (i[3] == max_group)
			{
				combiner.insert(i[0]);
				combiner.insert(i[1]);
			}
		}

		for (auto i : ranked_data)
		{

			if (combiner.count(i[0]) || combiner.count(i[1]))
			{
				grouping_data.push_back(i);
			}

		}

		//cout << "grouping_data" << grouping_data.size() << endl;
		//cout << "tree   " << tree.size() << endl;

		sort(grouping_data.begin(), grouping_data.end(), [](const vector<int>&a, const vector<int>&b) {return a[2] < b[2]; });

		int grouping_pos;

		bool checked = false;// in case of repeat, eg 3-4 4-7, 
		if (combiner.count(grouping_data[0][0]))
		{

			vector<int> temp;

			int tree_size = tree.size();
			//cout << "tree_size" << tree_size << endl;
			for (int i = 0; i < tree_size; i++)
			{

				if (((tree[i][0] == grouping_data[0][1] || tree[i][1] == grouping_data[0][1])) && checked == false)
				{
					grouping_pos = tree[i][3];
					//cout << "grouping_pos " << grouping_pos << endl;
					temp = { grouping_data[0][0], grouping_data[0][1], grouping_data[0][2], grouping_pos };
					tree.push_back(temp);
					//cout << "tree2  \t" << tree.size() << endl;
					//cout << "grouping_pos \t" << grouping_pos << endl;
					//cout << "temp2 \t" << i[0] << "\t" << i[1] << "\t" << i[2] << "\t" << i[3] << endl;
					checked = true;

				}


			}

			for (int i = 0; i < tree.size(); i++)
			{
				if (tree[i][3] == max_group)
				{
					tree[i][3] = grouping_pos;
				}

			}

			//for (auto h : tree)
			//{
			//	cout << "[0]" << "max_group" << "\t" << max_group << "\t" << h[0] << "\t" << h[1] << "\t" << h[2] << "\t" << h[3] << endl;

			//}

			sort(tree.begin(), tree.end(), [](const vector<int>&a, const vector<int>&b) {return a[3] < b[3]; });




		}

		if (combiner.count(grouping_data[0][1]))
		{

			vector<int> temp;
			int tree_size = tree.size();
			//cout << "tree_size" << tree_size << endl;
			for (int i = 0; i < tree_size; i++)
			{

				if (((tree[i][0] == grouping_data[0][0] || tree[i][1] == grouping_data[0][0])) && checked == false)
				{
					grouping_pos = tree[i][3];
					//cout << "grouping_pos " << grouping_pos << endl;
					temp = { grouping_data[0][0], grouping_data[0][1], grouping_data[0][2], grouping_pos };
					tree.push_back(temp);
					//cout << "tree2  \t" << tree.size() << endl;
					//cout << "grouping_pos \t" << grouping_pos << endl;
					//cout << "temp2 \t" << i[0] << "\t" << i[1] << "\t" << i[2] << "\t" << i[3] << endl;
					checked = true;

				}


			}





			for (int i = 0; i < tree.size(); i++)
			{
				if (tree[i][3] == max_group)
				{
					tree[i][3] = grouping_pos;
				}

			}

			//for (auto h : tree)
			//{
			//	cout << "[1]" << "max_group" << max_group << "\t" << h[0] << "\t" << h[1] << "\t" << h[2] << "\t" << h[3] << endl;

			//}

			sort(tree.begin(), tree.end(), [](const vector<int>&a, const vector<int>&b) {return a[3] < b[3]; });




		}

		int del_pos;
		for (int i = 0; i < ranked_data.size(); i++)
		{
			if (grouping_data[0][0] == ranked_data[i][0] && grouping_data[0][1] == ranked_data[i][1] && grouping_data[0][2] == ranked_data[i][2])
			{
				del_pos = i;
			}

		}

		//cout << "ranked_data before  " << ranked_data.size() << endl;
		ranked_data.erase(ranked_data.begin() + del_pos);
		//cout << "ranked_data after   " << ranked_data.size() << endl;

		max_group = tree[tree.size() - 1][3];
		//cout << "max_group    " << max_group << endl;



		//for (auto h : tree)
		//{
		//	cout << h[0] << "\t" << h[1] << "\t" << h[2] << "\t" << h[3] << endl;

		//}

	}

	//cout << "max_group" << max_group << endl;



	//cout << "tree.size()" << tree.size() << endl;

	//renumber the group
	if (tree.size() == MAXV)
	{
		for (int i=0; i < tree.size(); i++)
		{
			tree[i][3] == 0;
		}

	}


}

void KrusKal::show_path()
{

	cout << "Since the graph is undirected, the result of i j is unordered.\nIt means we just cluster the pair which has same elements" << endl;

	cout << "the tree size is" << tree.size() << endl;
cout <<  "\ni"<<"\t" << "j"<<" \t" << "cost "<<"\t" << endl;

	for (auto h : tree)
{
	cout << h[0] << "\t" << h[1] << "\t" << h[2] << "\t"<< endl;

}

}



int main(int argc, char **argv)
{
	KrusKal *K = new KrusKal();

	K->spanning_tree();
	K->show_path();

	set <int, less<int>> a;







	return 0;
}