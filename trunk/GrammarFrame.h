#ifndef _GRAMMAR_FRAME_H_
#define _GRAMMAR_FRAME_H_

#include <vector>

class SentenceUnit;
class WordDescription;

class GrammarFrame {

public:
	GrammarFrame(const std::vector<SentenceUnit> &su);

	void buildGrammarFrame();

	std::vector<WordDescription> getObject() const;
	std::vector<SentenceUnit> getObjectText() const;
	std::vector<WordDescription> getPredicate() const;
	std::vector<SentenceUnit> getPredicateText() const;

private:

	const std::vector<SentenceUnit> mySentenceUnit;

	std::vector<WordDescription> myObject;
	std::vector<SentenceUnit> myObjectText;
	std::vector<WordDescription> myPredicate;
	std::vector<SentenceUnit> myPredicateText;

};

#endif
