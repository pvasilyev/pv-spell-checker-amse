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
			// существительное + именительный падеж -- кандидат на подлежащее
			if ((*jt).myPartOfSpeech == WordDescription::NOUN &&
			((*jt).myGrammem & (u_int64_t)WordDescription::NOMINATIV)) {
				bool b = true;
				if (it != mySentenceUnits.begin()) {
					--it;
					for (std::vector<WordDescription>::const_iterator kt = (it->myVectorWordDescription).begin();
					kt != (it->myVectorWordDescription).end(); ++kt) {
						if ((*kt).myPartOfSpeech == WordDescription::PREPOSAL ||
						((*kt).myPartOfSpeech == WordDescription::ADJECTIVE_FULL &&
						((*kt).myGrammem & !(u_int64_t)WordDescription::NOMINATIV))) {
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

			// местоимение + именительный падеж -- кандидат на подлежащее
			if ((*jt).myPartOfSpeech == WordDescription::PRONOUN &&
			((*jt).myGrammem & (u_int64_t)WordDescription::NOMINATIV)) {
				bool b = true;
				if (it != mySentenceUnits.begin()) {
					--it;
					for (std::vector<WordDescription>::const_iterator kt = (it->myVectorWordDescription).begin();
					kt != (it->myVectorWordDescription).end(); ++kt) {
						if ((*kt).myPartOfSpeech == WordDescription::PREPOSAL ||
						((*kt).myPartOfSpeech == WordDescription::ADJECTIVE_FULL &&
						((*kt).myGrammem & !(u_int64_t)WordDescription::NOMINATIV))) {
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

			// глагол -- кандидат на сказуемое 
			if ((*jt).myPartOfSpeech == WordDescription::VERB) {
				myPredicate.push_back(*jt);
				myPredicateText.push_back(*it);
			}
		}
	}
	// проверка согласованности сказуемых
	PredicateCoordinationCount pcc;

	for (std::vector<WordDescription>::const_iterator it = myPredicate.begin();
	it != myPredicate.end(); ++it) {
		if (it->myGrammem & (u_int64_t)WordDescription::PLURAL) {
			++pcc.myPlural;
		}
		if (it->myGrammem & (u_int64_t)WordDescription::SINGULAR) {
			++pcc.mySingular;
		}
		if (it->myGrammem & (u_int64_t)WordDescription::MASCULINUM) {
			++pcc.myMasculinum;
		}
		if (it->myGrammem & (u_int64_t)WordDescription::FEMINUM) {
			++pcc.myFeminum;
		}
		if (it->myGrammem & (u_int64_t)WordDescription::NEUTRUM) {
			++pcc.myNeutrum;
		}
		if (it->myGrammem & (u_int64_t)WordDescription::PASTTENSE) {
			++pcc.myPast;
		}
		if (it->myGrammem & (u_int64_t)WordDescription::PRESENTTENSE) {
			++pcc.myPresent;
		}
		if (it->myGrammem & (u_int64_t)WordDescription::FUTURETENSE) {
			++pcc.myFuture;
		}
	}
	myPredicatesInCoordination = ((pcc.myPlural == 0 || pcc.myPlural == (int)myPredicate.size()) &&
				(pcc.mySingular == 0 || pcc.mySingular == (int)myPredicate.size()) &&
				(pcc.myMasculinum == 0 || pcc.myMasculinum == (int)myPredicate.size()) &&
				(pcc.myFeminum == 0 || pcc.myFeminum == (int)myPredicate.size()) &&
				(pcc.myNeutrum == 0 || pcc.myNeutrum == (int)myPredicate.size()) &&
				(pcc.myPast == 0 || pcc.myPast == (int)myPredicate.size()) &&
				(pcc.myPresent == 0 || pcc.myPresent == (int)myPredicate.size()) &&
				(pcc.myFuture == 0 || pcc.myFuture == (int)myPredicate.size()));

	// проверка согласованности подлежащих
	SubjectCoordinationCount scc;

	for (std::vector<WordDescription>::const_iterator it = mySubject.begin();
	it != mySubject.end(); ++it) {
		if (it->myGrammem & (u_int64_t)WordDescription::PLURAL) {
			++scc.myPlural;
		}
		if (it->myGrammem & (u_int64_t)WordDescription::SINGULAR) {
			++scc.mySingular;
		}
		if (it->myGrammem & (u_int64_t)WordDescription::MASCULINUM) {
			++scc.myMasculinum;
		}
		if (it->myGrammem & (u_int64_t)WordDescription::FEMINUM) {
			++scc.myFeminum;
		}
		if (it->myGrammem & (u_int64_t)WordDescription::NEUTRUM) {
			++scc.myNeutrum;
		}
		if (it->myGrammem & (u_int64_t)WordDescription::NOUN) {
			++scc.myNoun;
		}
		if (it->myGrammem & (u_int64_t)WordDescription::PRONOUN) {
			++scc.myPronoun;
		}
	}
	mySubjectsInCoordination = ((scc.myPlural == 0 || scc.myPlural == (int)mySubject.size()) &&
				(scc.mySingular == 0 || scc.mySingular == (int)mySubject.size()) &&
				(scc.myMasculinum == 0 || scc.myMasculinum == (int)mySubject.size()) &&
				(scc.myFeminum == 0 || scc.myFeminum == (int)mySubject.size()) &&
				(scc.myNeutrum == 0 || scc.myNeutrum == (int)mySubject.size()) &&
				(scc.myNoun == 0 || scc.myNoun == (int)mySubject.size()) &&
				(scc.myPronoun == 0 || scc.myPronoun == (int)mySubject.size()));

	if (mySubjectsInCoordination && !myPredicatesInCoordination) {
		// фильтр по числу
		bool plural = (scc.mySingular == 0);
		for (std::vector<WordDescription>::iterator it = myPredicate.begin();
		it != myPredicate.end(); ++it) {
			
		}
		// фильтр по роду
		int gender;
		if (scc.myMasculinum != 0) {
			gender = 0;
		} else
		if (scc.myFeminum != 0) {
			gender = 1;
		} else
		if (scc.myNeutrum != 0) {
			gender = 2;
		}
		for (std::vector<WordDescription>::iterator it = myPredicate.begin();
		it != myPredicate.end(); ++it) {
			
		}
	} else
	if (!mySubjectsInCoordination && myPredicatesInCoordination) {
		// фильтр по числу
		for (std::vector<WordDescription>::iterator it = mySubject.begin();
		it != myPredicate.end(); ++it) {
			
		}

		// фильтр по роду
		for (std::vector<WordDescription>::iterator it = mySubject.begin();
		it != myPredicate.end(); ++it) {
			
		}
	} else
	if (!mySubjectsInCoordination && !myPredicatesInCoordination) {
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

PredicateCoordinationCount::PredicateCoordinationCount() {
	myPlural = 0;
	mySingular = 0;
	myMasculinum = 0;
	myFeminum = 0;
	myNeutrum = 0;
	myPast = 0;
	myPresent = 0;
	myFuture = 0; 
}

SubjectCoordinationCount::SubjectCoordinationCount() {
	myPlural = 0;
	mySingular = 0;
	myMasculinum = 0;
	myFeminum = 0;
	myNeutrum = 0;
	myNoun = 0;
	myPronoun = 0;
}

