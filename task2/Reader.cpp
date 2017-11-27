#include <unistd.h>
#include <iostream>
#include <string>
#include <fstream>
#include "SharedObject.h"
#include "Semaphore.h"
#include "Reporter.h"

int main(void)
{
	std::cout << "I am a reader\n";
	// SEMAPHORE
	Semaphore sem_Reading("reading");
	// get shared object
	Shared<Reporter> reporter("reporter", false);
	// referencing
	while(true){
		// CRITICAL START
		sem_Reading.Wait();
		fflush(reporter->writeFile);
		std::string strMessage = reporter->readLine();
		std::cout << strMessage;
		// CRITICAL END
	}
}
