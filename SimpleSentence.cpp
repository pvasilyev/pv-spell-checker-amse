#include <iostream>
#include <ostream>
#include <vector>

#include "ComplexSentence.h"
#include "GrammarFrame.h"
#include "GrammarUnits.h"
#include "SimpleSentence.h"
#include "SyntaxAnalyzer.h"
#include "VLemmatizer.h"

SimpleSentence::SimpleSentence(const std::vector<SentenceUnit> &su): mySentenceUnits(su) {
	GrammarFrame frame(su);
	mySubject = frame.getSubject();
	myPredicate = frame.getPredicate();
}


void SimpleSentence::print(std::ostream &os) const {
	os << "Варианты подлежащего:" << "\n";
	for (std::vector<SentencePart>::const_iterator it = mySubject.begin(); it != mySubject.end(); ++it) {
		os << (it->mySentenceUnit).myText << "\n";
	}
	os << "Варианты сказуемого:" << "\n";
	for (std::vector<SentencePart>::const_iterator it = myPredicate.begin(); it != myPredicate.end(); ++it) {
		os << (it->mySentenceUnit).myText << "\n";
	}
	os << "\n";

}
