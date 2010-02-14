#include "vlemmatizer.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>

int main(int argc, char **argv){
	VLemmatizer lem;

	std::ifstream inFile ("sample.txt");
	std::ofstream outFile ("result.txt");

	std::string src;

	while (!inFile.eof()){
		inFile >> src;

		// очистка от ',', '.', '"', ''', ':', '!', '?'
		if (src[0] == '"') {
			src.erase(src.begin());
		}
		if ((src[src.length()-1] == ',') || (src[src.length()-1] == '.') || (src[src.length()-1] == '"') || (src[src.length()-1] == '!') || (src[src.length()-1] == '?')) {
			src.erase(src.length() - 1, 1);
		}
		if ((src[src.length()-1] == ',') || (src[src.length()-1] == '.') || (src[src.length()-1] == '"') || (src[src.length()-1] == '!') || (src[src.length()-1] == '?')) {
			src.erase(src.length() - 1, 1);
		}
		// конец очистки

		std::vector<WordDescription> res = lem.lemmatize(src);
		outFile << src << "\n";

		for (std::vector<WordDescription>::iterator it = res.begin(); it != res.end(); ++it){
			outFile << "\n" ;
			it->printPartOfSpeech(outFile);
			it->printGrammems(outFile);
		}

		outFile << "\n" ;
	}


	inFile.close();
	outFile.close();

	return 0;
}
