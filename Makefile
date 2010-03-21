default: program

clean:
	rm -f *.o program

VLemmatizer.o: VLemmatizer.cpp VLemmatizer.h
	g++ -c -Wall VLemmatizer.cpp

SyntaxAnalyzer.o: SyntaxAnalyzer.cpp SyntaxAnalyzer.h
	g++ -c -Wall SyntaxAnalyzer.cpp

GrammarFrame.o: GrammarFrame.cpp GrammarFrame.h
	g++ -c -Wall GrammarFrame.cpp

GrammarUnits.o: GrammarUnits.cpp GrammarUnits.h
	g++ -c -Wall GrammarUnits.cpp

SimpleSentence.o: SimpleSentence.cpp SimpleSentence.h
	g++ -c -Wall SimpleSentence.cpp

ComplexSentence.o: ComplexSentence.cpp ComplexSentence.h
	g++ -c -Wall ComplexSentence.cpp

SentenceManager.o: SentenceManager.cpp SentenceManager.h
	g++ -c -Wall SentenceManager.cpp

main.o: main.cpp SyntaxAnalyzer.h VLemmatizer.h
	g++ -c -Wall main.cpp

program: VLemmatizer.o SyntaxAnalyzer.o GrammarFrame.o GrammarUnits.o SimpleSentence.o ComplexSentence.o SentenceManager.o main.o
	g++ -Wall main.o VLemmatizer.o SyntaxAnalyzer.o GrammarFrame.o GrammarUnits.o SimpleSentence.o ComplexSentence.o SentenceManager.o -lturglem -lMAFSA -lturglem-russian -o program
