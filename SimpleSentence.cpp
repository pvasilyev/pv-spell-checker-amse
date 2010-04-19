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
	mySubjectSentencePart = frame.getSubjectSentencePart();
	myPredicateSentencePart = frame.getPredicateSentencePart();
}


void SimpleSentence::print(std::ostream &os) const {
	os << "Варианты подлежащего:" << "\n";
	for (std::vector<SentencePart>::const_iterator it = mySubjectSentencePart.begin(); it != mySubjectSentencePart.end(); ++it) {
		os << (it->mySentenceUnit).myText << "\n";
	}
	os << "Варианты сказуемого:" << "\n";
	for (std::vector<SentencePart>::const_iterator it = myPredicateSentencePart.begin(); it != myPredicateSentencePart.end(); ++it) {
		os << (it->mySentenceUnit).myText << "\n";
	}
	os << "\n";

}
