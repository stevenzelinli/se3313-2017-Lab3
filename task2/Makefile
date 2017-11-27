all : Writer Reader

Writer: Writer.o thread.o Blockable.o
	g++ -g -o Writer Writer.o thread.o Blockable.o -pthread -l rt

Reader: Reader.o thread.o Blockable.o
	g++ -g -o Reader Reader.o -pthread -l rt
	
Writer.o : Writer.cpp thread.h Reporter.h Blockable.h SharedObject.h Semaphore.h
	g++ -g -c Writer.cpp -std=c++11

thread.o : thread.cpp thread.h Blockable.h
	g++ -g -c thread.cpp -std=c++11

Blockable.o : Blockable.cpp Blockable.h
	g++ -g -c Blockable.cpp -std=c++11
	
Reader.o : Reader.cpp Reporter.h SharedObject.h Semaphore.h
	g++ -g -c Reader.cpp -std=c++11 
