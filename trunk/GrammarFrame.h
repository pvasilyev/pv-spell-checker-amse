#ifndef _GRAMMAR_FRAME_H_
#define _GRAMMAR_FRAME_H_

#include <vector>

class SourceSentenceUnit;
class WordDescription;

class GrammarFrame {

public:
	GrammarFrame(std::vector<SourceSentenceUnit> &ssu);

	void buildGrammarFrame();

	std::vector<std::vector<WordDescription>::iterator> getGrammarFrame();
	std::vector<std::vector<WordDescription>::iterator> getObject() const;
	std::vector<std::vector<SourceSentenceUnit>::iterator> getObjectText() const;
	std::vector<std::vector<WordDescription>::iterator> getPredicate() const;
	std::vector<std::vector<SourceSentenceUnit>::iterator> getPredicateText() const;

private:
	std::vector<std::vector<WordDescription>::iterator> myGrammarFrame;

	std::vector<SourceSentenceUnit> mySSU_GF;

	std::vector<std::vector<WordDescription>::iterator> myObject;
	std::vector<std::vector<SourceSentenceUnit>::iterator> myObjectText;
	std::vector<std::vector<WordDescription>::iterator> myPredicate;
	std::vector<std::vector<SourceSentenceUnit>::iterator> myPredicateText;

};

#endif // _GRAMMAR_FRAME_H_
