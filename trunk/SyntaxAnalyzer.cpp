#include <iostream>
#include <ostream>
#include <string>

#include "SyntaxAnalyzer.h"
#include "ComplexSentence.h"
#include "SimpleSentence.h"
#include "VLemmatizer.h"

SyntaxAnalyzer::SyntaxAnalyzer(std::string &sentence) {


// parse words and symbols like ','
// get vector of mySentenceUnit: symbol or word

	std::string temp;
	for (std::string::iterator it = sentence.begin(); it != sentence.end(); ++it) {
		if (temp.empty()) {
			if ((*it) == '"' || (*it) == '\'' || (*it) == '-') {
				temp.push_back(*it);
				mySentenceUnit.push_back(temp);
				temp.clear();
			}
			else {
				if ((*it) != ' ') temp.push_back(*it);
			}
		}
		else {
			if ((*it) == ' ') {
				mySentenceUnit.push_back(temp);
				temp.clear();
			}
			else {
				if ((*it) == ',' || (*it) == ':' || (*it) == ';' || (*it) == '-' || (*it) == '"' || (*it) == '\'' || (*it) == '!' || (*it) == '?' || (*it) == '.') {
					mySentenceUnit.push_back(temp);
					temp.clear();
					temp.push_back(*it);
					mySentenceUnit.push_back(temp);
					temp.clear();
				}
				else {
					temp.push_back((*it));
				}
			}
		}
	}
	if (!temp.empty()) mySentenceUnit.push_back(temp);


// get WordDescription (s) of all SentenceUnits

	VLemmatizer lem;

	for (std::vector<std::string>::iterator it = mySentenceUnit.begin(); it != mySentenceUnit.end(); ++it) {
		SourceSentenceUnit tmp;
		if (isWord(*it)) {
			std::vector<WordDescription> result = lem.lemmatize(*it);
		//	tmp.isWord = true;
		//	tmp.myWD = result;
		//	tmp.myText = (*it);
		}
		else {
			std::vector<WordDescription> result;
		//	tmp.isWord = false;
		//	tmp.myWD = result;
		//	tmp.myText = (*it);
		}
		std::cerr << "!";
		mySSUnits->push_back(tmp);
	}

	ComplexSentence *p = new ComplexSentence(*mySSUnits);
	myComplexSentence = p;
}

SyntaxAnalyzer::~SyntaxAnalyzer() {
	delete myComplexSentence;
}

bool SyntaxAnalyzer::isWord(std::string &string) const {

	bool b = (string.find(',') != std::string::npos || string.find(':') != std::string::npos || string.find(';') != std::string::npos || string.find('-') != std::string::npos || string.find('"') != std::string::npos || string.find('\'') != std::string::npos || string.find('!') != std::string::npos || string.find('?') != std::string::npos || string.find('.') != std::string::npos);

	if (b) return false;
	else return true;
}

bool isPredicateInCoordination(std::vector<std::vector<WordDescription> > &predicate) {

	bool b = true;
//	for (std::vector<std::vector>)
	return b;
}

void SyntaxAnalyzer::print(std::ostream &os) {
	myComplexSentence->print_cs(os);
//	os << sent << "\n" << "\n";
//	os << "Варианты подлежащего:" << "\n";
//	for (std::vector<std::string>::iterator it = myObject.begin(); it != myObject.end(); ++it) {
//		os << (*it) << "\n";
//	}
//	os << "Варианты сказуемого:" << "\n";
//	for (std::vector<std::string>::iterator it = myPredicate.begin(); it != myPredicate.end(); ++it) {
//		os << (*it) << "\n";
//	}
//	os << "\n";
}

void SyntaxAnalyzer::parse() {
// разбор
	myComplexSentence->parse_cs();

}
