#ifndef HTREE_H
#define HTREE_H

#include "huffmancode.h"
#include "huffmannode.h"
#include "header.h"
#include <vector>

class HuffmanTree {
	std::vector<HuffmanCode> Codes;
	std::vector<HuffmanNode> Tree;
public:
	int GetElementFrequency(int index);
	char GetElementChar(int index);
	HuffmanNode *GetElement(int index);
	void PrintCode(int index);
	char GetCharByCode(std::string code);
	HuffmanCode GetCodeByChar(char c);
	bool BuildTree();
	void DeleteTree(HuffmanNode *root);
	void TraverseTree(HuffmanNode *root, long buffer, size_t buffsize);
	bool CompressFile(const std::string fname, std::vector<char> content, Header header);
	bool DecompressFile(std::ifstream &file, std::vector<char> &result, long Length, char LastCharacter);
	void Add(HuffmanNode node);
	void AddCode(HuffmanCode code);
	int GetCount();
	int GetCodeCount();
	HuffmanNode *GetRoot();
};


#endif