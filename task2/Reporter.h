#ifndef REPORTER_H
#define REPORTER_H
#include <iostream>
//#include <unistd.h>
#include <stdio.h>
#include <string>

/**
 * Reporter handles writing reports to the txt file and reading lines from the txt file.
 * It uses the C object type FILE for use with file io commands (e.g fputs() & fopen()).
 **/
class Reporter{
public:
	FILE * writeFile;
	
	void initialize(const std::string strFilePath){
		writeFile = fopen(strFilePath.c_str(), "w+");
		if(writeFile == NULL) 
		{
			std::cout << "Unable to open file\n Check path ...\n";
			return;
		}
	}

	void writeReport(const std::string strReport){
		fputs(strReport.c_str(), writeFile);
	}

	~Reporter(){
		fputs("#Shared Object Destroyed#", writeFile);
	}

	char * readLine(){
		char read[101];
		fgets(read, 100, writeFile);
		return read;
	}
};

#endif