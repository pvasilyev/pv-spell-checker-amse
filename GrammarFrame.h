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
	void tryToAddSubject(std::vector<SentenceUnit>::const_iterator it, const WordDescription &description);

	const std::vector<SentenceUnit> mySentenceUnits;

	std::vector<SentencePart> mySubject;
	std::vector<SentencePart> myPredicate;

};

class Rule {

public:
	virtual bool accepts(...) = 0;

};

class SubjectCoordinationRule : public Rule {

public:
	bool accepts(const std::vector<SentencePart> &subjects) const;

};

class PredicateCoordinationRule : public Rule {

public:
	bool accepts(const std::vector<SentencePart> &predicates) const;

};

#endif
