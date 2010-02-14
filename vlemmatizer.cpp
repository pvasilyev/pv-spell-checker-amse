#include "vlemmatizer.h"
#include <stdio.h>
#include <iostream>
#include <fstream>

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

WordDescription::WordDescription(WordDescription::PartOfSpeech partOfSpeech, u_int64_t iGr) {
	myPartOfSpeech = partOfSpeech;
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

std::vector<WordDescription::Grammem> &WordDescription::getGrammems() {
	return myGrammems;
}

void WordDescription::printPartOfSpeech(std::ostream &out) {
	switch (myPartOfSpeech){
		case 0: out << "Part Of Speech = существительное\n"                  ; break;
		case 1: out << "Part Of Speech = прилагательное\n"                   ; break;
		case 2: out << "Part Of Speech = глагол\n"                           ; break;
		case 3: out << "Part Of Speech = местоимение\n"                      ; break;
		case 4: out << "Part Of Speech = местоименное прилагательное\n"      ; break;
		case 5: out << "Part Of Speech = местоимение-предикатив\n"           ; break; // НЕЧЕГО слезы лить.
		case 6: out << "Part Of Speech = числительное\n"                     ; break;
		case 7: out << "Part Of Speech = порядковое числительное\n"          ; break;
		case 8: out << "Part Of Speech = наречие\n"                          ; break;
		case 9: out << "Part Of Speech = категория состояния (предикатив)\n" ; break; // "мне каково?": стыдно, холодно, просто
		case 10: out << "Part Of Speech = предлог\n"                         ; break;
		case 11: out << "Part Of Speech = posl\n"                            ; break;
		case 12: out << "Part Of Speech = союз\n"                            ; break;
		case 13: out << "Part Of Speech = междометие\n"                      ; break;
		case 14: out << "Part Of Speech = вводное слово\n"                   ; break;
		case 15: out << "Part Of Speech = реплика\n"                         ; break;
		case 16: out << "Part Of Speech = частица\n"                         ; break;
		case 17: out << "Part Of Speech = краткое наречие\n"                 ; break;
		case 18: out << "Part Of Speech = причастие\n"                       ; break;
		case 19: out << "Part Of Speech = деепричастие\n"                    ; break;
		case 20: out << "Part Of Speech = краткое причастие\n"               ; break;
		case 21: out << "Part Of Speech = инфитив глагола\n"                 ; break;
		default : out << "Part Of Speech = не известно\n"                    ; break;

	}
}

void WordDescription::printGrammems(std::ostream &out) {
	out << "Grammems:\n";
	for (std::vector<WordDescription::Grammem>::iterator jt = myGrammems.begin(); jt != myGrammems.end(); ++jt) {
		switch ((*jt)) {
			case 0 : out << "множественное число\n"      ; break;
			case 1 : out << "единственное число\n"       ; break;
			case 2 : out << "именительный падеж\n"       ; break;
			case 3 : out << "родительный падеж\n"        ; break;
			case 4 : out << "дательный падеж\n"          ; break;
			case 5 : out << "винительный падеж\n"        ; break;
			case 6 : out << "творительный падеж\n"       ; break;
			case 7 : out << "предложный падеж\n"         ; break;
			case 8 : out << "звательный падеж\n"         ; break;
			case 9 : out << "мужской род\n"              ; break;
			case 10: out << "женский род\n"              ; break;
			case 11: out << "средний род\n"              ; break;
			case 12: out << "смешанный род\n"            ; break;
			case 13: out << "краткая форма\n"            ; break;
			case 14: out << "настоящее время\n"          ; break;
			case 15: out << "будущее время\n"            ; break;
			case 16: out << "прошедшее время\n"          ; break;
			case 17: out << "первое лицо\n"              ; break;
			case 18: out << "второе лицо\n"              ; break;
			case 19: out << "третье лицо\n"              ; break;
			case 20: out << "повелительное наклонение\n" ; break;
			case 21: out << "одушевлённое\n"             ; break;
			case 22: out << "неодушевлённое\n"           ; break;
			case 23: out << "сравнительная степень\n"    ; break;
			case 24: out << "совершенный вид\n"          ; break;
			case 25: out << "несовершенный вид\n"        ; break;
			case 26: out << "непереходной глагол\n"      ; break;
			case 27: out << "переходной глагол\n"        ; break;
			case 28: out << "активный залог\n"           ; break;
			case 29: out << "пассивный залог\n"          ; break;
			case 30: out << "несклоняемый\n"             ; break;
			case 31: out << "только инфинитив\n"         ; break;
			case 32: out << "отчество\n"                 ; break;
			case 33: out << "топоним\n"                  ; break;
			case 34: out << "организация\n"              ; break;
			case 35: out << "качественное\n"             ; break;
			case 36: out << "не имеет числа\n"           ; break;
			case 37: out << "вопросительное\n"           ; break;
			case 38: out << "указательное\n"             ; break;
			case 39: out << "имя\n"                      ; break;
			case 40: out << "фамилия\n"                  ; break;
			case 41: out << "безличное\n"                ; break;
			case 42: out << "сленг\n"                    ; break;
			case 43: out << "опечатка\n"                 ; break;
			case 44: out << "разговорный\n"              ; break;
			case 45: out << "притяжательный\n"           ; break;
			case 46: out << "архаизм\n"                  ; break;
			case 47: out << "переносное значение\n"      ; break;
			case 48: out << "высокий стиль\n"            ; break;
			case 49: out << "профессия\n"                ; break;
			case 50: out << "превосходная степень\n"     ; break;
			case 51: out << "положительная степень\n"    ; break;
			default: break;
		}
	}
}
