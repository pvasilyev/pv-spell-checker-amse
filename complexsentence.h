#include <vector>

#ifndef _COMPLEX_SENTENCE_H_
#define _COMPLEX_SENTENCE_H_

#include "simplesentence.h"
#include "sentencemanager.h"
#include "syntax.h"

class SourceSentenceUnit;
class SimpleSentence;

class ComplexSentence {

private:
	std::vector<SimpleSentence> myVectorSimpleSentence;
	SentenceManager *mySentenceManager;

	std::vector<SourceSentenceUnit> *mySSU_CS;

public:
	ComplexSentence(std::vector<SourceSentenceUnit> &ssu);

	void parse_cs();

};

#endif
