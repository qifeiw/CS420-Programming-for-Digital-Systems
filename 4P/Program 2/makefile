CXX = gcc -Wall 

all: calSpan dataDump

calSpan.o: calSpan.c
	$(CXX) -c calSpan.c

calSpanMain: calSpan.o calSpanMain.c
	$(CXX) calSpan.o calSpanMain.c -o calSpanMain

dataDump.o: dataDump.c
	$(CXX) -c dataDump.c

dataDumpMain: dataDump.o dataDumpMain.c
	$(CXX) dataDump.o dataDumpMain.c -o dataDumpMain
clean:
	rm -f *.o dataDumpMain calSpanMain 
	
	