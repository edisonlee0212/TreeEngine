#include "Debug.h"


std::vector<std::string*> Debug::mErrorMessages;
std::vector<std::string*> Debug::mLogMessages;


void Debug::Log(std::string msg) {
	//std::cout << msg << std::endl;
	//mLogMessages.push_back(new std::string(msg + "\n"));
}

void Debug::Error(std::string msg) {
	//std::cout << msg << std::endl;
	//mErrorMessages.push_back(new std::string(msg + "\n"));
}