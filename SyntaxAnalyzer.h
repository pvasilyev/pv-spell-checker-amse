#ifndef _SYNTAX_ANALYZER_H_
#define _SYNTAX_ANALYZER_H_

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


class SyntaxAnalyzer {

public:
        explicit SyntaxAnalyzer(std::string &sentence);
        ~SyntaxAnalyzer();

        void parse();
        void print(std::ostream &os, std::string &sent);

private:
        std::vector<std::string> mySentenceUnit;
        std::vector<std::vector<WordDescription> > myWordDescription;

        std::vector<SourceSentenceUnit> *mySSUnits;     // исходные "сырые" данные

        ComplexSentence *myComplexSentence;

private:
        bool isWord(std::string &string) const;
        bool isPredicateInCoordination(std::vector<std::vector<WordDescription> > &predicate) ;

};


class SentencePartName {

public:
        enum SP {
                SUBJECT = 0,            //подлежащее
                PREDICATE = 1,          //сказуемое
                OBJECTIVECOMPONENT = 2, //дополнение
                ADVERBIAL = 3,          //обстоятельство
                DEFINITION = 4,         //определение
                PARTICIPIAL = 5,        //деепричастный/причастный оборот
        };

        friend class Syntax;

};

#endif //_SYNTAX_ANALYZER_H_
