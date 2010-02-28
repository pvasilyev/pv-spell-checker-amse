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
		PLURAL = 0,
		SINGULAR = 1,

		NOMINATIV = 2,
		GENITIV = 3,
		DATIV = 4,
		ACCUSATIV = 5,
		INSTRUMENTALIS = 6,
		LOCATIV = 7,
		VOCATIV = 8,

		MASCULINUM = 9,
		FEMINUM = 10,
		NEUTRUM = 11,
		MASCFEM = 12,

		SHORTFORM = 13,

		PRESENTTENSE = 14,
		FUTURETENSE = 15,
		PASTTENSE = 16,

		FIRSTPERSON = 17,
		SECONDPERSON = 18,
		THIRDPERSON = 19,

		IMPERATIV = 20,

		ANIMATIVE = 21,
		NONANIMATIV = 22,

		COMPARATIVE = 23,

		PERFECTIVE = 24,
		NONPERFECTIVE = 25,

		NONTRANSITIVE = 26,
		TRANSITIVE = 27,

		ACTIVEVOICE = 28,
		PASSIVEVOICE = 29,

		INDECLINABLE = 30,
		INITIALISM = 31,

		PATRONOMIC = 32,

		TOPONYM = 33,
		ORGANISATION = 34,

		QUALITATIVE = 35,
		DEFACTOSINGTANTUM = 36,

		INTERROGATIVE = 37,
		DEMONSTRATIVE = 38,

		NAME = 39,
		SURNAME = 40,
		IMPERSONAL = 41,
		SLANG = 42,
		MISPRINT = 43,
		COLLOQUIAL = 44,
		POSSESIVE = 45,
		ARCHAISM = 46,
		SECONDCASE = 47,
		POETRY = 48,
		PROFESSION = 49,
		SUPERLATIVE = 50,
		POSITIVE = 51
	};

private:
	WordDescription::PartOfSpeech myPartOfSpeech;
	std::vector<WordDescription::Grammem> myGrammems;
	u_int64_t myGrammem;

	WordDescription(PartOfSpeech partOfSpeech, u_int64_t iGr);

public:
	WordDescription::PartOfSpeech &getPartOfSpeech();
	std::vector<Grammem> &getGrammems();

	void printPartOfSpeech(std::ostream &os);
	void printGrammems(std::ostream &os);

	friend class VLemmatizer;
	friend class Syntax;
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

#endif //_VASILIEV_LEMMATIZER_H_
