#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;




class ReadDPDAandInput
{
private:
	vector<string> fullFile;
	string line;
	vector<string> inputLine;
	vector<string> transitionRule;
	vector<string>	split(string str, char delimiter);
	
public:

	// Line starting with "Q";
	vector<string> setOfStates;
	string startState;
	vector<string> acceptStates;

	// Line starting with "A";
	vector<string> inputAlphabet;

	// Line starting with "Z";
	vector<string> stackAlphabet;

	// Line starting with "Z";
	vector<vector<string>> transitionRules;

	// Input Lines;
	vector<vector<string>> inputLines;

	void readFiles(string fileName);
};

