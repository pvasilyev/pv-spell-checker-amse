#ifndef _GRAMMAR_FRAME_H_
#define _GRAMMAR_FRAME_H_

#include <vector>

class SourceSentenceUnit;
class WordDescription;

class GrammarFrame {

public:
	GrammarFrame(const std::vector<SourceSentenceUnit> &ssu);

	void buildGrammarFrame();

	std::vector<std::vector<WordDescription>::const_iterator> getObject() const;
	std::vector<std::vector<SourceSentenceUnit>::const_iterator> getObjectText() const;
	std::vector<std::vector<WordDescription>::const_iterator> getPredicate() const;
	std::vector<std::vector<SourceSentenceUnit>::const_iterator> getPredicateText() const;

private:

	const std::vector<SourceSentenceUnit> mySourceSentenceUnit_GrammarFrame;

	std::vector<std::vector<WordDescription>::const_iterator> myObject;
	std::vector<std::vector<SourceSentenceUnit>::const_iterator> myObjectText;
	std::vector<std::vector<WordDescription>::const_iterator> myPredicate;
	std::vector<std::vector<SourceSentenceUnit>::const_iterator> myPredicateText;

};

#endif
