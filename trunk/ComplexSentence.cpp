#include <iostream>
#include <ostream>
#include <vector>

#include "ComplexSentence.h"
#include "SentenceManager.h"
#include "SimpleSentence.h"
#include "SyntaxAnalyzer.h"
#include "VLemmatizer.h"

ComplexSentence::ComplexSentence(const std::vector<SourceSentenceUnit> &ssu): mySourceSentenceUnit_ComplexSentence(ssu) {}

void ComplexSentence::parse_cs() {

	SimpleSentence tmpSS(mySourceSentenceUnit_ComplexSentence);
	tmpSS.parse_ss();
	myVectorSimpleSentence.push_back(tmpSS);
}

void ComplexSentence::print_cs(std::ostream &os) {
	for (std::vector<SimpleSentence>::const_iterator it = myVectorSimpleSentence.begin(); it != myVectorSimpleSentence.end(); ++it) {
		it->print_ss(os);
	}
	
}
