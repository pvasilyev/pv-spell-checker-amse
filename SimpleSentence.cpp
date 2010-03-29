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
	myGrammarFrame = new GrammarFrame(su);
	myGrammarFrame->buildGrammarFrame();
	mySubject = myGrammarFrame->getSubject();
	myPredicate = myGrammarFrame->getPredicate();
	mySubjectText = myGrammarFrame->getSubjectText();
	myPredicateText = myGrammarFrame->getPredicateText();
}

SimpleSentence::~SimpleSentence() {
	delete myGrammarFrame;
}
SimpleSentence::SimpleSentence(const SimpleSentence &ss) : mySentenceUnits(ss.mySentenceUnits) {
	myGrammarFrame = new GrammarFrame(ss.mySentenceUnits);
	mySubject = ss.mySubject;
	myPredicate = ss.myPredicate;
	mySubjectText = ss.mySubjectText;
	myPredicateText = ss.myPredicateText;
}

SimpleSentence& SimpleSentence::operator = (const SimpleSentence &ss) {
	mySentenceUnits= ss.mySentenceUnits;
	mySubject = ss.mySubject;
	myPredicate = ss.myPredicate;
	mySubjectText = ss.mySubjectText;
	myPredicateText = ss.myPredicateText;
	return *this;
}

void SimpleSentence::print_ss(std::ostream &os) const {
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
