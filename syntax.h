#include <string>
#include <vector>

#ifndef _SYNTAX_H_
#define _SYNTAX_H_

#include "complexsentence.h"
#include "vlemmatizer.h"

class ComplexSentence;
class SimpleSentence;

class SentencePartName {

public:
	enum SP {
		SUBJECT = 0,		//подлежащее
		PREDICATE = 1,		//сказуемое
		OBJECTIVECOMPONENT = 2,	//дополнение
		ADVERBIAL = 3,		//обстоятельство
		DEFINITION = 4,		//определение
		PARTICIPIAL = 5,	//деепричастный/причастный оборот
	};

	friend class Syntax;

};

class SourceSentenceUnit {

public:
	std::vector<WordDescription> myWD;
	std::string myText;
	bool isWord;

};

class Syntax {

private:
	std::vector<std::string> mySentenceUnit;
	std::vector<std::vector<WordDescription> > myWordDescription;
	std::vector<std::string> myObject;	// подлежащие
	std::vector<std::string> myPredicate;	// сказуемые

	std::vector<SourceSentenceUnit> *mySSUnits;	// исходные "сырые" данные

	ComplexSentence *myComplexSentence;

	bool isWord(std::string &string) const;
	bool isPredicateInCoordination(std::vector<std::vector<WordDescription> > &predicate) ;

public:
	explicit Syntax(std::string &sentence);

	void parse();
	void print(std::ostream &os, std::string &sent);

};

#endif //_SYNTAX_H_
