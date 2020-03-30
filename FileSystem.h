#pragma once
#include "Misc.h"
class FileSystem {
public:
	static std::string GetPath(std::string path) {
		return "Resources/" + path;
	}

	static std::string LoadFileAsString(std::string path);
};