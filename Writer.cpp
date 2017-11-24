#include <iostream>
#include <thread>
#include <unistd.h>

using namespace std;

int main(void)
{
	// variable declaration
	char charChoice;
	cout << "I am a Writer" << endl;

	// looping the choice
	while (true)
	{
		charChoice = 'C';
		// invalid input
		while(toupper(charChoice) != 'Y' && toupper(charChoice) != 'N'){
			cout << "Would you like to create a writer thread? ";
			cin >> charChoice;
			// if user decides to spawn writer thread 
			if(toupper(charChoice) == 'Y'){
				// code to run writing thread
				// first get delay
				int intDelay = 1;
				cout << "What is the Delay time (sec) for the new thread? ";
				cin >> intDelay;
				unsigned int delay = intDelay * 1000000;
				thread writingThread();
			}
			// if not then exit
			else if(toupper(charChoice) == 'N'){
				string temp;
				cout << "Now exiting ...\n";
				return 0;
			}
		}
	}
}
