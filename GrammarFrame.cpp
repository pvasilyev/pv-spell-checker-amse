#include <iostream>
#include <stdio.h>

#include "GrammarFrame.h"
#include "SyntaxAnalyzer.h"
#include "VLemmatizer.h"

GrammarFrame::GrammarFrame(const std::vector<SourceSentenceUnit> &ssu): mySourceSentenceUnit_GrammarFrame(ssu) {}

void GrammarFrame::buildGrammarFrame() {
	for (std::vector<SourceSentenceUnit>::const_iterator it = (mySourceSentenceUnit_GrammarFrame).begin(); it != (mySourceSentenceUnit_GrammarFrame).end(); ++it ) {
		for (std::vector<WordDescription>::const_iterator jt = (it->myVectorWordDescription).begin(); jt != (it->myVectorWordDescription).end(); ++jt) {
			// существительное + именительный падеж -- кандидат на подлежащее
			if ((*jt).myPartOfSpeech == WordDescription::NOUN && ((*jt).myGrammem & (u_int64_t)WordDescription::NOMINATIV)) {
				bool b = true;
				if (it != mySourceSentenceUnit_GrammarFrame.begin()) {
					--it;
					for (std::vector<WordDescription>::const_iterator kt = (it->myVectorWordDescription).begin(); kt != (it->myVectorWordDescription).end(); ++kt) {
						if ((*kt).myPartOfSpeech == WordDescription::PREPOSAL || ((*kt).myPartOfSpeech == WordDescription::ADJECTIVE_FULL && ((*kt).myGrammem & !(u_int64_t)WordDescription::NOMINATIV))) {
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
			if ((*jt).myPartOfSpeech == WordDescription::PRONOUN && ((*jt).myGrammem & (u_int64_t)WordDescription::NOMINATIV)) {
				bool b = true;
				if (it != mySourceSentenceUnit_GrammarFrame.begin()) {
					--it;
					for (std::vector<WordDescription>::const_iterator kt = (it->myVectorWordDescription).begin(); kt != (it->myVectorWordDescription).end(); ++kt) {
						if ((*kt).myPartOfSpeech == WordDescription::PREPOSAL || ((*kt).myPartOfSpeech == WordDescription::ADJECTIVE_FULL && ((*kt).myGrammem & !(u_int64_t)WordDescription::NOMINATIV))) {
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
			if ((*jt).myPartOfSpeech == WordDescription::VERB) {
				myPredicate.push_back(jt);
				myPredicateText.push_back(it);
			//	std::cerr << it->myText << " ";
			}
		}
	}

}

std::vector<std::vector<WordDescription>::const_iterator> GrammarFrame::getObject() const {
	return myObject;
}

std::vector<std::vector<SourceSentenceUnit>::const_iterator> GrammarFrame::getObjectText() const {
	return myObjectText;
}

std::vector<std::vector<WordDescription>::const_iterator> GrammarFrame::getPredicate() const {
	return myPredicate;
}

std::vector<std::vector<SourceSentenceUnit>::const_iterator> GrammarFrame::getPredicateText() const {
	return myPredicateText;
}

