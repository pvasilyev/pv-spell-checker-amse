#ifndef _GRAMMAR_FRAME_H_
#define _GRAMMAR_FRAME_H_

#include <vector>

class SentenceUnit;
class WordDescription;
class SentencePart;

class GrammarFrame {

public:
	GrammarFrame(const std::vector<SentenceUnit> &su);

	std::vector<WordDescription> getSubject() const;
	std::vector<SentenceUnit> getSubjectText() const;
	std::vector<WordDescription> getPredicate() const;
	std::vector<SentenceUnit> getPredicateText() const;

private:
	bool checkPredicateCoordination() const;
	bool checkSubjectCoordination() const;
	void doFiltration(bool subjectsInCoordination, bool predicatesInCoordination);
	void tryToAddSubject(std::vector<SentenceUnit>::const_iterator it, std::vector<WordDescription>::const_iterator jt);

	const std::vector<SentenceUnit> mySentenceUnits;

	std::vector<WordDescription> mySubject;
	std::vector<SentenceUnit> mySubjectText;
	std::vector<SentencePart> mySubjectSentencePart;
	std::vector<WordDescription> myPredicate;
	std::vector<SentenceUnit> myPredicateText;
	std::vector<SentencePart> myPredicateSentencePart;

};

#endif
