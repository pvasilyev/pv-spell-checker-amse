#ifndef _RULES_H_
#define _RULES_H_

#include <vector>

#include "VLemmatizer.h"

class SentencePart;

class Rule {

public:
	virtual bool accepts(const std::vector<SentencePart> &) const = 0;

protected:
	virtual std::vector<WordDescription::Grammem> getGrammems() const;
	virtual std::vector<WordDescription::PartOfSpeech> getParts() const;

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
