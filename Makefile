default: clean program

clean:
	rm -f *.o program

vlemmatizer.o: vlemmatizer.cpp vlemmatizer.h
	g++ -c vlemmatizer.cpp -Wall

syntax.o: syntax.cpp syntax.h
	g++ -c syntax.cpp -Wall

grammarframe.o: grammarframe.cpp grammarframe.h
	g++ -c grammarframe.cpp -Wall

grammarunits.o: grammarunits.cpp grammarunits.h
	g++ -c grammarunits.cpp -Wall

simplesentence.o: simplesentence.cpp simplesentence.h
	g++ -c simplesentence.cpp -Wall

complexsentence.o: complexsentence.cpp complexsentence.h
	g++ -c complexsentence.cpp -Wall

sentencemanager.o: sentencemanager.cpp sentencemanager.h
	g++ -c sentencemanager.cpp -Wall

main.o: main.cpp
	g++ -c main.cpp -Wall

program: vlemmatizer.o syntax.o grammarframe.o grammarunits.o simplesentence.o complexsentence.o sentencemanager.o main.o
	g++ main.o vlemmatizer.o syntax.o grammarframe.o grammarunits.o simplesentence.o complexsentence.o sentencemanager.o -lturglem -lMAFSA -lturglem-russian -o program -Wall
