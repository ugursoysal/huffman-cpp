#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H
#include "pch.h"
#include <vector>
#include <string>

// basic file handling
class File {
public:
	// global functions
	static std::vector<char> ReadText(const std::string& name);
	static bool file_exists(const std::string& name);
	static long file_length(const std::string& name);
};
#endif
