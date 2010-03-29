#include <iostream>
#include <stdio.h>

#include "GrammarFrame.h"
#include "SyntaxAnalyzer.h"
#include "VLemmatizer.h"

GrammarFrame::GrammarFrame(const std::vector<SentenceUnit> &su): mySentenceUnit(su) {}

void GrammarFrame::buildGrammarFrame() {
	for (std::vector<SentenceUnit>::const_iterator it = (mySentenceUnit).begin(); it != (mySentenceUnit).end(); ++it ) {
		for (std::vector<WordDescription>::const_iterator jt = (it->myVectorWordDescription).begin(); jt != (it->myVectorWordDescription).end(); ++jt) {
			// существительное + именительный падеж -- кандидат на подлежащее
			if ((*jt).myPartOfSpeech == WordDescription::NOUN && ((*jt).myGrammem & (u_int64_t)WordDescription::NOMINATIV)) {
				bool b = true;
				if (it != mySentenceUnit.begin()) {
					--it;
					for (std::vector<WordDescription>::const_iterator kt = (it->myVectorWordDescription).begin(); kt != (it->myVectorWordDescription).end(); ++kt) {
						if ((*kt).myPartOfSpeech == WordDescription::PREPOSAL || ((*kt).myPartOfSpeech == WordDescription::ADJECTIVE_FULL && ((*kt).myGrammem & !(u_int64_t)WordDescription::NOMINATIV))) {
							b = false;
						}
					}
					++it;
				}
				if (b) {
					myObject.push_back(*jt);
					myObjectText.push_back(*it);
				}
			}

			// местоимение + именительный падеж -- кандидат на подлежащее
			if ((*jt).myPartOfSpeech == WordDescription::PRONOUN && ((*jt).myGrammem & (u_int64_t)WordDescription::NOMINATIV)) {
				bool b = true;
				if (it != mySentenceUnit.begin()) {
					--it;
					for (std::vector<WordDescription>::const_iterator kt = (it->myVectorWordDescription).begin(); kt != (it->myVectorWordDescription).end(); ++kt) {
						if ((*kt).myPartOfSpeech == WordDescription::PREPOSAL || ((*kt).myPartOfSpeech == WordDescription::ADJECTIVE_FULL && ((*kt).myGrammem & !(u_int64_t)WordDescription::NOMINATIV))) {
							b = false;
						}
					}
					++it;
				}
				if (b) {
					myObject.push_back(*jt);
					myObjectText.push_back(*it);
				}
			}

			// глагол -- кандидат на сказуемое 
			if ((*jt).myPartOfSpeech == WordDescription::VERB) {
				myPredicate.push_back(*jt);
				myPredicateText.push_back(*it);
			}
		}
	}

}

std::vector<WordDescription> GrammarFrame::getObject() const {
	return myObject;
}

std::vector<SentenceUnit> GrammarFrame::getObjectText() const {
	return myObjectText;
}

std::vector<WordDescription> GrammarFrame::getPredicate() const {
	return myPredicate;
}

std::vector<SentenceUnit> GrammarFrame::getPredicateText() const {
	return myPredicateText;
}

