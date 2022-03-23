#include "ExecuteTransitionRules.h"

void ExecuteTransitionRules::PrintStack(stack<string> s)
{
	if (s.empty())
		return;
	string x = s.top();
	s.pop();
	PrintStack(s);
	printStack.append(x+",");
	s.push(x);
}

void ExecuteTransitionRules::WriteOnOutputFile(string dpdaFile, string inputFile, string outputFile) {

	
	outfile.open(outputFile);
	
	ReadDPDAandInput readFile;
	readFile.readFiles(dpdaFile);
	readFile.readFiles(inputFile);

	setOfStates = readFile.setOfStates;
	startState = readFile.startState;
	originalStartState = readFile.startState;
	acceptStates = readFile.acceptStates;
	inputAlphabet = readFile.inputAlphabet;
	stackAlphabet = readFile.stackAlphabet;
	transitionRules = readFile.transitionRules;
	inputLines = readFile.inputLines;

	ExecuteDPDA();
}

void ExecuteTransitionRules::ExecuteDPDA(){

	if ((counter2 == 0) && (!CheckTransitionRules())) {
		outfile << "Error [1]:DPDA description is invalid!" << endl;
	}
	else if ((counter2 == 0) && (!CheckInputFile())) {
		outfile << "Error [2]:Input description is invalid!" << endl;
	}
	else if ((count(acceptStates.begin(), acceptStates.end(), startState)) && (inputLines[inputLine].size() == 0)) {
		counter2 = 1;
		outfile << "ACCEPT" << endl;
		outfile << endl;

		inputLine += 1;
		startState = originalStartState;
		ExecuteDPDA();
	}
	else if ( (!(count(acceptStates.begin(), acceptStates.end(), startState))) && (inputLines[inputLine].size() == 0)) {
		counter2 = 1;
		outfile << "REJECT" << endl;
		outfile << endl;

		inputLine += 1;
		startState = originalStartState;
		ExecuteDPDA();
	}

	else if (!isThereValidRule) {
		counter2 = 1;
		outfile << "REJECT" << endl;
		outfile << endl;

		inputLine += 1;
		inputLetter = 0;
		startState = originalStartState;
		isThereValidRule = true;
		for (int i = 0;i < stackDPDA.size();i++) {
			stackDPDA.pop();
		}
		ExecuteDPDA();
	}
	else if (inputLines[inputLine].size() > inputLetter) {
		counter2 = 1;
		ExecuteTransitionRule();
	}
	else {
		counter2 = 1;
		if (inputLines.size() > inputLine) {
			if (counter == 0) {
				counter += 1;
				inputLetter -= 1;
				ExecuteTransitionRule();
			}
			else if ((count(acceptStates.begin(), acceptStates.end(), startState)) && ((stackDPDA.size() == 0) || stackDPDA.top() == "$")) {
				outfile<< "ACCEPT" << endl;
				outfile << endl;
			}
			else {
				outfile << "REJECT" << endl;
				outfile << endl;
			}
			inputLine += 1;
			inputLetter = 0;
			counter = 0;
			if (inputLines.size() > inputLine) {
				startState = originalStartState;
				for (int i = 0;i < stackDPDA.size();i++) {
					stackDPDA.pop();
				}
				ExecuteDPDA();
			}
			
		}
		outfile.close();
	}
}

void ExecuteTransitionRules::ExecuteTransitionRule() {

	isThereValidRule = false;

	for (vector<string> transitionRule : transitionRules) {
		if (stackDPDA.size() == 0) {
			if (transitionRule[0] == startState && (((transitionRule[1] == inputLines[inputLine][inputLetter]) || (transitionRule[1] == "e")) && (transitionRule[2] == "e"))) {

				isThereValidRule = true;
				startState = transitionRule[3];

				if (transitionRule[4] != "e") {
					stackDPDA.push(transitionRule[4]);
				}
				if (transitionRule[1] == inputLines[inputLine][inputLetter]) {
					inputLetter += 1;
				}

				outfile << transitionRule[0] << "," << transitionRule[1] << "," << transitionRule[2] << " => " << transitionRule[3] << "," << transitionRule[4] << " [STACK]:";
				PrintStack(stackDPDA);
				outfile << printStack.substr(0, printStack.size() - 1) << endl;
				printStack = "";

				if (counter == 1) {
					inputLetter += 1;
				}

				ExecuteDPDA();
				break;
			}
		}
		else {
			if (transitionRule[0] == startState && (((transitionRule[1] == inputLines[inputLine][inputLetter]) || (transitionRule[1] == "e")) && ((transitionRule[2] == "e") || (transitionRule[2] == stackDPDA.top())))) {

				isThereValidRule = true;
				startState = transitionRule[3];

				if (transitionRule[4] != "e") {
					stackDPDA.push(transitionRule[4]);
				}
				if (transitionRule[2] == stackDPDA.top()) {
					stackDPDA.pop();
				}

				if (transitionRule[1] == inputLines[inputLine][inputLetter]) {
					inputLetter += 1;
				}

				outfile << transitionRule[0] << "," << transitionRule[1] << "," << transitionRule[2] << " => " << transitionRule[3] << "," << transitionRule[4] << " [STACK]:";
				PrintStack(stackDPDA);
				outfile << printStack.substr(0, printStack.size() - 1) << endl;
				printStack = "";

				if (counter == 1) {
					inputLetter += 1;
				}

				ExecuteDPDA();
				break;
			}
		}
	}
	if (inputLines.size() > inputLine) {
		ExecuteDPDA();
	}
}

bool ExecuteTransitionRules::CheckTransitionRules() {

	for (vector<string> transitionRule : transitionRules) {
	
		if (((find(setOfStates.begin(), setOfStates.end(), transitionRule[0]) == setOfStates.end()))
			|| ((find(setOfStates.begin(), setOfStates.end(), transitionRule[3]) == setOfStates.end()))
			|| (((find(stackAlphabet.begin(), stackAlphabet.end(), transitionRule[2]) == stackAlphabet.end()) && (transitionRule[2] != "e")))
			|| (((find(stackAlphabet.begin(), stackAlphabet.end(), transitionRule[4]) == stackAlphabet.end()) && (transitionRule[4] != "e")))
			|| (((find(inputAlphabet.begin(), inputAlphabet.end(), transitionRule[1]) == inputAlphabet.end()) && (transitionRule[1] != "e")))) {
			return false;
		}
	}
	return true;
}

bool ExecuteTransitionRules::CheckInputFile() {

	for (vector<string> inputLine : inputLines) {
		for (string input : inputLine) {
			if ((find(inputAlphabet.begin(), inputAlphabet.end(), input) == inputAlphabet.end())) {
				return false;
			}
		}
	}
	return true;
}


