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
	mySubjectText = frame.getSubjectText();
	myPredicateText = frame.getPredicateText();
}


void SimpleSentence::print(std::ostream &os) const {
	os << "Варианты подлежащего:" << "\n";
	for (std::vector<SentenceUnit>::const_iterator it = mySubjectText.begin(); it != mySubjectText.end(); ++it) {
		os << it->myText << "\n";
	}
	os << "Варианты сказуемого:" << "\n";
	for (std::vector<SentenceUnit>::const_iterator it = myPredicateText.begin(); it != myPredicateText.end(); ++it) {
		os << it->myText << "\n";
	}
	os << "\n";

}
