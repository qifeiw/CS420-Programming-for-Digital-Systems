CXX=gcc -Wall -std=c99

myipTest: myipTest.o ipAddress.o
	$(CXX) -g myipTest.o ipAddress.o -lm -o myipTest

myipTest.o: myipTest.c ipAddress.h
	$(CXX) -c -g myipTest.c
ipAddress.o: ipAddress.c ipAddress.h
	$(CXX) -c ipAddress.c	

clean:
	rm -f *.o myipTest

