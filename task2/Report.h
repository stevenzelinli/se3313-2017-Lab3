#ifndef REPORT_H
#define REPORT_H
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <thread>
#include <string>
#include <sstream>
#include "SharedObject.h"
#include "Semaphore.h"
#include <string>

/**
 * Reporter handles writing reports to the txt file and reading lines from the txt file.
 * It uses the C object type FILE for use with file io commands (e.g fputs() & fopen()).
 **/
class Report{
public:
	int intThread;
	int intReport;
	int intSecond;
};

#endif