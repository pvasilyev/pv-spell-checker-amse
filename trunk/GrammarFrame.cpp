#include <iostream>
#include <stdio.h>

#include "GrammarFrame.h"
#include "SyntaxAnalyzer.h"
#include "VLemmatizer.h"

GrammarFrame::GrammarFrame(const std::vector<SentenceUnit> &su): mySentenceUnits(su) {}

void GrammarFrame::buildGrammarFrame() {
	for (std::vector<SentenceUnit>::const_iterator it = (mySentenceUnits).begin();
	it != (mySentenceUnits).end(); ++it ) {
		for (std::vector<WordDescription>::const_iterator jt = (it->myVectorWordDescription).begin();
		jt != (it->myVectorWordDescription).end(); ++jt) {
			tryToAddSubject(it, jt);

			// глагол -- кандидат на сказуемое 
			if ((jt)->hasPart(WordDescription::VERB)) {
				myPredicate.push_back(*jt);
				myPredicateText.push_back(*it);
			}
		}
	}

	myPredicatesInCoordination = checkPredicateCoordination();
	mySubjectsInCoordination = checkSubjectCoordination();
	doFiltration(mySubjectsInCoordination, myPredicatesInCoordination);
}

void GrammarFrame::tryToAddSubject(std::vector<SentenceUnit>::const_iterator it,
				std::vector<WordDescription>::const_iterator jt) {
			// существительное + именительный падеж -- кандидат на подлежащее
			if ((jt->hasPart(WordDescription::NOUN) || jt->hasPart(WordDescription::PRONOUN) ) &&
			(jt->hasGrammem(WordDescription::NOMINATIV))) {
				bool b = true;
				if (it != mySentenceUnits.begin()) {
					--it;
					for (std::vector<WordDescription>::const_iterator kt = (it->myVectorWordDescription).begin();
					kt != (it->myVectorWordDescription).end(); ++kt) {
						if ((kt)->hasPart(WordDescription::PREPOSAL) ||
						((kt)->hasPart(WordDescription::ADJECTIVE_FULL) &&
						(!(kt)->hasGrammem(WordDescription::NOMINATIV)))) {
							b = false;
						}
					}
					++it;
				}
				if (b) {
					mySubject.push_back(*jt);
					mySubjectText.push_back(*it);
				}
			}

}

bool GrammarFrame::checkPredicateCoordination() const {
	if (!myPredicate.empty()) {
		const WordDescription &firstPredicate = (myPredicate.at(0));
		for (std::vector<WordDescription>::const_iterator it = myPredicate.begin();
		     it != myPredicate.end(); ++it) {
			if (!it->areCoordinatedGrammem(firstPredicate, WordDescription::PLURAL) ||
			    !it->areCoordinatedGrammem(firstPredicate, WordDescription::SINGULAR) ||
			    !it->areCoordinatedGrammem(firstPredicate, WordDescription::MASCULINUM) ||
			    !it->areCoordinatedGrammem(firstPredicate, WordDescription::FEMINUM) ||
			    !it->areCoordinatedGrammem(firstPredicate, WordDescription::NEUTRUM) ||
			    !it->areCoordinatedGrammem(firstPredicate, WordDescription::PASTTENSE) ||
			    !it->areCoordinatedGrammem(firstPredicate, WordDescription::PRESENTTENSE) ||
			    !it->areCoordinatedGrammem(firstPredicate, WordDescription::FUTURETENSE)) {
				return false;
				break;
			}
		}
	}
	return true;
}
 
bool GrammarFrame::checkSubjectCoordination() const {
	if (!mySubject.empty()) {
		const WordDescription &firstSubject = (mySubject.at(0));
		for (std::vector<WordDescription>::const_iterator it = mySubject.begin();
		     it != mySubject.end(); ++it) {
			if (!it->areCoordinatedGrammem(firstSubject, WordDescription::PLURAL) ||
			    !it->areCoordinatedGrammem(firstSubject, WordDescription::SINGULAR) ||
			    !it->areCoordinatedGrammem(firstSubject, WordDescription::MASCULINUM) ||
			    !it->areCoordinatedGrammem(firstSubject, WordDescription::FEMINUM) ||
			    !it->areCoordinatedGrammem(firstSubject, WordDescription::NEUTRUM) ||
			    !it->areCoordinatedPart(firstSubject, WordDescription::NOUN) ||
			    !it->areCoordinatedPart(firstSubject, WordDescription::PRONOUN)) {
				return false;
				break;
			}
		}
	}
	return true;
}

void GrammarFrame::doFiltration(bool subjectsInCoordination, bool predicatesInCoordination) {
	if (subjectsInCoordination && !predicatesInCoordination) {
		// фильтр по числу
		for (std::vector<WordDescription>::iterator it = myPredicate.begin();
		it != myPredicate.end(); ++it) {
			
		}
		// фильтр по роду
		for (std::vector<WordDescription>::iterator it = myPredicate.begin();
		it != myPredicate.end(); ++it) {
			
		}
	} else
	if (!subjectsInCoordination && predicatesInCoordination) {
		// фильтр по числу
		for (std::vector<WordDescription>::iterator it = mySubject.begin();
		it != mySubject.end(); ++it) {
			
		}

		// фильтр по роду
		for (std::vector<WordDescription>::iterator it = mySubject.begin();
		it != mySubject.end(); ++it) {
			
		}
	} else
	if (!subjectsInCoordination && !predicatesInCoordination) {
		// NP-hard problem :)
	}
}
 
std::vector<WordDescription> GrammarFrame::getSubject() const {
	return mySubject;
}

std::vector<SentenceUnit> GrammarFrame::getSubjectText() const {
	return mySubjectText;
}

std::vector<WordDescription> GrammarFrame::getPredicate() const {
	return myPredicate;
}

std::vector<SentenceUnit> GrammarFrame::getPredicateText() const {
	return myPredicateText;
}


