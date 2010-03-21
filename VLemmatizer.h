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
		PLURAL = (u_int64_t)1 << 0,
		SINGULAR = (u_int64_t)1 << 1,

		NOMINATIV = (u_int64_t)1 << 2,
		GENITIV = (u_int64_t)1 << 3,
		DATIV = (u_int64_t)1 << 4,
		ACCUSATIV = (u_int64_t)1 << 5,
		INSTRUMENTALIS = (u_int64_t)1 << 6,
		LOCATIV = (u_int64_t)1 << 7,
		VOCATIV = (u_int64_t)1 << 8,

		MASCULINUM = (u_int64_t)1 << 9,
		FEMINUM = (u_int64_t)1 << 10,
		NEUTRUM = (u_int64_t)1 << 11,
		MASCFEM = (u_int64_t)1 << 12,

		SHORTFORM = (u_int64_t)1 << 13,

		PRESENTTENSE = (u_int64_t)1 << 14,
		FUTURETENSE = (u_int64_t)1 << 15,
		PASTTENSE = (u_int64_t)1 << 16,

		FIRSTPERSON = (u_int64_t)1 << 17,
		SECONDPERSON = (u_int64_t)1 << 18,
		THIRDPERSON = (u_int64_t)1 << 19,

		IMPERATIV = (u_int64_t)1 << 20,

		ANIMATIVE = (u_int64_t)1 << 21,
		NONANIMATIV = (u_int64_t)1 << 22,

		COMPARATIVE = (u_int64_t)1 << 23,

		PERFECTIVE = (u_int64_t)1 << 24,
		NONPERFECTIVE = (u_int64_t)1 << 25,

		NONTRANSITIVE = (u_int64_t)1 << 26,
		TRANSITIVE = (u_int64_t)1 << 27,

		ACTIVEVOICE = (u_int64_t)1 << 28,
		PASSIVEVOICE = (u_int64_t)1 << 29,

		INDECLINABLE = (u_int64_t)1 << 30,
		INITIALISM = (u_int64_t)1 << 31,

		PATRONOMIC = (u_int64_t)1 << 32,

		TOPONYM = (u_int64_t)1 << 33,
		ORGANISATION = (u_int64_t)1 << 34,

		QUALITATIVE = (u_int64_t)1 << 35,
		DEFACTOSINGTANTUM = (u_int64_t)1 << 36,

		INTERROGATIVE = (u_int64_t)1 << 37,
		DEMONSTRATIVE = (u_int64_t)1 << 38,

		NAME = (u_int64_t)1 << 39,
		SURNAME = (u_int64_t)1 << 40,
		IMPERSONAL = (u_int64_t)1 << 41,
		SLANG = (u_int64_t)1 << 42,
		MISPRINT = (u_int64_t)1 << 43,
		COLLOQUIAL = (u_int64_t)1 << 44,
		POSSESIVE = (u_int64_t)1 << 45,
		ARCHAISM = (u_int64_t)1 << 46,
		SECONDCASE = (u_int64_t)1 << 47,
		POETRY = (u_int64_t)1 << 48,
		PROFESSION = (u_int64_t)1 << 49,
		SUPERLATIVE = (u_int64_t)1 << 50,
		POSITIVE = (u_int64_t)1 << 51
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

	friend class ComplexSentence;
	friend class GrammarFrame;
	friend class GrammarUnits;
	friend class SentenceManager;
	friend class SimpleSentence;
	friend class SyntaxAnalyzer;
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

#endif //_VASILIEV_LEMMATIZER_H_
