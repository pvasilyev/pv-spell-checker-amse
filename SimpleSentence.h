#ifndef _SIMPLE_SENTENCE_H_
#define _SIMPLE_SENTENCE_H_

#include <vector>

class ComplexSentence;
class GrammarFrame;
class GrammarUnits;
class SentenceManager;
class SourceSentenceUnit;
class WordDescription;

class SimpleSentence {

public:
	SimpleSentence(std::vector<SourceSentenceUnit> &ssu);
	~SimpleSentence();

	void parse_ss();

private:
	GrammarFrame *myGrammarFrame;
	GrammarUnits *myGrammarUnits;

	std::vector<std::vector<WordDescription>::iterator> *myObject;
	std::vector<std::vector<WordDescription>::iterator> *myPredicate;

	std::vector<SourceSentenceUnit> *mySSU_SS;

};

#endif // _SIMPLE_SENTENCE_H_
