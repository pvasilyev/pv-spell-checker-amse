#include "vlemmatizer.h"
#include "syntax.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>

int main(int argc, char **argv){

	std::ifstream inFile ("sample.txt");
	std::ofstream outFile ("result.txt");

	std::string sentence;

	while (!inFile.eof()) {
		std::getline(inFile, sentence);
		if (sentence != "") {
			Syntax s(sentence);
			s.parse();
			s.print(std::cout, sentence);
		}
	}

	inFile.close();
	outFile.close();

	return 0;
}
