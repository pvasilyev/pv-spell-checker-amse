#ifndef _COMPLEX_SENTENCE_H_
#define _COMPLEX_SENTENCE_H_

#include <ostream>
#include <vector>

class SentenceManager;
class SimpleSentence;
class SourceSentenceUnit;
class SyntaxAnalyzer;
class WordDescription;

class ComplexSentence {

public:
	ComplexSentence(const std::vector<SourceSentenceUnit> &ssu);

	void parse_cs();
	void print_cs(std::ostream &os);

private:
	std::vector<SimpleSentence> myVectorSimpleSentence;
	//SentenceManager *mySentenceManager;

	const std::vector<SourceSentenceUnit> mySourceSentenceUnit_ComplexSentence;
};

#endif
