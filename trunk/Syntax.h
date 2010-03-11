#ifndef _SYNTAX_H_
#define _SYNTAX_H_

#include <string>
#include <vector>

class ComplexSentence;
class GrammarFrame;
class GrammarUnits;
class SimpleSentence;
class WordDescription;

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

	std::vector<SourceSentenceUnit> *mySSUnits;	// исходные "сырые" данные

	ComplexSentence *myComplexSentence;

	bool isWord(std::string &string) const;
	bool isPredicateInCoordination(std::vector<std::vector<WordDescription> > &predicate) ;

public:
	explicit Syntax(std::string &sentence);
	~Syntax();

	void parse();
	void print(std::ostream &os, std::string &sent);

};


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

#endif //_SYNTAX_H_
