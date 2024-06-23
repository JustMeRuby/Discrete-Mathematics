/*
	* MSSV: 19110488
	* Ho va ten: Huynh Khoang Tri
	* Assignment: Assignment 1 - Truth Tables
	* Created on: 11/11/2021
	* IDE: Microsoft Visual Studio 2019
*/

#include <iostream>
#include <string>
using namespace std;

const int numPropositions = 5;
string Props[numPropositions] = { "~", "v", "^", "->", "<->"};
bool isProp(string mode)
{
	for (int i = 0; i < numPropositions; i++)
	{
		if (mode == Props[i]) { return true; }
	}
	return false;
}

string DecialToBinary(int n, int numVar)
{
	int ReversedBinaryArray[32];
	int i = 0;
	while (n > 0)
	{
		ReversedBinaryArray[i] = n % 2;
		// Because n is an "int", deviding n, for example, 5 and 1, by 2, will result in 5 / 2 = 2, and 1 / 2 = 0
		n = n / 2;
		i++;
	}
	string BinaryString;
	for (i = i - 1; i >= 0; i--)
	{
		BinaryString = BinaryString + to_string(ReversedBinaryArray[i]);
	}
	if (BinaryString.size() != numVar)
	{
		string Temp;
		for (int j = 0; j < numVar - BinaryString.size(); j++)
		{
			Temp = Temp + '0';
		}
		BinaryString = Temp + BinaryString;
	}
	return BinaryString;
}

void NegationProp()
{
	string Binary;
	string Array[3][2];
	Array[0][0] = "p";
	Array[0][1] = "~p";

	for (int i = 1; i < 3; i++)
	{
		Binary = DecialToBinary(2 - i, 1);
		for (int j = 0; j < 1; j++)
		{
			Array[i][j] = Binary[j];
			if (Array[i][j] == "0")
			{
				Array[i][j + 1] = "1";
				continue;
			}
			Array[i][j + 1] = "0";
		}
	}
	cout << Array[0][0] << '\t' << Array[0][1] << '\n';
	cout << Array[1][0] << '\t' << Array[1][1] << '\n';
	cout << Array[2][0] << '\t' << Array[2][1] << '\n';
	cout << "----------------------------------------------\n";
}

void OtherProps(string mode)
{
	string Binary;
	string Array[5][3];
	Array[0][0] = "p";
	Array[0][1] = "q";
	Array[0][2] = "p " + mode + " q";

	for (int i = 1; i < 5; i++)
	{
		Binary = DecialToBinary(4 - i, 2);
		for (int j = 0; j < 2; j++)
		{
			Array[i][j] = Binary[j];
		}
		if (mode == "v")
		{
			if (Array[i][0] == "1" || Array[i][1] == "1")
			{
				Array[i][2] = "1";
				continue;
			}
			Array[i][2] = "0";
		}
		if (mode == "^")
		{
			if (Array[i][0] == "1" && Array[i][1] == "1")
			{
				Array[i][2] = "1";
				continue;
			}
			Array[i][2] = "0";
		}
		if (mode == "->")
		{
			if (Array[i][0] == "1" && Array[i][1] == "0")
			{
				Array[i][2] = "0";
				continue;
			}
			Array[i][2] = "1";
		}
		if (mode == "<->")
		{
			if (Array[i][0] == Array[i][1])
			{
				Array[i][2] = "1";
				continue;
			}
			Array[i][2] = "0";
		}
	}
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 3;j++)
		{
			cout << Array[i][j] << '\t';
		}
		cout << '\n';
	}
	cout << "----------------------------------------------\n";
}

void PrintTruthTable(string mode)
{
	if (mode == "~") { NegationProp(); }
	else { OtherProps(mode); }
}

int input()
{
	cout << "(Acceptable Propositions: ~, v, ^, ->, <->, all)\n";
	cout << "(Type 'exit' or nothing then click Enter will stop the program)\n";

	string mode;
	cout << "Enter Proposition: ";
	getline(cin, mode);

	while (!isProp(mode) && mode != "all")
	{
		if (mode == "exit" || mode == "")
		{
			cout << "The program has stopped ...\n";
			return -1;
		}
		cout << "----------------------------------------------\n";
		cout << "'" + mode + "'" + " is not a proposition\n";
		cout << "(Acceptable Propositions: ~, v, ^, ->, <->, all)\n";
		cout << "(Type 'exit' or nothing then click Enter will stop the program)\n";
		cout << "Re-enter Proposition: ";
		getline(cin, mode);
	}
	if (mode == "all")
	{
		for (int i = 0; i < numPropositions; i++)
		{
			cout << "------------------------\n";
			PrintTruthTable(Props[i]);
		}
		return 1;
	}
	else
	{
		cout << "------------------------\n";
		PrintTruthTable(mode);
		return 1;
	}
}

int main()
{
	while (input() == 1) { input(); }
	return 0;
}