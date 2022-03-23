#include "ReadDPDAandInput.h"

vector<string> ReadDPDAandInput::split(string str, char delimiter) {

	vector<string> fullFile;
	stringstream ss(str); // Turn the string into a stream. 
	string tok;
	string lastState;

	while (getline(ss, tok, delimiter)) {

		if (tok[0] == 'Q' || tok[0] == 'A' || tok[0] == 'Z' || tok[0] == 'T') {
			tok.erase(0, 2);
		}
		else if (str[0] == 'Q' && (tok.find("=>") != string::npos)) {
			tok.erase(remove(tok.begin(), tok.end(), ' '), tok.end());
			tok.erase(remove(tok.begin(), tok.end(), '='), tok.end());
			tok.erase(remove(tok.begin(), tok.end(), '>'), tok.end());

			lastState = tok.substr(0, (tok.find('(')));
			fullFile.push_back(lastState);
			tok.erase(0, (tok.find('(')));
		}
		fullFile.push_back(tok);
	}

	return fullFile;
}

void ReadDPDAandInput::readFiles(string fileName) {
	ifstream MyReadFile(fileName);

	while (getline(MyReadFile, line)) {

		fullFile = split(line, ',');

		if (line[0] == 'Q') {

			for (int i = 0;i < fullFile.size();i++) {
				if (fullFile[i][0] == '(') {
					fullFile[i].erase(remove(fullFile[i].begin(), fullFile[i].end(), '('), fullFile[i].end());
					fullFile[i].erase(remove(fullFile[i].begin(), fullFile[i].end(), ')'), fullFile[i].end());
					startState = fullFile[i];
				}
				else if (fullFile[i][0] == '[') {
					fullFile[i].erase(remove(fullFile[i].begin(), fullFile[i].end(), '['), fullFile[i].end());
					fullFile[i].erase(remove(fullFile[i].begin(), fullFile[i].end(), ']'), fullFile[i].end());
					acceptStates.push_back(fullFile[i]);
				}
				else {
					setOfStates.push_back(fullFile[i]);
				}
			}
			fullFile.clear();
		}
		else if (line[0] == 'A') {
			inputAlphabet = split(line, ',');
			fullFile.clear();
		}
		else if (line[0] == 'Z') {
			stackAlphabet = split(line, ',');
			fullFile.clear();
		}
		else if (line[0] == 'T') {
			transitionRule = split(line, ',');
			transitionRules.push_back(transitionRule);
			fullFile.clear();
		}
		else {
			inputLine = split(line, ',');
			inputLines.push_back(inputLine);
			fullFile.clear();
		}

	}

	MyReadFile.close();
}
