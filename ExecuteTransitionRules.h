#pragma once
#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
#include "ReadDPDAandInput.h"


class ExecuteTransitionRules
{
private:
	ofstream outfile;
	stack<string> stackDPDA;
	string printStack;
	int inputLine = 0;
	int inputLetter = 0;
	int counter = 0;
	int counter2 = 0;
	bool isThereValidRule = true;
	void ExecuteDPDA();
	void ExecuteTransitionRule();
	bool CheckTransitionRules();
	bool CheckInputFile();
	void PrintStack(stack<string> s);

	// Line starting with "Q";
	vector<string> setOfStates;
	string startState;
	string originalStartState;
	vector<string> acceptStates;

	// Line starting with "A";
	vector<string> inputAlphabet;

	// Line starting with "Z";
	vector<string> stackAlphabet;

	// Line starting with "Z";
	vector<vector<string>> transitionRules;

	// Input Lines;
	vector<vector<string>> inputLines;

public:
	void WriteOnOutputFile(string dpdaFile, string inputFile, string outputFile);
};

