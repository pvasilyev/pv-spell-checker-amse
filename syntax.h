#ifndef _SYNTAX_H_
#define _SYNTAX_H_

#include <vector>
#include <string>
#include "vlemmatizer.h"

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



class Syntax {

private:
	std::vector<std::string> mySentenceUnit;
	std::vector<std::vector<WordDescription> > myWordDescription;
	std::vector<std::string> myObject;
	std::vector<std::string> myPredicate;

	bool isWord(std::string &string) const;
	bool isPredicateInCoordination(std::vector<std::vector<WordDescription> > &predicate) ;

public:
	explicit Syntax(std::string &sentence);

	void parse();
	void print(std::ostream &os, std::string &sent);

};

#endif //_SYNTAX_H_
