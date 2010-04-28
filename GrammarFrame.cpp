#include <iostream>
#include <stdio.h>

#include "GrammarFrame.h"
#include "SyntaxAnalyzer.h"
#include "Rules.h"
#include "VLemmatizer.h"

GrammarFrame::GrammarFrame(const std::vector<SentenceUnit> &su): mySentenceUnits(su) {

	for (std::vector<SentenceUnit>::const_iterator it = mySentenceUnits.begin();
		it != mySentenceUnits.end(); ++it ) {
		for (std::vector<WordDescription>::const_iterator jt = it->myVectorWordDescription.begin();
			jt != it->myVectorWordDescription.end(); ++jt) {
			tryToAddSubject(*it, *(it - 1), *jt, it == mySentenceUnits.begin());

			// глагол -- кандидат на сказуемое  
			if ((jt)->hasPart(WordDescription::VERB)) {
				SentencePart sp;
				sp.myWordDescription = *jt;
				sp.mySentenceUnit = *it;
				myPredicate.push_back(sp);
			}
		}
	}

	SubjectCoordinationRule scr;
	PredicateCoordinationRule pcr;
	bool predicatesInCoordination = pcr.accepts(myPredicate);
	bool subjectsInCoordination = scr.accepts(mySubject);
	doFiltration(subjectsInCoordination, predicatesInCoordination);
}

void GrammarFrame::tryToAddSubject(const SentenceUnit &current, const SentenceUnit &previous,
				const WordDescription &description, const bool &isFirstSentenceUnit) {
	// существительное или местоимение + именительный падеж -- кандидат на подлежащее
	if ((description.hasPart(WordDescription::NOUN) || description.hasPart(WordDescription::PRONOUN)) &&
		description.hasGrammem(WordDescription::NOMINATIV)) {
		bool b = true;
		if (!isFirstSentenceUnit) {
			for (std::vector<WordDescription>::const_iterator
				kt = previous.myVectorWordDescription.begin();
				kt != previous.myVectorWordDescription.end(); ++kt) {
				if (kt->hasPart(WordDescription::PREPOSAL) ||
					(kt->hasPart(WordDescription::ADJECTIVE_FULL) &&
					(!kt->hasGrammem(WordDescription::NOMINATIV)))) {
					b = false;
				}
			}
		}
		if (b) {
			SentencePart sp;
			sp.myWordDescription = description;
			sp.mySentenceUnit = current;
			mySubject.push_back(sp);
		}
	}
}

void GrammarFrame::doFiltration(bool subjectsInCoordination, bool predicatesInCoordination) {
	if (subjectsInCoordination && !predicatesInCoordination) {
		// фильтр по числу
		for (std::vector<SentencePart>::iterator it = myPredicate.begin();
			it != myPredicate.end(); ++it) {
			
		}
		// фильтр по роду
		for (std::vector<SentencePart>::iterator it = myPredicate.begin();
			it != myPredicate.end(); ++it) {
			
		}
	} else
	if (!subjectsInCoordination && predicatesInCoordination) {
		// фильтр по числу
		for (std::vector<SentencePart>::iterator it = mySubject.begin();
			it != mySubject.end(); ++it) {
			
		}

		// фильтр по роду
		for (std::vector<SentencePart>::iterator it = mySubject.begin();
		it != mySubject.end(); ++it) {
			
		}
	} else
	if (!subjectsInCoordination && !predicatesInCoordination) {
		// NP-hard problem :)
	}
}

std::vector<SentencePart> GrammarFrame::getPredicate() const {
	return myPredicate;
}

std::vector<SentencePart> GrammarFrame::getSubject() const {
	return mySubject;
}


