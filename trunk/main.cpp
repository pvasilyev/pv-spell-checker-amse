#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>

#include "SyntaxAnalyzer.h"
#include "VLemmatizer.h"

int main(int argc, char **argv){

	std::ifstream inFile ("sample.txt");
	std::ofstream outFile ("result.txt");

	std::string sentence;

	while (!inFile.eof()) {
		std::getline(inFile, sentence);
		if (sentence != "") {
			SyntaxAnalyzer s(sentence);
			s.print(outFile);
		}
	}

	inFile.close();
	outFile.close();

	return 0;
}
