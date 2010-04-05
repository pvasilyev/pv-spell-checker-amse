#ifndef _COMPLEX_SENTENCE_H_
#define _COMPLEX_SENTENCE_H_

#include <ostream>
#include <vector>

class SimpleSentence;
class SentenceUnit;
class WordDescription;

class ComplexSentence {

public:
	ComplexSentence(const std::vector<SentenceUnit> &ssu);

	void print(std::ostream &os) const;

private:
	std::vector<SimpleSentence> myVectorSimpleSentence;

	const std::vector<SentenceUnit> mySentenceUnits;
};

#endif
