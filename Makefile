default: program

clean:
	rm -f *.o program

VLemmatizer.o: VLemmatizer.cpp VLemmatizer.h
	g++ -Wall -c VLemmatizer.cpp

SyntaxAnalyzer.o: SyntaxAnalyzer.cpp SyntaxAnalyzer.h ComplexSentence.h SimpleSentence.h VLemmatizer.h
	g++ -Wall -c SyntaxAnalyzer.cpp

GrammarFrame.o: GrammarFrame.cpp GrammarFrame.h SyntaxAnalyzer.h VLemmatizer.h Rules.h
	g++ -Wall -c GrammarFrame.cpp

Rules.o: Rules.cpp Rules.h
	g++ -Wall -c Rules.cpp

GrammarUnits.o: GrammarUnits.cpp GrammarUnits.h	
	g++ -Wall -c GrammarUnits.cpp

SimpleSentence.o: SimpleSentence.cpp SimpleSentence.h ComplexSentence.h GrammarFrame.h GrammarUnits.h SyntaxAnalyzer.h VLemmatizer.h
	g++ -Wall -c SimpleSentence.cpp

ComplexSentence.o: ComplexSentence.cpp ComplexSentence.h SentenceManager.h SimpleSentence.h SyntaxAnalyzer.h VLemmatizer.h
	g++ -Wall -c ComplexSentence.cpp

SentenceManager.o: SentenceManager.cpp SentenceManager.h
	g++ -Wall -c SentenceManager.cpp

main.o: main.cpp SyntaxAnalyzer.h VLemmatizer.h
	g++ -Wall -c main.cpp

program: VLemmatizer.o SyntaxAnalyzer.o GrammarFrame.o Rules.o GrammarUnits.o SimpleSentence.o ComplexSentence.o SentenceManager.o main.o
	g++ -Wall main.o VLemmatizer.o SyntaxAnalyzer.o GrammarFrame.o Rules.o GrammarUnits.o SimpleSentence.o ComplexSentence.o SentenceManager.o -lturglem -lMAFSA -lturglem-russian -o program
