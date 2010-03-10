#include <vector>

#include "complexsentence.h"
#include "syntax.h"

ComplexSentence::ComplexSentence(const std::vector<SourceSentenceUnit> &ssu) {
	*mySSU_CS = ssu;
}

void ComplexSentence::parse_cs() {

	SimpleSentence *p = new SimpleSentence(*mySSU_CS);

	myVectorSimpleSentence.push_back(*p);
	for (std::vector<SimpleSentence>::iterator it = myVectorSimpleSentence.begin(); it != myVectorSimpleSentence.end(); ++it) {
		it->parse_ss();
	}

	delete p;
}
