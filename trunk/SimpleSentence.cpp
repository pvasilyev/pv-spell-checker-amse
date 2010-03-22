#include <iostream>
#include <ostream>
#include <vector>

#include "ComplexSentence.h"
#include "GrammarFrame.h"
#include "GrammarUnits.h"
#include "SimpleSentence.h"
#include "SyntaxAnalyzer.h"
#include "VLemmatizer.h"

SimpleSentence::SimpleSentence(const std::vector<SourceSentenceUnit> &ssu): mySourceSentenceUnit_SimpleSentence(ssu) {
	myGrammarFrame = new GrammarFrame(ssu);
}

SimpleSentence::~SimpleSentence() {
	delete myGrammarFrame;
}

SimpleSentence::SimpleSentence(const SimpleSentence &ss) : mySourceSentenceUnit_SimpleSentence(ss.mySourceSentenceUnit_SimpleSentence) {
	myGrammarFrame = new GrammarFrame(ss.mySourceSentenceUnit_SimpleSentence);
	myObject = ss.myObject;
	myPredicate = ss.myPredicate;
	myObjectText = ss.myObjectText;
	myPredicateText = ss.myPredicateText;
}

SimpleSentence& SimpleSentence::operator = (const SimpleSentence &ss) {
	mySourceSentenceUnit_SimpleSentence = ss.mySourceSentenceUnit_SimpleSentence;
	myObject = ss.myObject;
	myPredicate = ss.myPredicate;
	myObjectText = ss.myObjectText;
	myPredicateText = ss.myPredicateText;
	return *this;
}

void SimpleSentence::parse_ss() {
/*
	GrammarFrame frame(mySourceSentenceUnit_SimpleSentence);
	frame.buildGrammarFrame();
	myObject = frame.getObject();
	myPredicate = frame.getPredicate();
	myObjectText = frame.getObjectText();
	myPredicateText = frame.getPredicateText();
*/
	myGrammarFrame->buildGrammarFrame();
	myObject = myGrammarFrame->getObject();
	myPredicate = myGrammarFrame->getPredicate();
	myObjectText = myGrammarFrame->getObjectText();
	myPredicateText = myGrammarFrame->getPredicateText();
	
}

void SimpleSentence::print_ss(std::ostream &os) const {
	os << "Варианты подлежащего:" << "\n";
	for (std::vector<std::vector<SourceSentenceUnit>::const_iterator>::const_iterator it = myObjectText.begin(); it != myObjectText.end(); ++it) {
		os << (*it)->myText << "\n";
	}
	os << "Варианты сказуемого:" << "\n";
	for (std::vector<std::vector<SourceSentenceUnit>::const_iterator>::const_iterator it = myPredicateText.begin(); it != myPredicateText.end(); ++it) {
		os << (*it)->myText << "\n";
	}
	os << "\n";

}
