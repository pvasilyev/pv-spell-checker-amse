#include <fstream>
#include <iostream>
#include <stdio.h>

#include "VLemmatizer.h"
 
VLemmatizer::VLemmatizer(){
	myLem = turglem_load("/usr/local/share/turglem/russian/dict_russian.auto",
			   "/usr/local/share/turglem/russian/prediction_russian.auto",
			   "/usr/local/share/turglem/russian/paradigms_russian.bin",
			   &myErr_no, &myErr_what);

	my_s2l = LEM_RUSSIAN_conv_string_to_letters_utf8;
	my_l2s = LEM_RUSSIAN_conv_letters_to_string_utf8;
}

VLemmatizer::~VLemmatizer(){
	turglem_close(myLem);
}

WordDescription::WordDescription() {}

WordDescription::WordDescription(WordDescription::PartOfSpeech partOfSpeech, u_int64_t iGr) {
	myPartOfSpeech = partOfSpeech;
	myGrammem = iGr;
	for (int i = 0; i < 51; ++i) {
		if (iGr & ((u_int64_t)1 << i)) {
			myGrammems.push_back((Grammem)i);
		}
	}
}

std::vector<WordDescription> VLemmatizer::lemmatize(const std::string &srcStr) const {

	std::vector<WordDescription> vRes;
	const char *s = srcStr.data();
	MAFSA_letter l[32];
	ssize_t ssz_src;
	size_t sz_lem_res;
	int lem_res[32 * 2];
	
	ssz_src = my_s2l(s, l, 32);
	if (ssz_src < 0) {
		printf("can't convert word <%s> to letters! Is it russian word in UTF-8?\n", s);
		return vRes;
	}

	sz_lem_res = turglem_lemmatize(myLem, l, ssz_src, lem_res, 32, RUSSIAN_LETTER_DELIM, 0);
	
	for (size_t i = 0; i < sz_lem_res; ++i){
		WordDescription wdTmp((WordDescription::PartOfSpeech)turglem_paradigms_get_part_of_speech(myLem->paradigms, lem_res[i*2], lem_res[i*2 + 1]), turglem_paradigms_get_grammem(myLem->paradigms, lem_res[i*2], lem_res[i*2 + 1]));
		vRes.push_back(wdTmp);
	}
	return vRes;
}

WordDescription::PartOfSpeech &WordDescription::getPartOfSpeech() {
	return myPartOfSpeech;
}

bool WordDescription::hasSamePart(const WordDescription &description) const {
	return description.myPartOfSpeech == myPartOfSpeech;
}

bool WordDescription::hasSameNumeral(const WordDescription &description) const {
	return (((this->hasGrammem(WordDescription::SINGULAR)) && 
	(description.hasGrammem(WordDescription::SINGULAR))) ||
	((this->hasGrammem(WordDescription::PLURAL)) && 
	(description.hasGrammem(WordDescription::PLURAL))));
}

bool WordDescription::hasSameGenus(const WordDescription &description) const {
	return (((this->hasGrammem(WordDescription::MASCULINUM)) && 
	(description.hasGrammem(WordDescription::MASCULINUM))) ||
	((this->hasGrammem(WordDescription::FEMINUM)) && 
	(description.hasGrammem(WordDescription::FEMINUM))) ||
	((this->hasGrammem(WordDescription::NEUTRUM)) && 
	(description.hasGrammem(WordDescription::NEUTRUM))) ||
	((this->hasGrammem(WordDescription::MASCFEM)) && 
	(description.hasGrammem(WordDescription::MASCFEM))));
}

bool WordDescription::hasPart(const PartOfSpeech &pos) const {
	return (myPartOfSpeech == pos);
}

bool WordDescription::hasGrammem(const Grammem &grammem) const {
	return (myGrammem & (((u_int64_t)1) << grammem)) != 0;
}

bool WordDescription::areCoordinatedGrammem(const WordDescription &wd, Grammem grammem) const {
	return hasGrammem(grammem) == wd.hasGrammem(grammem);
}

bool WordDescription::areCoordinatedPart(const WordDescription &wd, PartOfSpeech pos) const {
	return wd.myPartOfSpeech == pos;
}

std::vector<WordDescription::Grammem> &WordDescription::getGrammems() {
	return myGrammems;
}


