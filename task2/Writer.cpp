#include <iostream>
#include <fstream>
#include <unistd.h>
#include <thread>

static int intThreads = 0;
/**
 * Writes to a file continuously using the format [thread number, 
 * number of times written to file, seconds passed since start of thread].
 * Takes parameters:
 * 	-ofstream fileStream: used for file output to txt file containing entries
 * 	-int intDelay: used to figure out the sleep time (in seconds) between each write to file
 **/
void writeToFile(std::ofstream &fileStream, int intDelay)
{
	int intReport = 0, intSeconds = 0;
	while (true)
	{
		fileStream << "[ " << intThreads << ", " << intReport << ", " << intSeconds << "]\n";
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

	// fstream setup
	std::ofstream txtStream;
	txtStream.open("writing.txt", std::ofstream::out | std::ofstream::trunc); // trunc erases all contents of the file
	txtStream << "# Writing Stream Creation #\n\n";

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
				std::thread writingThread(writeToFile, std::ref(txtStream), intDelay);
				writingThread.detach();
				// increment threads upon successful call
				intThreads++;
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
