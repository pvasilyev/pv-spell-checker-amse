#include <iostream>
#include <ostream>
#include <vector>

#include "ComplexSentence.h"
#include "SentenceManager.h"
#include "SimpleSentence.h"
#include "SyntaxAnalyzer.h"
#include "VLemmatizer.h"

ComplexSentence::ComplexSentence(const std::vector<SentenceUnit> &su): mySentenceUnit(su) {
	SimpleSentence tmpSS(mySentenceUnit);
	//tmpSS.parse_ss();
	myVectorSimpleSentence.push_back(tmpSS);
}

void ComplexSentence::print_cs(std::ostream &os) {
	for (std::vector<SimpleSentence>::const_iterator it = myVectorSimpleSentence.begin(); it != myVectorSimpleSentence.end(); ++it) {
		it->print_ss(os);
	}
	
}
/*
void ComplexSentence::parse_cs() {
	for (std::vector<SimpleSentence>::const_iterator it = myVectorSimpleSentence.begin(); it != myVectorSimpleSentence.end(); ++it) {
		it->parse_ss(os);
	}
	
}
*/
