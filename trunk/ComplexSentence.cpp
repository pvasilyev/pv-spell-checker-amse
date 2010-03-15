#include <ostream>
#include <vector>

#include "ComplexSentence.h"
#include "SentenceManager.h"
#include "SimpleSentence.h"
#include "SyntaxAnalyzer.h"

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

void ComplexSentence::print_cs(std::ostream &os) {
	for (std::vector<SimpleSentence>::iterator it = myVectorSimpleSentence.begin(); it != myVectorSimpleSentence.end(); ++it) {
		it->print_ss(os);
	}
	
}
