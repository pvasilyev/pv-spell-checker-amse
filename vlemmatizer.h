#ifndef _VASILIEV_LEMMATIZER_H_
#define _VASILIEV_LEMMATIZER_H_

#include <turglem/lemmatizer.h>
#include <turglem/russian/charset_adapters.h>
#include <MAFSA/charset_adapter.h>

#include <list>
#include <string>
#include <vector>

class WordDescription {

public:
	enum PartOfSpeech {
		NOUN = 0,
		ADJECTIVE_FULL = 1,
		VERB = 2,
		PRONOUN = 3,
		PRONOUN_PRILAGATIELNOE = 4,
		PRONOUN_PREDIKATIV = 5,
		NUMERAL = 6,
		NUMERAL_PORIADKOVOE = 7,
		ADVERB = 8,
		PREDIKATIV  = 9,
		PREPOSAL = 10,
		POSL = 11,
		CONJUNCTOIN = 12,
		INTERJUNCTION = 13,
		INPUT = 14,
		PHRASE = 15,
		PARTICLE = 16,
		ADJECTIVE_SHORT = 17,
		PARTICIPLE = 18,
		ADVERB_PARTICIPLE = 19,
		PARTICIPLE_SHORT = 20,
		INFINITIVE = 21
	};

	enum Grammem {
		Plural = 0,
		Singular = 1,

		Nominativ = 2,
		Genitiv = 3,
		Dativ = 4,
		Accusativ = 5,
		Instrumentalis = 6,
		Locativ = 7,
		Vocativ = 8,

		Masculinum = 9,
		Feminum = 10,
		Neutrum = 11,
		MascFem = 12,

		ShortForm = 13,

		PresentTense = 14,
		FutureTense = 15,
		PastTense = 16,

		FirstPerson = 17,
		SecondPerson = 18,
		ThirdPerson = 19,

		Imperative = 20,

		Animative = 21,
		NonAnimative = 22,

		Comparative = 23,

		Perfective = 24,
		NonPerfective = 25,

		NonTransitive = 26,
		Transitive = 27,

		ActiveVoice = 28,
		PassiveVoice = 29,

		Indeclinable = 30,
		Initialism = 31,

		Patronymic = 32,

		Toponym = 33,
		Organisation = 34,

		Qualitative = 35,
		DeFactoSingTantum = 36,

		Interrogative = 37,
		Demonstrative = 38,

		Name = 39,
		SurName = 40,
		Impersonal = 41,
		Slang = 42,
		Misprint = 43,
		Colloquial = 44,
		Possessive = 45,
		Archaism = 46,
		SecondCase = 47,
		Poetry = 48,
		Profession = 49,
		Superlative = 50,
		Positive = 51
	};

private:
	WordDescription::PartOfSpeech myPartOfSpeech;
	std::vector<WordDescription::Grammem> myGrammems;

private:
	WordDescription(PartOfSpeech partOfSpeech, u_int64_t iGr);

public:
	WordDescription::PartOfSpeech &getPartOfSpeech();
	std::vector<Grammem> &getGrammems();

	void printPartOfSpeech(std::ostream &out);
	void printGrammems(std::ostream &out);

	friend class VLemmatizer;
};

class VLemmatizer{

private:
	turglem myLem;

	int myErr_no;
	int myErr_what;

	MAFSA_conv_string_to_letters my_s2l;
	MAFSA_conv_letters_to_string my_l2s;

public:
	VLemmatizer();
	~VLemmatizer();

	std::vector<WordDescription> lemmatize(const std::string &word) const;
};

#endif //_VASILIEV_VLEMMATIZER_H_
