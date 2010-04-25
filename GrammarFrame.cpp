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
			tryToAddSubject(it, *jt);

			// глагол -- кандидат на сказуемое 
			if ((jt)->hasPart(WordDescription::VERB)) {
				SentencePart sp;
				sp.myWordDescription = (*jt);
				sp.mySentenceUnit = *it;
				myPredicateSentencePart.push_back(sp);
			}
		}
	}

	bool predicatesInCoordination = checkPredicateCoordination();
	bool subjectsInCoordination = checkSubjectCoordination();
	doFiltration(subjectsInCoordination, predicatesInCoordination);
}

//итераторы не для передачи по параметру
void GrammarFrame::tryToAddSubject(std::vector<SentenceUnit>::const_iterator it,
				const WordDescription &description) {
	// существительное или местоимение + именительный падеж -- кандидат на подлежащее
	if ((description.hasPart(WordDescription::NOUN) || description.hasPart(WordDescription::PRONOUN)) &&
		(description.hasGrammem(WordDescription::NOMINATIV))) {
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
			sp.myWordDescription = (description);
			sp.mySentenceUnit = *it;
			mySubjectSentencePart.push_back(sp);
		}
	}
}

bool GrammarFrame::checkPredicateCoordination() const {
// PLURAL etc -- положить в контейнер + сделать метод статическим!
	if (!myPredicateSentencePart.empty()) {
		const WordDescription &firstPredicate = (myPredicateSentencePart.at(0)).myWordDescription;
		std::vector<WordDescription::Grammem> vectorGrammems;
		vectorGrammems.push_back(WordDescription::PLURAL);
		vectorGrammems.push_back(WordDescription::SINGULAR);
		vectorGrammems.push_back(WordDescription::MASCULINUM);
		vectorGrammems.push_back(WordDescription::FEMINUM);
		vectorGrammems.push_back(WordDescription::NEUTRUM);
		vectorGrammems.push_back(WordDescription::PASTTENSE);
		vectorGrammems.push_back(WordDescription::PRESENTTENSE);
		vectorGrammems.push_back(WordDescription::FUTURETENSE);
		for (std::vector<SentencePart>::const_iterator it = myPredicateSentencePart.begin();
		     it != myPredicateSentencePart.end(); ++it) {
			for (std::vector<WordDescription::Grammem>::const_iterator jt = vectorGrammems.begin();
				jt != vectorGrammems.end(); ++jt) {
				if (!(it->myWordDescription).areCoordinatedGrammem(firstPredicate, *jt)) {
					return false;
				}
			}
		}
	}
	return true;
}
 
bool GrammarFrame::checkSubjectCoordination() const {
	if (!mySubjectSentencePart.empty()) {
		const WordDescription &firstSubject = (mySubjectSentencePart.at(0)).myWordDescription;
		std::vector<WordDescription::Grammem> vectorGrammems;
		vectorGrammems.push_back(WordDescription::PLURAL);
		vectorGrammems.push_back(WordDescription::SINGULAR);
		vectorGrammems.push_back(WordDescription::MASCULINUM);
		vectorGrammems.push_back(WordDescription::FEMINUM);
		vectorGrammems.push_back(WordDescription::NEUTRUM);
		std::vector<WordDescription::PartOfSpeech> vectorPartsOfSpeech;
		vectorPartsOfSpeech.push_back(WordDescription::NOUN);
		vectorPartsOfSpeech.push_back(WordDescription::PRONOUN);
		for (std::vector<SentencePart>::const_iterator it = mySubjectSentencePart.begin();
		     it != mySubjectSentencePart.end(); ++it) {
			for (std::vector<WordDescription::Grammem>::const_iterator jt = vectorGrammems.begin();
				jt != vectorGrammems.end(); ++jt) {
				if (!(it->myWordDescription).areCoordinatedGrammem(firstSubject, *jt)) {
					return false;
				}
			}
			for (std::vector<WordDescription::PartOfSpeech>::const_iterator jt = vectorPartsOfSpeech.begin();
				jt != vectorPartsOfSpeech.end(); ++jt) {
				if (!(it->myWordDescription).areCoordinatedPart(firstSubject, *jt)) {
					return false;
				}
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

