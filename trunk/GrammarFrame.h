#ifndef _GRAMMAR_FRAME_H_
#define _GRAMMAR_FRAME_H_

#include <vector>

class SentenceUnit;
class WordDescription;
class SentencePart;

class GrammarFrame {

public:
	GrammarFrame(const std::vector<SentenceUnit> &su);

	std::vector<SentencePart> getPredicateSentencePart() const;
	std::vector<SentencePart> getSubjectSentencePart() const;

private:
	bool checkPredicateCoordination() const;
	bool checkSubjectCoordination() const;
	void doFiltration(bool subjectsInCoordination, bool predicatesInCoordination);
	void tryToAddSubject(std::vector<SentenceUnit>::const_iterator it, std::vector<WordDescription>::const_iterator jt);

	const std::vector<SentenceUnit> mySentenceUnits;

	std::vector<SentencePart> mySubjectSentencePart;
	std::vector<SentencePart> myPredicateSentencePart;

};

#endif
