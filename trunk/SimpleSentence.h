#ifndef _SIMPLE_SENTENCE_H_
#define _SIMPLE_SENTENCE_H_

#include <vector>
#include <ostream>

class ComplexSentence;
class GrammarFrame;
class GrammarUnits;
class SentenceManager;
class SourceSentenceUnit;
class WordDescription;

class SimpleSentence {

public:
	SimpleSentence(std::vector<SourceSentenceUnit> &ssu);
	SimpleSentence(const SimpleSentence &ss);
	~SimpleSentence();

	void parse_ss();
	void print_ss(std::ostream &os);

private:
	GrammarFrame *myGrammarFrame;
	//GrammarUnits *myGrammarUnits;

	std::vector<std::vector<WordDescription>::iterator> myObject;
	std::vector<std::vector<SourceSentenceUnit>::iterator> myObjectText;
	std::vector<std::vector<WordDescription>::iterator> myPredicate;
	std::vector<std::vector<SourceSentenceUnit>::iterator> myPredicateText;

	std::vector<SourceSentenceUnit> mySSU_SS;

};

#endif // _SIMPLE_SENTENCE_H_
