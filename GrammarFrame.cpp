#include <iostream>
#include <stdio.h>

#include "GrammarFrame.h"
#include "SyntaxAnalyzer.h"
#include "VLemmatizer.h"

GrammarFrame::GrammarFrame(const std::vector<SentenceUnit> &su): mySentenceUnits(su) {

	for (std::vector<SentenceUnit>::const_iterator it = mySentenceUnits.begin();
		it != mySentenceUnits.end(); ++it ) {
		for (std::vector<WordDescription>::const_iterator jt = it->myVectorWordDescription.begin();
			jt != it->myVectorWordDescription.end(); ++jt) {
			tryToAddSubject(it, *jt);

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

//итераторы не для передачи по параметру
void GrammarFrame::tryToAddSubject(std::vector<SentenceUnit>::const_iterator it,
				const WordDescription &description) {
	// существительное или местоимение + именительный падеж -- кандидат на подлежащее
	if ((description.hasPart(WordDescription::NOUN) || description.hasPart(WordDescription::PRONOUN)) &&
		description.hasGrammem(WordDescription::NOMINATIV)) {
		bool b = true;
		if (it != mySentenceUnits.begin()) {
			const std::vector<SentenceUnit>::const_iterator previous = it - 1;
			for (std::vector<WordDescription>::const_iterator
				kt = previous->myVectorWordDescription.begin();
				kt != previous->myVectorWordDescription.end(); ++kt) {
				if (kt->hasPart(WordDescription::PREPOSAL) ||
					(kt->hasPart(WordDescription::ADJECTIVE_FULL) &&
					(!kt->hasGrammem(WordDescription::NOMINATIV)))) {
					b = false;
				}
			}
		}
		if (b) {
			SentencePart sp;
			sp.myWordDescription = (description);
			sp.mySentenceUnit = *it;
			mySubject.push_back(sp);
		}
	}
}

bool GrammarFrame::checkPredicateCoordination() const {
	if (!myPredicate.empty()) {
		const WordDescription &firstPredicate = myPredicate.at(0).myWordDescription;

		std::vector<WordDescription::Grammem> vectorGrammems;
		vectorGrammems.push_back(WordDescription::PLURAL);
		vectorGrammems.push_back(WordDescription::SINGULAR);
		vectorGrammems.push_back(WordDescription::MASCULINUM);
		vectorGrammems.push_back(WordDescription::FEMINUM);
		vectorGrammems.push_back(WordDescription::NEUTRUM);
		vectorGrammems.push_back(WordDescription::PASTTENSE);
		vectorGrammems.push_back(WordDescription::PRESENTTENSE);
		vectorGrammems.push_back(WordDescription::FUTURETENSE);

		for (std::vector<SentencePart>::const_iterator it = myPredicate.begin();
		     it != myPredicate.end(); ++it) {
			for (std::vector<WordDescription::Grammem>::const_iterator jt = vectorGrammems.begin();
				jt != vectorGrammems.end(); ++jt) {
				if (!it->myWordDescription.areCoordinatedGrammem(firstPredicate, *jt)) {
					return false;
				}
			}
		}
	}
	return true;
}
 
bool GrammarFrame::checkSubjectCoordination() const {
	if (!mySubject.empty()) {
		const WordDescription &firstSubject = mySubject.at(0).myWordDescription;

		std::vector<WordDescription::Grammem> vectorGrammems;
		vectorGrammems.push_back(WordDescription::PLURAL);
		vectorGrammems.push_back(WordDescription::SINGULAR);
		vectorGrammems.push_back(WordDescription::MASCULINUM);
		vectorGrammems.push_back(WordDescription::FEMINUM);
		vectorGrammems.push_back(WordDescription::NEUTRUM);

		std::vector<WordDescription::PartOfSpeech> vectorPartsOfSpeech;
		vectorPartsOfSpeech.push_back(WordDescription::NOUN);
		vectorPartsOfSpeech.push_back(WordDescription::PRONOUN);

		for (std::vector<SentencePart>::const_iterator it = mySubject.begin();
		     it != mySubject.end(); ++it) {
			for (std::vector<WordDescription::Grammem>::const_iterator jt = vectorGrammems.begin();
				jt != vectorGrammems.end(); ++jt) {
				if (!it->myWordDescription.areCoordinatedGrammem(firstSubject, *jt)) {
					return false;
				}
			}
			for (std::vector<WordDescription::PartOfSpeech>::const_iterator jt = vectorPartsOfSpeech.begin();
				jt != vectorPartsOfSpeech.end(); ++jt) {
				if (!it->myWordDescription.areCoordinatedPart(firstSubject, *jt)) {
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

bool SubjectCoordinationRule::accepts(const std::vector<SentencePart> &subjects) const {
	if (!subjects.empty()) {
		const WordDescription &firstSubject = subjects.at(0).myWordDescription;

		std::vector<WordDescription::Grammem> vectorGrammems;
		vectorGrammems.push_back(WordDescription::PLURAL);
		vectorGrammems.push_back(WordDescription::SINGULAR);
		vectorGrammems.push_back(WordDescription::MASCULINUM);
		vectorGrammems.push_back(WordDescription::FEMINUM);
		vectorGrammems.push_back(WordDescription::NEUTRUM);

		std::vector<WordDescription::PartOfSpeech> vectorPartsOfSpeech;
		vectorPartsOfSpeech.push_back(WordDescription::NOUN);
		vectorPartsOfSpeech.push_back(WordDescription::PRONOUN);

		for (std::vector<SentencePart>::const_iterator it = subjects.begin();
		     it != subjects.end(); ++it) {
			for (std::vector<WordDescription::Grammem>::const_iterator jt = vectorGrammems.begin();
				jt != vectorGrammems.end(); ++jt) {
				if (!it->myWordDescription.areCoordinatedGrammem(firstSubject, *jt)) {
					return false;
				}
			}
			for (std::vector<WordDescription::PartOfSpeech>::const_iterator jt = vectorPartsOfSpeech.begin();
				jt != vectorPartsOfSpeech.end(); ++jt) {
				if (!it->myWordDescription.areCoordinatedPart(firstSubject, *jt)) {
					return false;
				}
			}
		}
	}
	return true;
}

bool PredicateCoordinationRule::accepts(const std::vector<SentencePart> &predicates) const {
	if (!predicates.empty()) {
		const WordDescription &firstPredicate = predicates.at(0).myWordDescription;

		std::vector<WordDescription::Grammem> vectorGrammems;
		vectorGrammems.push_back(WordDescription::PLURAL);
		vectorGrammems.push_back(WordDescription::SINGULAR);
		vectorGrammems.push_back(WordDescription::MASCULINUM);
		vectorGrammems.push_back(WordDescription::FEMINUM);
		vectorGrammems.push_back(WordDescription::NEUTRUM);
		vectorGrammems.push_back(WordDescription::PASTTENSE);
		vectorGrammems.push_back(WordDescription::PRESENTTENSE);
		vectorGrammems.push_back(WordDescription::FUTURETENSE);

		for (std::vector<SentencePart>::const_iterator it = predicates.begin();
		     it != predicates.end(); ++it) {
			for (std::vector<WordDescription::Grammem>::const_iterator jt = vectorGrammems.begin();
				jt != vectorGrammems.end(); ++jt) {
				if (!it->myWordDescription.areCoordinatedGrammem(firstPredicate, *jt)) {
					return false;
				}
			}
		}
	}
	return true;
}

