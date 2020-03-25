#ifndef DEBUG_H
#define DEBUG_H
#include <iostream>
#include <vector>
class Debug
{
public:
	Debug() {

	}
	~Debug() {

	}
	static void Log(std::string msg) {
		std::cout << msg << std::endl;
		mLogMessages.push_back(msg + "\n");
	}
	static void Error(std::string msg) {
		std::cout << msg << std::endl;
		mErrorMessages.push_back(msg + "\n");
	}

	static std::vector<std::string> mLogMessages;
	static std::vector<std::string> mErrorMessages;
};

std::vector<std::string> Debug::mErrorMessages;
std::vector<std::string> Debug::mLogMessages;
#endif DEBUG_H
