#include "Rules.h"
#include "SyntaxAnalyzer.h"
#include "VLemmatizer.h"

bool SubjectCoordinationRule::accepts(const std::vector<SentencePart> &subjects) const {
	if (!subjects.empty()) {
		const WordDescription &firstSubject = subjects.at(0).myWordDescription;

		std::vector<WordDescription::Grammem> vectorGrammems;
		vectorGrammems.push_back(WordDescription::PLURAL);
		vectorGrammems.push_back(WordDescription::SINGULAR);
		vectorGrammems.push_back(WordDescription::MASCULINUM);
		vectorGrammems.push_back(WordDescription::FEMINUM);
		vectorGrammems.push_back(WordDescription::NEUTRUM);

		std::vector<WordDescription::PartOfSpeech> vectorPartsOfSpeech;
		vectorPartsOfSpeech.push_back(WordDescription::NOUN);
		vectorPartsOfSpeech.push_back(WordDescription::PRONOUN);

		for (std::vector<SentencePart>::const_iterator it = subjects.begin();
		     it != subjects.end(); ++it) {
			for (std::vector<WordDescription::Grammem>::const_iterator jt = vectorGrammems.begin();
				jt != vectorGrammems.end(); ++jt) {
				if (!it->myWordDescription.areCoordinatedGrammem(firstSubject, *jt)) {
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

		std::vector<WordDescription::Grammem> vectorGrammems;
		vectorGrammems.push_back(WordDescription::PLURAL);
		vectorGrammems.push_back(WordDescription::SINGULAR);
		vectorGrammems.push_back(WordDescription::MASCULINUM);
		vectorGrammems.push_back(WordDescription::FEMINUM);
		vectorGrammems.push_back(WordDescription::NEUTRUM);
		vectorGrammems.push_back(WordDescription::PASTTENSE);
		vectorGrammems.push_back(WordDescription::PRESENTTENSE);
		vectorGrammems.push_back(WordDescription::FUTURETENSE);

		for (std::vector<SentencePart>::const_iterator it = predicates.begin();
		     it != predicates.end(); ++it) {
                        for (std::vector<WordDescription::Grammem>::const_iterator jt = vectorGrammems.begin();
                                jt != vectorGrammems.end(); ++jt) {
                                if (!it->myWordDescription.areCoordinatedGrammem(firstPredicate, *jt)) {
                                        return false;
                                }
                        }
                }
        }
        return true;
}
