#pragma once
#include "Misc.h"
class FileSystem {
public:
	static std::string GetPath(std::string path) {
		return "src/" + path;
	}
};