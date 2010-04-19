#ifndef _SYNTAX_ANALYZER_H_
#define _SYNTAX_ANALYZER_H_

#include <string>
#include <vector>
#include "VLemmatizer.h"

class ComplexSentence;
class GrammarFrame;
class WordDescription;

class SentenceUnit {

public:
	std::vector<WordDescription> myVectorWordDescription;
	std::string myText;
	bool myIsWord;

};

class SentencePart {

public:
	WordDescription myWordDescription;
	SentenceUnit mySentenceUnit;

};

class SyntaxAnalyzer {

public:
	explicit SyntaxAnalyzer(const std::string &sentence);
        ~SyntaxAnalyzer();

        void print(std::ostream &os);

private:
        bool isWord(const std::string &string) const;

private:
        std::vector<std::string> mySentenceUnits;
        std::vector<SentenceUnit> myVectorSentenceUnit;     // исходные "сырые" данные
        ComplexSentence *myComplexSentence;

};

#endif
