// Parser_P2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <vector>
#include <utility>

using namespace std;

int main()
{
	map <pair<string, string>, string > parseTable;
	stack <string> myStack;
	vector <string> input = {"(", "i", "+", "i",")", "*", "i", "$" };
	myStack.push("$");
	myStack.push("E");

	//Parsing Table
	parseTable[{"E", "i"}] = "TE'";
	parseTable[{"E", "("}] = "TE'";
	parseTable[{"E'", "+"}] = "+TE'";
	parseTable[{"E'", ")"}] = "ε";
	parseTable[{"E'", "$"}] = "ε";
	parseTable[{"T", "i"}] = "FT'";
	parseTable[{"T", "("}] = "FT'";
	parseTable[{"T'", "+"}] = "ε";
	parseTable[{"T'","*"}] = "*FT'";
	parseTable[{"T'", ")"}] = "ε";
	parseTable[{"T'", "$"}] = "ε";
	parseTable[{"F", "i"}] = "i";
	parseTable[{"F", "("}] = "(E)";

	//Predictive Parsing Program
	while (myStack.top() != "$")
	{
		if (input.at(0) == myStack.top())
		{
			cout << "match " << input.at(0) << endl;
			myStack.pop();
			input.erase(input.begin());
		}
		else
		{
			string value = parseTable[{myStack.top(), input.at(0)}];
			cout << "output " << myStack.top() << "-->" << value << endl;
			myStack.pop();
			if (value != "ε")
			{
				while (!value.empty())
				{
					string buffer;
					if (value.at(value.length() - 1) != '\'')
					{
						buffer.push_back(value.at(value.length() - 1));
						myStack.push(buffer);
						value.erase(value.length() - 1);
					}
					else
					{
						string x; 
						buffer.push_back(value.at(value.length() - 2));
						buffer.push_back(value.at(value.length() - 1));
						myStack.push(buffer);
						value.erase(value.length() - 2);
					}
					buffer.clear();
				}
			}
		}
	}
    return 0;
}

