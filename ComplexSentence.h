#ifndef _COMPLEX_SENTENCE_H_
#define _COMPLEX_SENTENCE_H_

#include <vector>

class SentenceManager;
class SimpleSentence;
class SourceSentenceUnit;
class SyntaxAnalyzer;

class ComplexSentence {

private:
	std::vector<SimpleSentence> myVectorSimpleSentence;
	SentenceManager *mySentenceManager;

	std::vector<SourceSentenceUnit> *mySSU_CS;

public:
	ComplexSentence(std::vector<SourceSentenceUnit> &ssu);

	void parse_cs();

};

#endif // _COMPLEX_SENTENCE_H_
