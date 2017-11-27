#include <iostream>
#include <fstream>
#include <unistd.h>
#include <thread>
#include <string>
#include <sstream>
#include "SharedObject.h"
#include "Semaphore.h"
#include "Reporter.h"

static int intThreads = 0; // keep track of number of running writing threads

/**
 * Writes to a file continuously using the format [thread number, 
 * number of times written to file, seconds passed since start of thread].
 * Takes parameters:
 * 	-int intDelay: used to figure out the sleep time (in seconds) between each write to file
 **/
void writeToFile(int intDelay = 2)
{
	int intReport = 0, intSeconds = 0, _intThreads = intThreads++; // increment threads upon successful call
	// SEMAPHORES
	Semaphore sem_Writing("writing");
	Semaphore sem_Reading("reading");
	// get shared object
	Shared<Reporter> reporter("reporter");
	while (true)
	{	
		// building message
		std::ostringstream oss;
		oss << "[ " << _intThreads << ", " << intReport << ", " << intSeconds << "]\n";
		// CRITICAL START
		sem_Writing.Wait();
		reporter->writeReport(oss.str());
		sem_Writing.Signal();
		sem_Reading.Signal();
		// CRITICAL END
		sleep(intDelay);
		intSeconds += intDelay;
		intReport++;
	}
}

int main(void)
{
	// variable declaration
	char charChoice;
	std::cout << "I am a Writer" << std::endl;
	// SEMAPHORE DECLARATION
	Semaphore sem_Writing("writing", 1, true);
	Semaphore sem_Reading("reading", 0, true);
	// will be using the FILE type instead of std::ofstream to create the shared data
	// encapsulated the FILE object in a class Reporter
	Shared<Reporter> reporter("reporter", true);
	reporter->initialize("writing.txt");
	// CRITICAL START
	sem_Writing.Wait(); // block 
	reporter->writeReport("#Shared Object Created & Initialized#\n"); // operator<< returns this, to output i need to again use the << operator
	sem_Writing.Signal(); // next write in queue
	sem_Reading.Signal(); // signal that the file has been updated
	// CRITICAL END
	// looping the choice
	while (true)
	{
		charChoice = 'C';
		// invalid input
		while (toupper(charChoice) != 'Y' && toupper(charChoice) != 'N')
		{
			std::cout << "Would you like to create a writer thread? ";
			std::cin >> charChoice;
			// if user decides to spawn writer thread
			if (toupper(charChoice) == 'Y')
			{
				// code to run writing thread
				// first get delay
				int intDelay = 1;
				std::cout << "What is the Delay time (sec) for the new thread? ";
				std::cin >> intDelay;
				std::thread writingThread(writeToFile, intDelay);
				writingThread.detach();
			}
			// if not then exit
			else if (toupper(charChoice) == 'N')
			{
				std::string temp;
				std::cout << "Deleting Threads\n";
				// delete threads
				std::cout << "Now exiting ...\n";
				return 0;
			}
		}
	}
}
