#pragma once
#include <iostream>
#include <string>
#include <vector>
class Debug
{
public:
	static void Log(std::string msg);
	static void Error(std::string msg);

	static std::vector<std::string*> mLogMessages;
	static std::vector<std::string*> mErrorMessages;
};
