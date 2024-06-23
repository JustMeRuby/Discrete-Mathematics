/*
	* MSSV: 19110488
	* Ho va ten: Huynh Khoang Tri
	* Assignment: Assignment 2 - Connected Components
	* Created on: 02/12/2021
	* IDE: Microsoft Visual Studio 2019
*/

#include <iostream>
#include <fstream>
#include <string>

#define MAX 100

using namespace std;

void FillMatrix(string filename, int matrix[][MAX], int &numVertices)
{
	ifstream file(filename);
	string text;
	
	int i = -1;
	while (getline(file, text))
	{
		++numVertices;
		++i;
		int j = -1;
		for (int k = 0; k < text.size(); k++)
		{
			if (text[k] != ' ')
			{
				++j;
				// Convert char to int
				matrix[i][j] = int(text[k]) - 48;
			}
		}
	}
}

void PrintMatrix(int matrix[][MAX], int numVertices)
{
	for (int i = 0; i < numVertices; i++)
	{
		for (int j = 0; j < numVertices; j++)
		{
			cout << matrix[i][j] << '\t';
		}
		cout << endl;
	}
	cout << endl;
}

void PrintComponents(string array[], int numVertices)
{
	for (int i = 0; i < numVertices; i++)
	{
		cout << array[i] << '\t';
	}
	cout << endl;
}

/* Y tuong:
	Ban dau, ta co mang chua cac thanh phan lien thong rieng le, vi du [1, 2, 3, 4]
	Ta tien hanh mo rong mang de xem cac dinh trong mang lien ket voi dinh nao khac,
thong qua viec duyet ma tran ke, vi du [1, 2, 3, 4] -> [12, 213, 32, 4]
	Ta tien hanh duyet nguoc mang tren. Neu co mot thanh phan lien thong B dung truoc thanh phan lien thong ma ta dang xet A,
va B chua mot hay nhieu dinh cua A, ta se chuyen cac dinh co trong A ma khong co trong B sang B,
sau do gan A = "Empty" hoac NULL (dung method clear() cua string).
Vi du:	[12, 213, 32, 4],		voi "4", ta chon "4", ta thay khong co thanh phan nao truoc do chua "4"
		[12, 213, 32, 4],		voi "32", ta chon "3", ta thay trong "213" cung co "3"
		[12, 213, Empty, 4],	voi "213", ta chon "2", ta thay trong "12" cung co "2",
								ma "12" chua co "3", ta them "3" vao "12" roi xoa "213"
		[123, Empty, Empty, 4]
	Thu tu vong lap:
		i: n-1 -> 0, dung de lay ra tung thanh phan lien thong
		j: 0 -> string[i].size(), dung de lay ra tung so (ky tu) trong string[i]
		k: i-1 -> 0, dung de lay ra tung thanh phan lien thong truoc thanh phan lien thong ma ta dang xet
		l: 0 -> string[i].size(), dung de chuyen cac dinh co trong string[i] ma khong co trong string[k] sang string[k]
*/
void HandleComponents(string array[], int matrix[][MAX], int numVertices)
{
	// // Expend connected components list to see which vertice connects with which vertice
	// Uncomment the PrintComponents lines to see the change
	// Before
	//PrintComponents(array, numVertices);
	for (int i = 0; i < numVertices; i++)
	{
		for (int j = 0; j < numVertices; j++)
		{
			if (matrix[i][j] == 1)
			{
				array[i].append(to_string(j + 1));
			}
		}
	}
	// After
	//PrintComponents(array, numVertices);
	
	// // Combine
	string componentString;
	char character;
	for (int i = numVertices - 1; i >= 0; i--)
	{
		// Uncomment the PrintComponents line below to see the whole process
		//PrintComponents(array, numVertices);

		componentString = array[i];
		for (int j = 0; j < componentString.size(); j++)
		{
			character = componentString[j];
			for (int k = i - 1; k >= 0; k--)
			{
				if (array[k].find(character) != array[k].npos)
				{
					for (int l = 0; l < componentString.size(); l++)
					{
						character = componentString[l];
						if (array[k].find(character) == array[k].npos)
						{
							array[k].push_back(character);
						}
					}
					array[i] = "Empty";
					break;
				}
			}
			if (array[i] == "Empty") { break; }
		}
	}
}

void DisplayResult(string array[], int numVertices)
{
	// First loop to count the number of Connected Components
	int numComponents = 0;
	for (int i = 0; i < numVertices; i++)
	{
		if (array[i] != "Empty") { ++numComponents; }
	}
	// Second loop to print Connected Components.
	// Keep in mind that this is doable with only one loop.
	// However, with one loop, the number of components can only be shown after displaying all components.
	cout << "The number of Connected Components: " << numComponents << endl;
	int count = 0;
	for (int i = 0; i < numVertices; i++)
	{
		if (array[i] != "Empty")
		{
			++count;
			cout << "Component " << count << ": " << array[i] << endl;
		}
	}
}

int main()
{
	// // Create empty 2D int array, then fill it to make it a adjacency matrix
	int matrix[MAX][MAX];
	int numVertices = 0;
	
	FillMatrix("Input_dothi.txt", matrix, numVertices);
	//PrintMatrix(matrix, numVertices);

	// // Create string array that contains connected components
	// // In the beginning, every vertice stands alone as a single connected component
	string components[MAX];
	for (int i = 0; i < numVertices; i++)
	{
		components[i] = to_string(i + 1);
	}
	// Before
	//PrintComponents(components, numVertices);
	// After
	HandleComponents(components, matrix, numVertices);
	//PrintComponents(components, numVertices);

	// // Output
	DisplayResult(components, numVertices);

	return 0;
}
