#ifndef _RULES_H_
#define _RULES_H_

#include <vector>

#include "SyntaxAnalyzer.h"

class Rule {

public:
	virtual bool accepts(const std::vector<SentencePart> &) const = 0;

};

class SubjectCoordinationRule : public Rule {

public:
	virtual bool accepts(const std::vector<SentencePart> &) const;

};

class PredicateCoordinationRule : public Rule {

public:
	virtual bool accepts(const std::vector<SentencePart> &) const;

};

#endif
