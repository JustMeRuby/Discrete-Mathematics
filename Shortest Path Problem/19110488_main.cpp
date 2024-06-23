/*
	* MSSV: 19110488
	* Ho va ten: Huynh Khoang Tri
	* Assignment: Assignment 3 - Shortest-Path Problems - Bonus
	* Created on: 29/12/2021
	* IDE: Microsoft Visual Studio 2019
*/

#include <iostream>
#include <fstream>
#include <string>

#define INF 10e4
#define MAX 100

using namespace std;

void fillMatrix(string filename, string info_file, int matrix[][MAX], string name_array[], int& numVertex, int& start, int& end)
{
	string line;

	ifstream info(info_file);
	while (getline(info, line))
	{
		string index_string;
		for (int i = 0; i < line.size(); i++)
		{
			if (line[i] != ' ')
				index_string.push_back(line[i]);
			else
				break;
		}

		int index = stoi(index_string) - 1;
		bool space = false;
		for (int i = 0; i < line.size(); i++)
		{
			if (line[i] == ' ')
			{
				space = true;
				continue;
			}
			if (space == false)
				continue;
			else
			{
				for (int j = i; j < line.size(); j++)
				{
					name_array[index].push_back(line[j]);
				}
				break;
			}
		}
	}

	ifstream infile(filename);
	string type;

	getline(infile, type);

	getline(infile, line);
	numVertex = stoi(line);

	for (int i = 0; i < numVertex; i++)
	{
		for (int j = 0; j < numVertex; j++)
		{
			if (i == j)
				matrix[i][j] = 0;
			else
				matrix[i][j] = INF;
		}
	}

	// Create empty 2D string array to contain Adjacency List
	// and the last line of .txt file which contains start + end values
	string temp_array[MAX][MAX];
	int i = -1;
	while (getline(infile, line))
	{
		i++;
		int j = 0;
		for (int k = 0; k < line.size(); k++)
		{
			if (line[k] == ' ') j++;
			else if (line[k] != ' ')
			{
				temp_array[i][j].push_back(line[k]);
			}
		}
	}

	if (type == "0")
	{
		for (int j = 0; j < i; j++)
		{
			int x = stoi(temp_array[j][0]);
			int y = stoi(temp_array[j][1]);
			int cost = stoi(temp_array[j][2]);
			matrix[x - 1][y - 1] = cost;
			matrix[y - 1][x - 1] = cost;
		}
		start = stoi(temp_array[i][0]);
		end = stoi(temp_array[i][1]);
	}
	else if (type == "1")
	{
		for (int j = 0; j < i; j++)
		{
			int x = stoi(temp_array[j][0]);
			int y = stoi(temp_array[j][1]);
			int cost = stoi(temp_array[j][2]);
			matrix[x - 1][y - 1] = cost;
		}
		start = stoi(temp_array[i][0]);
		end = stoi(temp_array[i][1]);
	}
	else
	{
		cout << "Wrong Input Information!" << endl;
	}

	info.close();
	infile.close();
}

void printMatrix(int matrix[][MAX], int numVertex)
{
	for (int i = 0; i < numVertex; i++)
	{
		for (int j = 0; j < numVertex; j++)
		{
			cout << matrix[i][j] << '\t';
		}
		cout << endl;
	}
	cout << endl;
}

void dijkstra(int matrix[][MAX], int numVertex, int start, int end, int* parent, int& output_cost)
{
	int* cost = new int[numVertex];
	bool* done = new bool[numVertex];

	for (int i = 0; i < numVertex; i++)
	{
		cost[i] = INF;
		parent[i] = -1;
		done[i] = false;
	}
	cost[start] = 0;
	parent[start] = start;
	done[start] = true;

	int current = start;
	int min_index = start;
	int min_cost;

	while (min_index != -1)
	{
		for (int i = 0; i < numVertex; i++)
		{
			if (done[i] == false && matrix[current][i] != INF)
			{
				if (cost[i] > cost[current] + matrix[current][i])
				{
					cost[i] = cost[current] + matrix[current][i];
					parent[i] = current;
				}
			}
		}

		min_index = -1;
		min_cost = INF;
		for (int i = 0; i < numVertex; i++)
		{
			if (min_cost > cost[i] && done[i] == false)
			{
				min_cost = cost[i];
				min_index = i;
			}
		}

		if (min_index != -1)
		{
			done[min_index] = true;
			current = min_index;
		}
	}

	output_cost = cost[end];
}

void output(int* parent, string name_array[], int start, int current, int output_cost)
{
	ofstream outfile("ket_qua_bonus_19110488.txt");
	if (output_cost == INF)
	{
		outfile << "Khong co duong di ngan nhat";
		cout << "Khong co duong di ngan nhat";
	}
	else
	{
		outfile << "Tong chi phi di chuyen = " << output_cost << endl;
		cout << "Tong chi phi di chuyen = " << output_cost << endl;
		
		int path[MAX];
		int i = -1;
		while (current != start)
		{
			++i;
			path[i] = current;
			current = parent[current];
		}

		outfile << "Duong di ngan nhat cua do thi la: " << name_array[start];
		cout << "Duong di ngan nhat cua do thi la: " << name_array[start];
		for (i; i >= 0; i--)
		{
			outfile << " -> " << name_array[path[i]];
			cout << " -> " << name_array[path[i]];
		}

		outfile.close();
	}
}

int main()
{
	// // Create empty 2D int array, then fill it to make it a adjacency matrix
	int matrix[MAX][MAX];
	int numVertex = 0;
	int start, end;
	start = end = -1;

	// // Create empty 1D string array to contain the name of every vertex
	string name_array[MAX];
	fillMatrix("thong_tin_dinh.txt", "ten_dinh.txt", matrix, name_array, numVertex, start, end);
	//printMatrix(matrix, numVertex);

	int* parent = new int[numVertex];
	int output_cost;
	--start;
	--end;
	dijkstra(matrix, numVertex, start, end, parent, output_cost);

	// // Output
	output(parent, name_array, start, end, output_cost);

	cin.get();
	return 0;
}
