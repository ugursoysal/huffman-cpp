#ifndef HHEAD_H
#define HHEAD_H
#include "freq.h"
#include <string>
#include <vector>

typedef std::pair<char, int> header_pair;
class Header
{
	char LastChar;
	long CharCount;
	long Length; // length of the original file
	std::vector<header_pair> Frequencies; // list of frequencies of characters
	std::string Filename;
public:
	Header(std::ifstream &f);
	Header(long CharCount, long Length, std::string original_filename, std::vector<Freq> &FreqArr, char LastCharacter);
	bool Write(std::ofstream &f);
	bool Read(std::ifstream &f);
	long GetLength();
	char GetLastCharacter();
	std::string GetOriginalFilename();
	std::vector<Freq> GetFreqArr();
	friend std::ostream &operator<<(std::ostream &os, Header const &m); // printing header in format
};
#endif // 