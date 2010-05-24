#include <cstdio>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

#include "SyntaxAnalyzer.h"
#include "VLemmatizer.h"

class file {

public:

	std::string inFile;
	std::string outFile;
	std::string goldFile;

	file(const std::string &in, const std::string &out, const std::string &gold): inFile(in), outFile(out), goldFile(gold) {}

};

void compareOutAndGold(const std::string &out, const std::string &gold) {

	std::ifstream os(out.data());
	std::ifstream gs(gold.data());
	std::string strO;
	std::string strG;

	bool bCont = (!os.eof() && !gs.eof());

	while (bCont) {
		std::getline(os, strO);
		std::getline(gs, strG);

		if (strO != strG) {
			std::cout << "Wrong answer!" << "\n";
			bCont = false;
		}
		else if (os.eof() || gs.eof()) {
			if (os.eof() && gs.eof()) {
				std::cout << "100 \% accepts!" << "\n";
				bCont = false;
			}
			else {
				std::cout << "Lengths not equal!" << "\n";
				bCont = false;
			}
		}
	}

	os.close();
	gs.close();
}

int main(int argc, char **argv){

	std::ifstream iFile ("sample.txt");
	std::ofstream oFile ("result.txt");

	std::vector<file> inFileList;

	for (int i = 0; i != 20; ++i) {
		std::string dir("./testing/");
		std::stringstream ss;
		ss << i + 1;
		std::string num = ss.str();
		std::string in(".in");
		std::string out(".out");
		std::string gold(".gold");
		file tmp(dir + num + in, dir + num + out, dir + num + gold);
		inFileList.push_back(tmp);
	}

	std::string sentence;

	for (std::vector<file>::const_iterator it = inFileList.begin(); it != inFileList.end(); ++it) {
		std::ifstream inFile((it->inFile).data());
		std::ofstream outFile((it->outFile).data());

		std::getline(inFile, sentence);

		SyntaxAnalyzer sa(sentence);
		sa.print(outFile);

		inFile.close();
		outFile.close();

		compareOutAndGold(it->outFile, it->goldFile);

	}

	while (!iFile.eof()) {
		std::getline(iFile, sentence);
		if (sentence != "") {
			SyntaxAnalyzer s(sentence);
			oFile << sentence << std::endl;
			s.print(oFile);
		}
	}

	iFile.close();
	oFile.close();
	
	return 0;
}

