#ifndef FILESYSTEM_H
#define FILESYSTEM_H

class FileSystem {
public:
	static std::string GetPath(std::string path) {
		return "src/" + path;
	}
};

#endif FILESYSTEM_H
