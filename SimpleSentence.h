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

	std::vector<SentencePart> mySubject;
	std::vector<SentencePart> myPredicate;

	std::vector<SentenceUnit> mySentenceUnits;

};

#endif 
