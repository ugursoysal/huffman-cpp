#ifndef HUFF_H
#define HUFF_H

#include "freq.h"
#include "tree.h"
#include <vector>

class Huffman {
private:
	static std::vector<Freq> FreqArr;
public:
	static void AddFreq(char c);
	static bool Exists(char c);
	static bool IncreaseFrequency(char c);
	static bool Compress();
	static bool Extract();
	static bool Exit();
	static int GetCount();
	static void SortFreqArr();
};
#endif