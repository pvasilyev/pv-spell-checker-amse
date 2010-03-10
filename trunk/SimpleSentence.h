#ifndef _SIMPLE_SENTENCE_H_
#define _SIMPLE_SENTENCE_H_

#include <vector>

#include "ComplexSentence.h"
#include "GrammarFrame.h"
#include "GrammarUnits.h"
#include "Syntax.h"
#include "VLemmatizer.h"

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
