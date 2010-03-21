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
	SimpleSentence(const std::vector<SourceSentenceUnit> &ssu);
	SimpleSentence(const SimpleSentence &ss);
	~SimpleSentence();

	SimpleSentence& operator = (const SimpleSentence &ss);

	void parse_ss();
	void print_ss(std::ostream &os) const;

private:
	GrammarFrame *myGrammarFrame;

	std::vector<std::vector<WordDescription>::const_iterator> myObject;
	std::vector<std::vector<SourceSentenceUnit>::const_iterator> myObjectText;
	std::vector<std::vector<WordDescription>::const_iterator> myPredicate;
	std::vector<std::vector<SourceSentenceUnit>::const_iterator> myPredicateText;

	std::vector<SourceSentenceUnit> mySourceSentenceUnit_SimpleSentence;

};

#endif 
