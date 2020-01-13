#ifndef DEBUG_H
#define DEBUG_H
#include <iostream>
class Debug
{
public:
	Debug() {

	}
	~Debug() {

	}
	static void LOG(const char* msg) {
		std::cout << msg << std::endl;
	}
private:

};

/* For debugging */
#if XDEBUG
#define xdebug(...) Debug::LOG(__VA_ARGS__)
#else
#define xdebug(...)
#endif

#endif DEBUG_H
