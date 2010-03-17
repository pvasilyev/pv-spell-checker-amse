#include <iostream>
#include <ostream>
#include <vector>

#include "ComplexSentence.h"
#include "GrammarFrame.h"
#include "GrammarUnits.h"
#include "SimpleSentence.h"
#include "SyntaxAnalyzer.h"
#include "VLemmatizer.h"

SimpleSentence::SimpleSentence(std::vector<SourceSentenceUnit> &ssu) {
	mySSU_SS = ssu;
	GrammarFrame *p = new GrammarFrame(mySSU_SS);
	myGrammarFrame = p;
}

SimpleSentence::~SimpleSentence() {
	delete myGrammarFrame;
}

SimpleSentence::SimpleSentence(const SimpleSentence &ss) {
	mySSU_SS = ss.mySSU_SS;
	GrammarFrame *p = new GrammarFrame(mySSU_SS);
	myGrammarFrame = p;
	myObject = ss.myObject;
	myPredicate = ss.myPredicate;
	myObjectText = ss.myObjectText;
	myPredicateText = ss.myPredicateText;
}

void SimpleSentence::parse_ss() {

	myGrammarFrame->buildGrammarFrame();
	myObject = myGrammarFrame->getObject();
	myPredicate = myGrammarFrame->getPredicate();
	myObjectText = myGrammarFrame->getObjectText();
	myPredicateText = myGrammarFrame->getPredicateText();

}

void SimpleSentence::print_ss(std::ostream &os) {	
	os << "Варианты подлежащего:" << "\n";
	for (std::vector<std::vector<SourceSentenceUnit>::iterator>::iterator it = myObjectText.begin(); it != myObjectText.end(); ++it) {
		os << (*it)->myText << "\n";
	}
	os << "Варианты сказуемого:" << "\n";
	for (std::vector<std::vector<SourceSentenceUnit>::iterator>::iterator it = myPredicateText.begin(); it != myPredicateText.end(); ++it) {
		os << (*it)->myText << "\n";
	}
	os << "\n";

}
