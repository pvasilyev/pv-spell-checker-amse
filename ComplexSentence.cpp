#include <iostream>
#include <ostream>
#include <vector>

#include "ComplexSentence.h"
#include "SentenceManager.h"
#include "SimpleSentence.h"
#include "SyntaxAnalyzer.h"
#include "VLemmatizer.h"

ComplexSentence::ComplexSentence(const std::vector<SentenceUnit> &su): mySentenceUnits(su) {
	SimpleSentence tmpSS(mySentenceUnits);
	myVectorSimpleSentence.push_back(tmpSS);
}

void ComplexSentence::print(std::ostream &os) const {
	for (std::vector<SimpleSentence>::const_iterator it = myVectorSimpleSentence.begin(); it != myVectorSimpleSentence.end(); ++it) {
		it->print(os);
	}
	
}
