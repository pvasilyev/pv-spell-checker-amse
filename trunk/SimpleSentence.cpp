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
}

SimpleSentence::~SimpleSentence() {
}

SimpleSentence::SimpleSentence(const SimpleSentence &ss) {
	mySSU_SS = ss.mySSU_SS;
	myObject = ss.myObject;
	myPredicate = ss.myPredicate;
	myObjectText = ss.myObjectText;
	myPredicateText = ss.myPredicateText;
}

void SimpleSentence::parse_ss() {
	GrammarFrame frame(mySSU_SS);

	frame.buildGrammarFrame();
	myObject = frame.getObject();
	myPredicate = frame.getPredicate();
	myObjectText = frame.getObjectText();
	myPredicateText = frame.getPredicateText();
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
