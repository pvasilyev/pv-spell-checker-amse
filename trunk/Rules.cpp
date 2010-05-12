#include "Rules.h"
#include "SyntaxAnalyzer.h"
#include "VLemmatizer.h"

std::vector<WordDescription::Grammem> Rule::getGrammems() const {
	std::vector<WordDescription::Grammem> vector;
	vector.push_back(WordDescription::PLURAL);
	vector.push_back(WordDescription::SINGULAR);
	vector.push_back(WordDescription::MASCULINUM);
	vector.push_back(WordDescription::FEMINUM);
	vector.push_back(WordDescription::NEUTRUM);
	return vector;
}

bool SubjectCoordinationRule::accepts(const std::vector<SentencePart> &subjects) const {
	if (!subjects.empty()) {
		const WordDescription &firstSubject = subjects.at(0).myWordDescription;

		std::vector<WordDescription::Grammem> vectorGrammems = this->getGrammems();

		std::vector<WordDescription::PartOfSpeech> vectorPartsOfSpeech;
		vectorPartsOfSpeech.push_back(WordDescription::NOUN);
		vectorPartsOfSpeech.push_back(WordDescription::PRONOUN);

		for (std::vector<SentencePart>::const_iterator it = subjects.begin();
		     it != subjects.end(); ++it) {
			for (std::vector<WordDescription::Grammem>::const_iterator jt = vectorGrammems.begin();
				jt != vectorGrammems.end(); ++jt) {
				if (!WordDescription::areCoordinatedGrammems(it->myWordDescription, firstSubject, *jt)) {
					return false;
				}
			}
			for (std::vector<WordDescription::PartOfSpeech>::const_iterator jt = vectorPartsOfSpeech.begin();
				jt != vectorPartsOfSpeech.end(); ++jt) {
				if (!it->myWordDescription.areCoordinatedPart(firstSubject, *jt)) {
					return false;
				}
			}
		}
	}
	return true;
}

bool PredicateCoordinationRule::accepts(const std::vector<SentencePart> &predicates) const {
	if (!predicates.empty()) {
		const WordDescription &firstPredicate = predicates.at(0).myWordDescription;

		std::vector<WordDescription::Grammem> vectorGrammems = this->getGrammems();
		vectorGrammems.push_back(WordDescription::PASTTENSE);
		vectorGrammems.push_back(WordDescription::PRESENTTENSE);
		vectorGrammems.push_back(WordDescription::FUTURETENSE);

		for (std::vector<SentencePart>::const_iterator it = predicates.begin();
		     it != predicates.end(); ++it) {
                        for (std::vector<WordDescription::Grammem>::const_iterator jt = vectorGrammems.begin();
                                jt != vectorGrammems.end(); ++jt) {
                                if (!WordDescription::areCoordinatedGrammems(it->myWordDescription, firstPredicate, *jt)) {
                                        return false;
                                }
                        }
                }
        }
        return true;
}
