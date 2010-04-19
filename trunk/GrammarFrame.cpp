#include <iostream>
#include <stdio.h>

#include "GrammarFrame.h"
#include "SyntaxAnalyzer.h"
#include "VLemmatizer.h"

GrammarFrame::GrammarFrame(const std::vector<SentenceUnit> &su): mySentenceUnits(su) {

	for (std::vector<SentenceUnit>::const_iterator it = mySentenceUnits.begin();
		it != mySentenceUnits.end(); ++it ) {
		for (std::vector<WordDescription>::const_iterator jt = (it->myVectorWordDescription).begin();
			jt != (it->myVectorWordDescription).end(); ++jt) {
			tryToAddSubject(it, jt);

			// глагол -- кандидат на сказуемое 
			if ((jt)->hasPart(WordDescription::VERB)) {
				SentencePart sp;
				sp.myWordDescription = (*jt);
				sp.mySentenceUnit = *it;
				myPredicateSentencePart.push_back(sp);
			}
		}
	}

	bool myPredicatesInCoordination = checkPredicateCoordination();
	bool mySubjectsInCoordination = checkSubjectCoordination();
	doFiltration(mySubjectsInCoordination, myPredicatesInCoordination);
}

void GrammarFrame::tryToAddSubject(std::vector<SentenceUnit>::const_iterator it,
				std::vector<WordDescription>::const_iterator jt) {
			// существительное или местоимение + именительный падеж -- кандидат на подлежащее
			if ((jt->hasPart(WordDescription::NOUN) || jt->hasPart(WordDescription::PRONOUN)) &&
				(jt->hasGrammem(WordDescription::NOMINATIV))) {
				bool b = true;
				if (it != mySentenceUnits.begin()) {
					const std::vector<SentenceUnit>::const_iterator previous = it - 1;
					for (std::vector<WordDescription>::const_iterator
						kt = (previous->myVectorWordDescription).begin();
						kt != (previous->myVectorWordDescription).end(); ++kt) {
						if ((kt)->hasPart(WordDescription::PREPOSAL) ||
							((kt)->hasPart(WordDescription::ADJECTIVE_FULL) &&
							(!(kt)->hasGrammem(WordDescription::NOMINATIV)))) {
							b = false;
						}
					}
				}
				if (b) {
					SentencePart sp;
					sp.myWordDescription = (*jt);
					sp.mySentenceUnit = *it;
					mySubjectSentencePart.push_back(sp);
				}
			}

}

bool GrammarFrame::checkPredicateCoordination() const {
	if (!myPredicateSentencePart.empty()) {
		const WordDescription &firstPredicate = (myPredicateSentencePart.at(0)).myWordDescription;
		for (std::vector<SentencePart>::const_iterator it = myPredicateSentencePart.begin();
		     it != myPredicateSentencePart.end(); ++it) {
			if (!(it->myWordDescription).areCoordinatedGrammem(firstPredicate, WordDescription::PLURAL) ||
			    !(it->myWordDescription).areCoordinatedGrammem(firstPredicate, WordDescription::SINGULAR) ||
			    !(it->myWordDescription).areCoordinatedGrammem(firstPredicate, WordDescription::MASCULINUM) ||
			    !(it->myWordDescription).areCoordinatedGrammem(firstPredicate, WordDescription::FEMINUM) ||
			    !(it->myWordDescription).areCoordinatedGrammem(firstPredicate, WordDescription::NEUTRUM) ||
			    !(it->myWordDescription).areCoordinatedGrammem(firstPredicate, WordDescription::PASTTENSE) ||
			    !(it->myWordDescription).areCoordinatedGrammem(firstPredicate, WordDescription::PRESENTTENSE) ||
			    !(it->myWordDescription).areCoordinatedGrammem(firstPredicate, WordDescription::FUTURETENSE)) {
				return false;
				break;
			}
		}
	}
	return true;
}
 
bool GrammarFrame::checkSubjectCoordination() const {
	if (!mySubjectSentencePart.empty()) {
		const WordDescription &firstSubject = (mySubjectSentencePart.at(0)).myWordDescription;
		for (std::vector<SentencePart>::const_iterator it = mySubjectSentencePart.begin();
		     it != mySubjectSentencePart.end(); ++it) {
			if (!(it->myWordDescription).areCoordinatedGrammem(firstSubject, WordDescription::PLURAL) ||
			    !(it->myWordDescription).areCoordinatedGrammem(firstSubject, WordDescription::SINGULAR) ||
			    !(it->myWordDescription).areCoordinatedGrammem(firstSubject, WordDescription::MASCULINUM) ||
			    !(it->myWordDescription).areCoordinatedGrammem(firstSubject, WordDescription::FEMINUM) ||
			    !(it->myWordDescription).areCoordinatedGrammem(firstSubject, WordDescription::NEUTRUM) ||
			    !(it->myWordDescription).areCoordinatedPart(firstSubject, WordDescription::NOUN) ||
			    !(it->myWordDescription).areCoordinatedPart(firstSubject, WordDescription::PRONOUN)) {
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
		for (std::vector<SentencePart>::iterator it = myPredicateSentencePart.begin();
			it != myPredicateSentencePart.end(); ++it) {
			
		}
		// фильтр по роду
		for (std::vector<SentencePart>::iterator it = myPredicateSentencePart.begin();
			it != myPredicateSentencePart.end(); ++it) {
			
		}
	} else
	if (!subjectsInCoordination && predicatesInCoordination) {
		// фильтр по числу
		for (std::vector<SentencePart>::iterator it = mySubjectSentencePart.begin();
			it != mySubjectSentencePart.end(); ++it) {
			
		}

		// фильтр по роду
		for (std::vector<SentencePart>::iterator it = mySubjectSentencePart.begin();
		it != mySubjectSentencePart.end(); ++it) {
			
		}
	} else
	if (!subjectsInCoordination && !predicatesInCoordination) {
		// NP-hard problem :)
	}
}

std::vector<SentencePart> GrammarFrame::getPredicateSentencePart() const {
	return myPredicateSentencePart;
}

std::vector<SentencePart> GrammarFrame::getSubjectSentencePart() const {
	return mySubjectSentencePart;
}

