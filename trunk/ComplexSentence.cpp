#include <vector>

#include "ComplexSentence.h"
#include "SentenceManager.h"
#include "SimpleSentence.h"
#include "Syntax.h"

ComplexSentence::ComplexSentence(std::vector<SourceSentenceUnit> &ssu) {
	mySSU_CS = &ssu;
}


void ComplexSentence::parse_cs() {

	SimpleSentence *p = new SimpleSentence(*mySSU_CS);

	myVectorSimpleSentence.push_back(*p);
	for (std::vector<SimpleSentence>::iterator it = myVectorSimpleSentence.begin(); it != myVectorSimpleSentence.end(); ++it) {
		it->parse_ss();
	}

	delete p;
}
