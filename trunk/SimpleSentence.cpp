#include <iostream>
#include <ostream>
#include <vector>

#include "ComplexSentence.h"
#include "GrammarFrame.h"
#include "GrammarUnits.h"
#include "SimpleSentence.h"
#include "SyntaxAnalyzer.h"
#include "VLemmatizer.h"

SimpleSentence::SimpleSentence(const std::vector<SentenceUnit> &su): mySentenceUnit(su) {
	myGrammarFrame = new GrammarFrame(su);
	myGrammarFrame->buildGrammarFrame();
	myObject = myGrammarFrame->getObject();
	myPredicate = myGrammarFrame->getPredicate();
	myObjectText = myGrammarFrame->getObjectText();
	myPredicateText = myGrammarFrame->getPredicateText();
}

SimpleSentence::~SimpleSentence() {
	delete myGrammarFrame;
}
SimpleSentence::SimpleSentence(const SimpleSentence &ss) : mySentenceUnit(ss.mySentenceUnit) {
	myGrammarFrame = new GrammarFrame(ss.mySentenceUnit);
	myObject = ss.myObject;
	myPredicate = ss.myPredicate;
	myObjectText = ss.myObjectText;
	myPredicateText = ss.myPredicateText;
}

SimpleSentence& SimpleSentence::operator = (const SimpleSentence &ss) {
	mySentenceUnit= ss.mySentenceUnit;
	myObject = ss.myObject;
	myPredicate = ss.myPredicate;
	myObjectText = ss.myObjectText;
	myPredicateText = ss.myPredicateText;
	return *this;
}
//void SimpleSentence::parse_ss() {
/*
	GrammarFrame frame(mySentenceUnit_SimpleSentence);
	frame.buildGrammarFrame();
	myObject = frame.getObject();
	myPredicate = frame.getPredicate();
	myObjectText = frame.getObjectText();
	myPredicateText = frame.getPredicateText();
*/
/*
	myGrammarFrame->buildGrammarFrame();
	myObject = myGrammarFrame->getObject();
	myPredicate = myGrammarFrame->getPredicate();
	myObjectText = myGrammarFrame->getObjectText();
	myPredicateText = myGrammarFrame->getPredicateText();
*/	
//}

void SimpleSentence::print_ss(std::ostream &os) const {
	os << "Варианты подлежащего:" << "\n";
	for (std::vector<SentenceUnit>::const_iterator it = myObjectText.begin(); it != myObjectText.end(); ++it) {
		os << it->myText << "\n";
	}
	os << "Варианты сказуемого:" << "\n";
	for (std::vector<SentenceUnit>::const_iterator it = myPredicateText.begin(); it != myPredicateText.end(); ++it) {
		os << it->myText << "\n";
	}
	os << "\n";

}
