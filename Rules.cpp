#include "Rules.h"
#include "SyntaxAnalyzer.h"

bool SubjectCoordinationRule::accepts(const std::vector<SentencePart> &subjects) const {
	if (!subjects.empty()) {

		std::vector<WordDescription::Grammem> grammems = this->getGrammems();
		std::vector<WordDescription::PartOfSpeech> parts = this->getParts();
		const WordDescription &first = subjects.at(0).myWordDescription;

		for (std::vector<SentencePart>::const_iterator it = subjects.begin();
		 it != subjects.end(); ++it) {
			if (!WordDescription::areCoordinatedGrammems(it->myWordDescription, first, grammems)) {
				return false;
			}
			if (!WordDescription::areCoordinatedParts(it->myWordDescription, first, parts)) {
				return false;
			}
		}
	}
	return true;
}

bool PredicateCoordinationRule::accepts(const std::vector<SentencePart> &predicates) const {
	if (!predicates.empty()) {

		std::vector<WordDescription::Grammem> grammems = this->getGrammems();
		grammems.push_back(WordDescription::PASTTENSE);
		grammems.push_back(WordDescription::PRESENTTENSE);
		grammems.push_back(WordDescription::FUTURETENSE);
		const WordDescription &first = predicates.at(0).myWordDescription;

		for (std::vector<SentencePart>::const_iterator it = predicates.begin();
		 it != predicates.end(); ++it) {
			if (!WordDescription::areCoordinatedGrammems(it->myWordDescription, first, grammems)) {
				return false;
			}
		}
        }
        return true;
}

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

