default: clean program

clean:
	rm -f *.o program

vlemmatizer.o: vlemmatizer.cpp vlemmatizer.h
	g++ -c vlemmatizer.cpp -Wall

main.o: main.cpp
	g++ -c main.cpp -Wall

program: vlemmatizer.o main.o
	g++ main.o vlemmatizer.o -lturglem -lMAFSA -lturglem-russian -o program -Wall
