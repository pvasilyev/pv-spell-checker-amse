#include <vector>

#ifndef _GRAMMAR_FRAME_H_
#define _GRAMMAR_FRAME_H_

#include "syntax.h"
#include "vlemmatizer.h"

class SourceSentenceUnit;

class GrammarFrame {

private:
	std::vector<std::vector<WordDescription>::iterator> *myGrammarFrame;

	std::vector<SourceSentenceUnit> *mySSU_GF;

	std::vector<std::vector<WordDescription>::iterator> *myObject;
	std::vector<std::vector<WordDescription>::iterator> *myPredicate;

public:
	GrammarFrame(std::vector<SourceSentenceUnit> &ssu);

	void buildGrammarFrame();

	std::vector<std::vector<WordDescription>::iterator> *getGrammarFrame();

};

#endif
