CXX=gcc -Wall -std=c99

equake: equake.o equakeFunctions.o
	$(CXX) -g equake.o equakeFunctions.o -lm -o equake

equakeFunctions.o: equakeFunctions.c equake.h
	$(CXX) -c equakeFunctions.c 
	
clean:
	rm -f *.o equake equake

