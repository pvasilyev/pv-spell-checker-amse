#include <iostream>
#include <ostream>
#include <string>

#include "SyntaxAnalyzer.h"
#include "ComplexSentence.h"
#include "SimpleSentence.h"
#include "VLemmatizer.h"

SyntaxAnalyzer::SyntaxAnalyzer(const std::string &sentence) {


// parse words and symbols like ','
// get vector of mySentenceUnit: symbol or word

	std::string temp;
	for (std::string::const_iterator it = sentence.begin(); it != sentence.end(); ++it) {
		if (temp.empty()) {
			if ((*it) == '"' || (*it) == '\'' || (*it) == '-') {
				temp.push_back(*it);
				mySentenceUnits.push_back(temp);
				temp.clear();
			}
			else {
				if ((*it) != ' ') temp.push_back(*it);
			}
		}
		else {
			if ((*it) == ' ') {
				mySentenceUnits.push_back(temp);
				temp.clear();
			}
			else {
				static const std::string specialChars = ",:;-\"'!?.";
				if (specialChars.find(*it) != std::string::npos) {
					mySentenceUnits.push_back(temp);
					temp.clear();
					temp.push_back(*it);
					mySentenceUnits.push_back(temp);
					temp.clear();
				}
				else {
					temp.push_back((*it));
				}
			}
		}

	}
	if (!temp.empty()) mySentenceUnits.push_back(temp);


// get WordDescription (s) of all SentenceUnits

	VLemmatizer lem;

	for (std::vector<std::string>::const_iterator it = mySentenceUnits.begin(); it != mySentenceUnits.end(); ++it) {
		SentenceUnit tmp;
		if (isWord(*it)) {
			std::vector<WordDescription> result = lem.lemmatize(*it);
			tmp.myIsWord = true;
			tmp.myVectorWordDescription = result;
			tmp.myText = (*it);
		}
		else {
			std::vector<WordDescription> result;
			tmp.myIsWord = false;
			tmp.myVectorWordDescription = result;
			tmp.myText = (*it);
		}
		myVectorSentenceUnit.push_back(tmp);
	}

	myComplexSentence = new ComplexSentence(myVectorSentenceUnit);
}

SyntaxAnalyzer::~SyntaxAnalyzer() {
	delete myComplexSentence;
}

bool SyntaxAnalyzer::isWord(const std::string &string) const {
	return
		string.find(',') == std::string::npos &&
		string.find(':') == std::string::npos &&
		string.find(';') == std::string::npos &&
		string.find('-') == std::string::npos &&
		string.find('"') == std::string::npos &&
		string.find('\'') == std::string::npos &&
		string.find('!') == std::string::npos &&
		string.find('?') == std::string::npos &&
		string.find('.') == std::string::npos;
}

void SyntaxAnalyzer::print(std::ostream &os) {
	myComplexSentence->print(os);
}

