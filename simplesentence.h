#include <vector>

#ifndef _SIMPLE_SENTENCE_H_
#define _SIMPLE_SENTENCE_H_

#include "complexsentence.h"
#include "grammarframe.h"
#include "grammarunits.h"
#include "syntax.h"

class ComplexSentence;
class SourceSentenceUnit;

class SimpleSentence {

private:
	GrammarFrame myGrammarFrame;
	GrammarUnits myGrammarUnits;

	std::vector<SourceSentenceUnit> *mySSU_SS;

public:
	SimpleSentence(const std::vector<SourceSentenceUnit> &ssu);

	void parse_ss();

};

#endif
