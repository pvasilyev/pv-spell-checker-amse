#include <vector>

#include "simplesentence.h"
#include "syntax.h"

SimpleSentence::SimpleSentence(const std::vector<SourceSentenceUnit> &ssu) {
	*mySSU_SS = ssu;
}

void SimpleSentence::parse_ss() {

	for (std::vector<SourceSentenceUnit>::iterator it = (*mySSU_SS).begin(); it != (*mySSU_SS).end(); ++it ) {
		for (std::vector<WordDescription>::iterator jt = (it->myWD).begin(); jt != (it->myWD).end(); ++jt) {
			// существительное + именительный падеж -- кандидат на подлежащее
			if ((*jt).myPartOfSpeech == 0 && ((*jt).myGrammem & ((u_int64_t)1 << 2))) {
				//myObject.push_back(mySentenceUnit[it - myWordDescription.begin()]);
			}

			// местоимение + именительный падеж -- кандидат на подлежащее
			if ((*jt).myPartOfSpeech == 3 && ((*jt).myGrammem & ((u_int64_t)1 << 2))) {
				//myObject.push_back(mySentenceUnit[it - myWordDescription.begin()]);
			}

			// глагол -- кандидат на сказуемое 
			if ((*jt).myPartOfSpeech == 2) {
				//myPredicate.push_back(mySentenceUnit[it - myWordDescription.begin()]);
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
