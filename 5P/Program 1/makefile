CXX=gcc -Wall -std=c99

bitTest: bitTest.o bitFunctions.o
	$(CXX) -g bitTest.o bitFunctions.o -o bitTest

bitTest.o: bitTest.c bitFunctions.h
	$(CXX) -c -g bitTest.c

bitFunctions.o: bitFunctions.c bitFunctions.h
	$(CXX) -c bitFunctions.c 	
myipTest: myipTest.o ipAddress.o
	$(CXX) -g myipTest.o ipAddress.o -lm -o myipTest

myipTest.o: myipTest.c ipAddress.h
	$(CXX) -c -g myipTest.c
ipAddress.o: ipAddress.c ipAddress.h
	$(CXX) -c ipAddress.c	

clean:
	rm -f *.o bitTest

