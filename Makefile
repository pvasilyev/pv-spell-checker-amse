default: program

clean:
	rm -f *.o program

VLemmatizer.o: VLemmatizer.cpp VLemmatizer.h
	g++ -c VLemmatizer.cpp -Wall

SyntaxAnalyzer.o: SyntaxAnalyzer.cpp SyntaxAnalyzer.h
	g++ -c SyntaxAnalyzer.cpp -Wall

GrammarFrame.o: GrammarFrame.cpp GrammarFrame.h
	g++ -c GrammarFrame.cpp -Wall

GrammarUnits.o: GrammarUnits.cpp GrammarUnits.h
	g++ -c GrammarUnits.cpp -Wall

SimpleSentence.o: SimpleSentence.cpp SimpleSentence.h
	g++ -c SimpleSentence.cpp -Wall

ComplexSentence.o: ComplexSentence.cpp ComplexSentence.h
	g++ -c ComplexSentence.cpp -Wall

SentenceManager.o: SentenceManager.cpp SentenceManager.h
	g++ -c SentenceManager.cpp -Wall

main.o: main.cpp
	g++ -c main.cpp -Wall

program: VLemmatizer.o SyntaxAnalyzer.o GrammarFrame.o GrammarUnits.o SimpleSentence.o ComplexSentence.o SentenceManager.o main.o
	g++ main.o VLemmatizer.o SyntaxAnalyzer.o GrammarFrame.o GrammarUnits.o SimpleSentence.o ComplexSentence.o SentenceManager.o -lturglem -lMAFSA -lturglem-russian -o program -Wall
