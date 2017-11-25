#include <iostream>
#include <fstream>
#include <unistd.h>
#include <thread>
#include <string>
#include <sstream>
#include "SharedObject.h"

static int intThreads = 0;
/**
 * Writes to a file continuously using the format [thread number, 
 * number of times written to file, seconds passed since start of thread].
 * Takes parameters:
 * 	-int intDelay: used to figure out the sleep time (in seconds) between each write to file
 **/
void writeToFile(int intDelay = 2)
{
	int intReport = 0, intSeconds = 0, _intThreads = intThreads++; // increment threads upon successful call
	Shared<FILE> txtStream("inputFile", false);
	FILE * _txtStream = txtStream.get();
	_txtStream = fopen("writing.txt", "a"); // a sets the mode to append
	std::ostringstream oss;
	while (true)
	{
		
		// building message
		oss << "[ " << _intThreads << ", " << intReport << ", " << intSeconds << "]\n";
		// CRITICAL START
		fputs(oss.str().c_str(), _txtStream);
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
	// will be using the FILE type instead of std::ofstream to create the shared data
	Shared<FILE> txtStream("inputFile", true);
	FILE * _txtStream = txtStream.get();
	_txtStream = fopen("writing.txt", "w"); // w erases all contents of the file for writing
	// CRITICAL START
	fputs("# Writing Stream Creation #\n", _txtStream); // operator<< returns this, to output i need to again use the << operator
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
