#include <iostream>

#include "GrammarFrame.h"
#include "SyntaxAnalyzer.h"
#include "VLemmatizer.h"

GrammarFrame::GrammarFrame(std::vector<SourceSentenceUnit> &ssu) {
	mySSU_GF = ssu;
}

void GrammarFrame::buildGrammarFrame() {
//std::cerr << "!";
	for (std::vector<SourceSentenceUnit>::iterator it = (mySSU_GF).begin(); it != (mySSU_GF).end(); ++it ) {
		for (std::vector<WordDescription>::iterator jt = (it->myWD).begin(); jt != (it->myWD).end(); ++jt) {
			// существительное + именительный падеж -- кандидат на подлежащее
			if ((*jt).myPartOfSpeech == 0 && ((*jt).myGrammem & ((u_int64_t)1 << 2))) {
				bool b = true;
				if (it != mySSU_GF.begin()) {
					--it;
					for (std::vector<WordDescription>::iterator kt = (it->myWD).begin(); kt != (it->myWD).end(); ++kt) {
						if ((*kt).myPartOfSpeech == 10 || ((*kt).myPartOfSpeech == 1 && ((*kt).myGrammem & !(u_int64_t)1 << 2))) {
							b = false;
						}
					}
					++it;
				}
				if (b) {
					myObject.push_back(jt);
					myObjectText.push_back(it);
				}
			}

			// местоимение + именительный падеж -- кандидат на подлежащее
			if ((*jt).myPartOfSpeech == 3 && ((*jt).myGrammem & ((u_int64_t)1 << 2))) {
				bool b = true;
				if (it != mySSU_GF.begin()) {
					--it;
					for (std::vector<WordDescription>::iterator kt = (it->myWD).begin(); kt != (it->myWD).end(); ++kt) {
						if ((*kt).myPartOfSpeech == 10 || ((*kt).myPartOfSpeech == 1 && ((*kt).myGrammem & !(u_int64_t)1 << 2))) {
							b = false;
						}
					}
					++it;
				}
				if (b) {
					myObject.push_back(jt);
					myObjectText.push_back(it);
				}
			}

			// глагол -- кандидат на сказуемое 
			if ((*jt).myPartOfSpeech == 2) {
				myPredicate.push_back(jt);
				myPredicateText.push_back(it);
			}
		}
	}
//std::cerr << "!";

/*
// a priori выкинуть неподходящее сказуемое
	VLemmatizer lem_temp;
	std::vector<std::vector<WordDescription> > predicate;
	for (std::vector<std::string>::iterator it = myPredicate.begin(); it != myPredicate.end(); ++it) {
		std::vector<WordDescription> temp = lem_temp.lemmatize(*it);
		predicate.push_back(temp);
	}
*/

// a priori выкинуть неподходящее подлежащее
/*	for (std::vector<std::vector<WordDescription>::iterator>::iterator it = myObject.begin(); it != myObject.end(); ++it) {
		if (it != myObject.begin()) {
			--it;
			if ((*it)->myPartOfSpeech == 3 || (*it)->myPartOfSpeech == 4 || (*it)->myPartOfSpeech == 5 || ((*it)->myPartOfSpeech == 1 && ((*it)->myGrammem & !(u_int64_t)1 << 10))) {
				myObject.erase(it);
				myObjectText.erase(myObjectText.begin() + (it - myObject.begin()));
			}
			++it;
		}
	}
*/
}

std::vector<std::vector<WordDescription>::iterator> GrammarFrame::getObject() const {
	return myObject;
}

std::vector<std::vector<SourceSentenceUnit>::iterator> GrammarFrame::getObjectText() const {
	return myObjectText;
}

std::vector<std::vector<WordDescription>::iterator> GrammarFrame::getPredicate() const {
	return myPredicate;
}

std::vector<std::vector<SourceSentenceUnit>::iterator> GrammarFrame::getPredicateText() const {
	return myPredicateText;
}

std::vector<std::vector<WordDescription>::iterator> GrammarFrame::getGrammarFrame() {
	return myGrammarFrame;
}
