#ifndef _GRAMMAR_FRAME_H_
#define _GRAMMAR_FRAME_H_

#include <vector>

class SentenceUnit;
class WordDescription;

class GrammarFrame {

public:
	GrammarFrame(const std::vector<SentenceUnit> &su);

	void buildGrammarFrame();

	std::vector<WordDescription> getSubject() const;
	std::vector<SentenceUnit> getSubjectText() const;
	std::vector<WordDescription> getPredicate() const;
	std::vector<SentenceUnit> getPredicateText() const;

private:

	bool myPredicatesInCoordination;
	bool mySubjectsInCoordination;

	const std::vector<SentenceUnit> mySentenceUnits;

	std::vector<WordDescription> mySubject;
	std::vector<SentenceUnit> mySubjectText;
	std::vector<WordDescription> myPredicate;
	std::vector<SentenceUnit> myPredicateText;

};

class PredicateCoordinationCount {

public:
	PredicateCoordinationCount();
	int mySingular;
	int myPlural;
	int myPast;
	int myPresent;
	int myFuture;
	int myFeminum;
	int myMasculinum;
	int myNeutrum;

};

class SubjectCoordinationCount {

public:
	SubjectCoordinationCount();
	int mySingular;
	int myPlural;
	int myFeminum;
	int myMasculinum;
	int myNeutrum;
	int myNoun;
	int myPronoun;

};

#endif
