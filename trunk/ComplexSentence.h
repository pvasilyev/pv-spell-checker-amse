#ifndef _COMPLEX_SENTENCE_H_
#define _COMPLEX_SENTENCE_H_

#include <ostream>
#include <vector>

class SentenceManager;
class SimpleSentence;
class SentenceUnit;
class SyntaxAnalyzer;
class WordDescription;

class ComplexSentence {

public:
	ComplexSentence(const std::vector<SentenceUnit> &ssu);

	void parse_cs();
	void print_cs(std::ostream &os);

private:
	std::vector<SimpleSentence> myVectorSimpleSentence;

	const std::vector<SentenceUnit> mySentenceUnit;
};

#endif
