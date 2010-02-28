default: clean program

clean:
	rm -f *.o program

vlemmatizer.o: vlemmatizer.cpp vlemmatizer.h
	g++ -c vlemmatizer.cpp -Wall

syntax.o: syntax.cpp syntax.h
	g++ -c syntax.cpp -Wall

main.o: main.cpp
	g++ -c main.cpp -Wall

program: vlemmatizer.o main.o syntax.o
	g++ main.o vlemmatizer.o syntax.o -lturglem -lMAFSA -lturglem-russian -o program -Wall
