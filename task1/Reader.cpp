#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>

int main(void)
{
	std::cout << "I am a reader" << std::endl;
	// creating read stream
	std::ifstream readStream;
	readStream.open("writing.txt");
	while(true){
		if(readStream.eof()){
			sleep(5);
		}
		else{
			std::string strMessage;
			std::getline(readStream, strMessage);
			std::cout << strMessage<< std::endl;
		}
	}
}
