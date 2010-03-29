#ifndef _SIMPLE_SENTENCE_H_
#define _SIMPLE_SENTENCE_H_

#include <vector>
#include <ostream>

class ComplexSentence;
class GrammarFrame;
class GrammarUnits;
class SentenceManager;
class SentenceUnit;
class WordDescription;

class SimpleSentence {

public:
	SimpleSentence(const std::vector<SentenceUnit> &su);
	SimpleSentence(const SimpleSentence &ss);
	~SimpleSentence();

	SimpleSentence& operator = (const SimpleSentence &ss);

	void print_ss(std::ostream &os) const;

private:
	GrammarFrame *myGrammarFrame;

	std::vector<WordDescription> myObject;
	std::vector<SentenceUnit> myObjectText;
	std::vector<WordDescription> myPredicate;
	std::vector<SentenceUnit> myPredicateText;

	std::vector<SentenceUnit> mySentenceUnit;

};

#endif 