void WordDescription::printPartOfSpeech(std::ostream &os) {
	switch (myPartOfSpeech){
		case 0: os << "Part Of Speech = существительное\n"                  ; break;
		case 1: os << "Part Of Speech = прилагательное\n"                   ; break;
		case 2: os << "Part Of Speech = глагол\n"                           ; break;
		case 3: os << "Part Of Speech = местоимение\n"                      ; break;
		case 4: os << "Part Of Speech = местоименное прилагательное\n"      ; break;
		case 5: os << "Part Of Speech = местоимение-предикатив\n"           ; break; // НЕЧЕГО слезы лить.
		case 6: os << "Part Of Speech = числительное\n"                     ; break;
		case 7: os << "Part Of Speech = порядковое числительное\n"          ; break;
		case 8: os << "Part Of Speech = наречие\n"                          ; break;
		case 9: os << "Part Of Speech = категория состояния (предикатив)\n" ; break; // "мне каково?": стыдно, холодно, просто
		case 10: os << "Part Of Speech = предлог\n"                         ; break;
		case 11: os << "Part Of Speech = posl\n"                            ; break;
		case 12: os << "Part Of Speech = союз\n"                            ; break;
		case 13: os << "Part Of Speech = междометие\n"                      ; break;
		case 14: os << "Part Of Speech = вводное слово\n"                   ; break;
		case 15: os << "Part Of Speech = реплика\n"                         ; break;
		case 16: os << "Part Of Speech = частица\n"                         ; break;
		case 17: os << "Part Of Speech = краткое наречие\n"                 ; break;
		case 18: os << "Part Of Speech = причастие\n"                       ; break;
		case 19: os << "Part Of Speech = деепричастие\n"                    ; break;
		case 20: os << "Part Of Speech = краткое причастие\n"               ; break;
		case 21: os << "Part Of Speech = инфитив глагола\n"                 ; break;
		default : os << "Part Of Speech = не известно\n"                    ; break;

	}
}

void WordDescription::printGrammems(std::ostream &os) {
	os << "Grammems:\n";
	for (std::vector<WordDescription::Grammem>::iterator jt = myGrammems.begin(); jt != myGrammems.end(); ++jt) {
		switch ((*jt)) {
			case 0 : os << "множественное число\n"      ; break;
			case 1 : os << "единственное число\n"       ; break;
			case 2 : os << "именительный падеж\n"       ; break;
			case 3 : os << "родительный падеж\n"        ; break;
			case 4 : os << "дательный падеж\n"          ; break;
			case 5 : os << "винительный падеж\n"        ; break;
			case 6 : os << "творительный падеж\n"       ; break;
			case 7 : os << "предложный падеж\n"         ; break;
			case 8 : os << "звательный падеж\n"         ; break;
			case 9 : os << "мужской род\n"              ; break;
			case 10: os << "женский род\n"              ; break;
			case 11: os << "средний род\n"              ; break;
			case 12: os << "смешанный род\n"            ; break;
			case 13: os << "краткая форма\n"            ; break;
			case 14: os << "настоящее время\n"          ; break;
			case 15: os << "будущее время\n"            ; break;
			case 16: os << "прошедшее время\n"          ; break;
			case 17: os << "первое лицо\n"              ; break;
			case 18: os << "второе лицо\n"              ; break;
			case 19: os << "третье лицо\n"              ; break;
			case 20: os << "повелительное наклонение\n" ; break;
			case 21: os << "одушевлённое\n"             ; break;
			case 22: os << "неодушевлённое\n"           ; break;
			case 23: os << "сравнительная степень\n"    ; break;
			case 24: os << "совершенный вид\n"          ; break;
			case 25: os << "несовершенный вид\n"        ; break;
			case 26: os << "непереходной глагол\n"      ; break;
			case 27: os << "переходной глагол\n"        ; break;
			case 28: os << "активный залог\n"           ; break;
			case 29: os << "пассивный залог\n"          ; break;
			case 30: os << "несклоняемый\n"             ; break;
			case 31: os << "только инфинитив\n"         ; break;
			case 32: os << "отчество\n"                 ; break;
			case 33: os << "топоним\n"                  ; break;
			case 34: os << "организация\n"              ; break;
			case 35: os << "качественное\n"             ; break;
			case 36: os << "не имеет числа\n"           ; break;
			case 37: os << "вопросительное\n"           ; break;
			case 38: os << "указательное\n"             ; break;
			case 39: os << "имя\n"                      ; break;
			case 40: os << "фамилия\n"                  ; break;
			case 41: os << "безличное\n"                ; break;
			case 42: os << "сленг\n"                    ; break;
			case 43: os << "опечатка\n"                 ; break;
			case 44: os << "разговорный\n"              ; break;
			case 45: os << "притяжательный\n"           ; break;
			case 46: os << "архаизм\n"                  ; break;
			case 47: os << "переносное значение\n"      ; break;
			case 48: os << "высокий стиль\n"            ; break;
			case 49: os << "профессия\n"                ; break;
			case 50: os << "превосходная степень\n"     ; break;
			case 51: os << "положительная степень\n"    ; break;
			default: break;
		}
	}
}
