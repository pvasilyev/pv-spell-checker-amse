#include <vector>

#ifndef _SIMPLE_SENTENCE_H_
#define _SIMPLE_SENTENCE_H_

#include "complexsentence.h"
#include "grammarframe.h"
#include "grammarunits.h"
#include "syntax.h"
#include "vlemmatizer.h"

class ComplexSentence;
class GrammarFrame;
class GrammarUnits;
class SourceSentenceUnit;

class SimpleSentence {

private:
	GrammarFrame *myGrammarFrame;
	GrammarUnits *myGrammarUnits;

	std::vector<std::vector<WordDescription>::iterator> *myObject;
	std::vector<std::vector<WordDescription>::iterator> *myPredicate;

	std::vector<SourceSentenceUnit> *mySSU_SS;

public:
	SimpleSentence(std::vector<SourceSentenceUnit> &ssu);
	~SimpleSentence();

	void parse_ss();

};

#endif
