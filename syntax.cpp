#include "syntax.h"
#include <string>
#include <ostream>
#include <iostream>

Syntax::Syntax(std::string &sentence) {


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
		if (isWord(*it)) {
			std::vector<WordDescription> result = lem.lemmatize(*it);
			myWordDescription.push_back(result);
		}
		else {
			std::vector<WordDescription> result;
			myWordDescription.push_back(result);
		}
	}
}


bool Syntax::isWord(std::string &string) const {

	bool b = (string.find(',') != std::string::npos || string.find(':') != std::string::npos || string.find(';') != std::string::npos || string.find('-') != std::string::npos || string.find('"') != std::string::npos || string.find('\'') != std::string::npos || string.find('!') != std::string::npos || string.find('?') != std::string::npos || string.find('.') != std::string::npos);

	if (b) return false;
	else return true;
}


void Syntax::print(std::ostream &os, std::string &sent) {
	os << sent << "\n" << "\n";
	os << "Варианты подлежащего:" << "\n";
	for (std::vector<std::string>::iterator it = myObject.begin(); it != myObject.end(); ++it) {
		os << (*it) << "\n";
	}
	os << "Варианты сказуемого:" << "\n";
	for (std::vector<std::string>::iterator it = myPredicate.begin(); it != myPredicate.end(); ++it) {
		os << (*it) << "\n";
	}
	os << "\n";
}

void Syntax::parse() {
	for (std::vector<std::vector<WordDescription> >::iterator it = myWordDescription.begin(); it != myWordDescription.end(); ++it ) {
		for (std::vector<WordDescription>::iterator jt = it->begin(); jt != it->end(); ++jt) {
			// существительное + именительный падеж
			if ((*jt).myPartOfSpeech == 0 && ((*jt).myGrammem & ((u_int64_t)1 << 2))) {
				myObject.push_back(mySentenceUnit[it - myWordDescription.begin()]);
			}

			// местоимение + именительный падеж
			if ((*jt).myPartOfSpeech == 3 && ((*jt).myGrammem & ((u_int64_t)1 << 2))) {
				myObject.push_back(mySentenceUnit[it - myWordDescription.begin()]);
			}

			// глагол
			if ((*jt).myPartOfSpeech == 2) {
				myPredicate.push_back(mySentenceUnit[it - myWordDescription.begin()]);
			}
		}
	}
}
