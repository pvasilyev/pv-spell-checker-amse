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
	std::vector<WordDescription> myVectorWordDescription;
	std::string myText;
	bool myIsWord;

};


class SyntaxAnalyzer {

public:
	explicit SyntaxAnalyzer(const std::string &sentence);
        ~SyntaxAnalyzer();

	void parse();
        void print(std::ostream &os);

private:
        std::vector<std::string> mySentenceUnit;
        std::vector<SourceSentenceUnit> myVectorSourceSentenceUnit;     // исходные "сырые" данные
        ComplexSentence *myComplexSentence;

private:
        bool isWord(const std::string &string) const;

};

#endif
