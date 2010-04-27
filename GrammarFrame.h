#ifndef _GRAMMAR_FRAME_H_
#define _GRAMMAR_FRAME_H_

#include <vector>

class SentenceUnit;
class WordDescription;
class SentencePart;

class GrammarFrame {

public:
	GrammarFrame(const std::vector<SentenceUnit> &su);

	std::vector<SentencePart> getPredicate() const;
	std::vector<SentencePart> getSubject() const;

private:
	bool checkPredicateCoordination() const;
	bool checkSubjectCoordination() const;
	void doFiltration(bool subjectsInCoordination, bool predicatesInCoordination);
	void tryToAddSubject(const SentenceUnit &current, const SentenceUnit &previous,
			const WordDescription &description, const bool &isFirstSentenceUnit);

	const std::vector<SentenceUnit> mySentenceUnits;

	std::vector<SentencePart> mySubject;
	std::vector<SentencePart> myPredicate;

};

#endif
