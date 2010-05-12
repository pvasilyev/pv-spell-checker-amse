#include "Rules.h"
#include "SyntaxAnalyzer.h"

std::vector<WordDescription::Grammem> Rule::getGrammems() const {
	std::vector<WordDescription::Grammem> vector;
	vector.push_back(WordDescription::PLURAL);
	vector.push_back(WordDescription::SINGULAR);
	vector.push_back(WordDescription::MASCULINUM);
	vector.push_back(WordDescription::FEMINUM);
	vector.push_back(WordDescription::NEUTRUM);
	return vector;
}

std::vector<WordDescription::PartOfSpeech> Rule::getParts() const {
	std::vector<WordDescription::PartOfSpeech> vector;
	vector.push_back(WordDescription::NOUN);
	vector.push_back(WordDescription::PRONOUN);
	return vector;
}

bool Rule::grammemsAccept(const std::vector<SentencePart> &vectorSentenceParts,
			const std::vector<WordDescription::Grammem> &vectorGrammems) const {

	const WordDescription &firstSentencePart = vectorSentenceParts.at(0).myWordDescription;

	for (std::vector<SentencePart>::const_iterator it = vectorSentenceParts.begin();
	     it != vectorSentenceParts.end(); ++it) {
		for (std::vector<WordDescription::Grammem>::const_iterator jt = vectorGrammems.begin();
			jt != vectorGrammems.end(); ++jt) {
			if (!WordDescription::areCoordinatedGrammems(it->myWordDescription, firstSentencePart, *jt)) {
				return false;
			}
		}
	}
	return true;
}

bool Rule::partsAccept(const std::vector<SentencePart> &vectorSentenceParts,
			const std::vector<WordDescription::PartOfSpeech> &vectorPartsOfSpeech) const {

	const WordDescription &firstSentencePart = vectorSentenceParts.at(0).myWordDescription;

	for (std::vector<SentencePart>::const_iterator it = vectorSentenceParts.begin();
	     it != vectorSentenceParts.end(); ++it) {
		for (std::vector<WordDescription::PartOfSpeech>::const_iterator jt = vectorPartsOfSpeech.begin();
			jt != vectorPartsOfSpeech.end(); ++jt) {
			if (!it->myWordDescription.areCoordinatedPart(firstSentencePart, *jt)) {
				return false;
			}
		}
	}
	return true;
}

bool SubjectCoordinationRule::accepts(const std::vector<SentencePart> &subjects) const {
	if (!subjects.empty()) {

		std::vector<WordDescription::Grammem> vectorGrammems = this->getGrammems();
		if (!grammemsAccept(subjects, vectorGrammems)) {
			return false;
		}

		std::vector<WordDescription::PartOfSpeech> vectorPartsOfSpeech = this->getParts();
		if (!partsAccept(subjects, vectorPartsOfSpeech)) {
			return false;
		}

	}
	return true;
}

bool PredicateCoordinationRule::accepts(const std::vector<SentencePart> &predicates) const {
	if (!predicates.empty()) {

		std::vector<WordDescription::Grammem> vectorGrammems = this->getGrammems();
		vectorGrammems.push_back(WordDescription::PASTTENSE);
		vectorGrammems.push_back(WordDescription::PRESENTTENSE);
		vectorGrammems.push_back(WordDescription::FUTURETENSE);
		if (!grammemsAccept(predicates, vectorGrammems)) {
			return false;
		}

        }
        return true;
}
