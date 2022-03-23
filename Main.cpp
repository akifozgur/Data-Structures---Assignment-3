#include <iostream>
#include "ExecuteTransitionRules.h"
using namespace std;

int main(int argc, char** argv)
{

	string DPDAFile = argv[1];
	string inputFile = argv[2];
	string outputFile = argv[3];

	ExecuteTransitionRules executeTranstitionRule;
	executeTranstitionRule.WriteOnOutputFile(DPDAFile, inputFile, outputFile);
	
}

