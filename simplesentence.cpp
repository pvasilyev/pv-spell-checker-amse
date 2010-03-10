#include <vector>

#include "simplesentence.h"

SimpleSentence::SimpleSentence(std::vector<SourceSentenceUnit> &ssu) {
	mySSU_SS = &ssu;
	GrammarFrame *p = new GrammarFrame(*mySSU_SS);
	myGrammarFrame = p;
}

SimpleSentence::~SimpleSentence() {
	delete myGrammarFrame;
}

void SimpleSentence::parse_ss() {

	//GrammarFrame *p = new GrammarFrame(*mySSU_SS);
	//myGrammarFrame = p;

	//delete p;

}


