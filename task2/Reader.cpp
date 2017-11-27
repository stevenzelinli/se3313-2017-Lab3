#include <iostream>
#include <fstream>
#include <unistd.h>
#include <thread>
#include <string>
#include <sstream>
#include "SharedObject.h"
#include "Semaphore.h"
#include "Report.h"

int main(void)
{
	std::cout << "I am a reader\n";
	// SEMAPHORE
	Semaphore sem_Reading("reading");
	// get shared object
	Shared<Report> reporter("reporter");
	// FILE * readFile = fopen("writing.txt", "r");
	// referencing
	while(true){
		// CRITICAL START
		sem_Reading.Wait();
		std::cout << "[ " << reporter->intThread << ", " << reporter->intReport << ", " << reporter->intSecond << " ]\n";
		// CRITICAL END
	}
}
