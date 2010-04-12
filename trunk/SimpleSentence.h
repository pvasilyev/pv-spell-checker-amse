#ifndef _SIMPLE_SENTENCE_H_
#define _SIMPLE_SENTENCE_H_

#include <vector>
#include <ostream>

class SentenceUnit;
class SentencePart;
class WordDescription;

class SimpleSentence {

public:
	SimpleSentence(const std::vector<SentenceUnit> &su);

	void print(std::ostream &os) const;

private:

	std::vector<WordDescription> mySubject;
	std::vector<SentenceUnit> mySubjectText;
	std::vector<SentencePart> mySubjectSentencePart;
	std::vector<WordDescription> myPredicate;
	std::vector<SentenceUnit> myPredicateText;
	std::vector<SentencePart> myPredicateSentencePart;

	std::vector<SentenceUnit> mySentenceUnits;

};

#endif 
