CXX=gcc -Wall -std=c99

gol: gol.o golFunctions.o
	$(CXX) -g gol.o golFunctions.o -o gol

gol.o: gol.c golFunctions.o
	$(CXX) -c -g gol.c

golFunctions.o: golFunctions.c gol.h
	$(CXX) -c golFunctions.c 
	
clean:
	rm -f *.o gol

