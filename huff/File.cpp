#include "../include/file_handling.h"
#include <fstream>

bool File::file_exists(const std::string& name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

long File::file_length(const std::string& name) {
	struct stat stat_buf;
	int rc = stat(name.c_str(), &stat_buf);
	return rc == 0 ? stat_buf.st_size : -1;
}

std::vector<char> File::ReadText(const std::string& name) {
	std::ifstream file(name, std::ios::binary);
	if (!file)
		throw 20;
	file.seekg(0, std::ios::end);  // seek to the end
	std::streampos size = file.tellg();  // get the position (file size)
	file.seekg(0, std::ios::beg);

	std::vector<char> buffer((size_t)size);
	size_t j = 0;
	while (j < size)
		buffer[j++] = file.get();
	file.close();
	return buffer;
}