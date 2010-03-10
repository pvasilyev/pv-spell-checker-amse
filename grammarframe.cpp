#include "grammarframe.h"

GrammarFrame::GrammarFrame(std::vector<SourceSentenceUnit> &ssu) {
	mySSU_GF = &ssu;
}

void GrammarFrame::buildGrammarFrame() {

	for (std::vector<SourceSentenceUnit>::iterator it = (*mySSU_GF).begin(); it != (*mySSU_GF).end(); ++it ) {
		for (std::vector<WordDescription>::iterator jt = (it->myWD).begin(); jt != (it->myWD).end(); ++jt) {
			// существительное + именительный падеж -- кандидат на подлежащее
			if ((*jt).myPartOfSpeech == 0 && ((*jt).myGrammem & ((u_int64_t)1 << 2))) {
				myObject->push_back(jt);
			}

			// местоимение + именительный падеж -- кандидат на подлежащее
			if ((*jt).myPartOfSpeech == 3 && ((*jt).myGrammem & ((u_int64_t)1 << 2))) {
				myObject->push_back(jt);
			}

			// глагол -- кандидат на сказуемое 
			if ((*jt).myPartOfSpeech == 2) {
				myPredicate->push_back(jt);
			}
		}
	}
/*
// a priori выкинуть неподходящее сказуемое
	VLemmatizer lem_temp;
	std::vector<std::vector<WordDescription> > predicate;
	for (std::vector<std::string>::iterator it = myPredicate.begin(); it != myPredicate.end(); ++it) {
		std::vector<WordDescription> temp = lem_temp.lemmatize(*it);
		predicate.push_back(temp);
	}
*/
}

std::vector<std::vector<WordDescription>::iterator> *GrammarFrame::getGrammarFrame() {
	return myGrammarFrame;
}
