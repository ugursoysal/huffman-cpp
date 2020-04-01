#include "../include/pch.h"
#include "../include/file_handling.h"
#include "../include/quicksort.h"
#include "../include/freq.h"
#include "../include/header.h"
#include "../include/huffman.h"
#include <iostream>
#include <fstream>

std::vector<Freq> Huffman::FreqArr;

void Huffman::SortFreqArr() {
	quicksort(FreqArr, 0, GetCount() - 1);
}

void Huffman::AddFreq(char c) { // add frequency to the array
	FreqArr.push_back(Freq(c));
	FreqArr[GetCount() - 1].IncreaseFrequency();
}

bool Huffman::Exists(char c) { // if character exists in the current FreqArr (global)
	for (int i = 0; i < GetCount(); i++) {
		if (FreqArr[i].GetCharacter() == c) return true;
	}
	return false;
}

int Huffman::GetCount() {
	return FreqArr.size();
}

bool Huffman::IncreaseFrequency(char c) {
	for (int i = 0; i < GetCount(); i++) {
		if (FreqArr[i].GetCharacter() == c) {
			FreqArr[i].IncreaseFrequency();
			return true;
		}
	}
	return false;
}

bool Huffman::Compress() {
	system("CLS");
	std::cout << "\nYou need to copy the file to be compressed to the \"files\" folder in the same path with this program.\n" << '\n';
	std::cout << "Please enter the filename you want to compress with it's extension (max " << MAX_FILENAME_LENGTH << " characters, no white spaces): ";
	std::string filename;
	std::vector<char> content;
	std::cin.clear();
	std::cin.sync();
	if (!(std::cin >> filename)) return false;
	filename = "files/" + filename;
	while (!File::file_exists(filename)) {
		system("CLS");
		std::cout << "\n(!) ERROR: Couldn't find the file.\n" << '\n';
		std::cout << "Please enter the filename you want to compress with it's extension (max " << MAX_FILENAME_LENGTH << " characters, no white spaces): ";
		std::cin.clear();
		std::cin.sync();
		if (!(std::cin >> filename)) return false;
	}
	while (File::file_length(filename) > MAX_FILE_LENGTH || File::file_length(filename) < MIN_FILE_LENGTH) {
		system("CLS");
		std::cout << "\n(!) ERROR: Specified file doesn't meet the requirements. (min length: " << MIN_FILE_LENGTH << ", max length: " << MAX_FILE_LENGTH << ")\n" << '\n';
		std::cout << "Please enter the filename you want to compress with it's extension (max " << MAX_FILENAME_LENGTH << " characters, no white spaces): ";
		std::cin.clear();
		std::cin.sync();
		if (!(std::cin >> filename)) return false;
	}
	try {
		content = File::ReadText(filename);
	}
	catch (int ex) {
		if (ex == 20) {
			std::cout << "Read operation failed." << '\n';
		}
		return false;
	}
	if (content.size() < 2) {
		std::cout << "File is too small to be compressed." << '\n';
		return false;
	}
	// we need to save last character of content to check if it's there because terminating character '\0' confuses the tree
	char last = content[content.size() - 1];
	// get frequencies
	char c;
	for (std::vector<char>::const_iterator i = content.begin(); i != content.end(); ++i) {
		c = *i;
		if (!Exists(c)) AddFreq(c);
		else IncreaseFrequency(c);
	}
	// sort frequency array
	SortFreqArr();
	// create header object
	Header header(GetCount(), content.size(), filename, FreqArr, last);
	// create tree and add frequencies as nodes to the tree
	HuffmanTree tree;
	for (int i = 0; i < GetCount(); i++) {
		tree.Add(HuffmanNode(FreqArr[i].GetCharacter(), FreqArr[i].GetFrequency(), NULL, NULL));
	}
	// build the tree
	tree.BuildTree();
	// calculate codes
	tree.TraverseTree(tree.GetRoot(), 0, -1); 
	//print codes (by index)
	/*
	for (int i = 0; i < tree.GetCodeCount(); i++) {
		tree.PrintCode(i);
	}
	*/
	// try to compress
	try {
		if (tree.CompressFile(filename + ".zip", content, header) != true) {
			std::cout << "Couldn't process." << '\n';
		}
	}
	catch (int ex) 
	{
		switch (ex) {
		case 20:
			std::cout << "Write operation failed." << '\n';
		case 30:
			std::cout << "Tree doesn't contain one of the characters in the content. (may be newline character)" << '\n';
		}
		return false;
	}
	// end of the process
	tree.DeleteTree(tree.GetRoot()); // delete all leaf nodes
	FreqArr.clear();
	FreqArr = std::vector<Freq>(); // this will de-allocate memory
	// de-allocation of the root node will be handled by the standard class after everything is complete (when HuffmanTree is deleted)
	// since 'tree' is a local variable, it should be deleted after the execution of this function
	if (Program::WELCOME_MESSAGE)
		system("CLS");
	Program::WELCOME_MESSAGE = true;
	std::cout << "File compression succesful: " << filename << " -- > " << filename + ".zip" << '\n';
	return true;
}
bool Huffman::Extract() {
	system("CLS");
	std::cout << "\nYou need to copy the file to be decompressed to the \"files\" folder in the same path with this program.\n" << '\n';
	std::cout << "Please enter the filename you want to decompress with it's extension (max " << MAX_FILENAME_LENGTH << " characters, no white spaces): ";
	std::string filename;
	std::vector<char> content;
	std::cin.clear();
	std::cin.sync();
	if (!(std::cin >> filename)) return false;
	filename = "files/" + filename;
	while (!File::file_exists(filename)) {
		system("CLS");
		std::cout << "\n(!) ERROR: Couldn't find the file.\n" << '\n';
		std::cout << "Please enter the filename you want to compress with it's extension (max " << MAX_FILENAME_LENGTH << " characters, no white spaces): ";
		std::cin.clear();
		std::cin.sync();
		if (!(std::cin >> filename)) return false;
	}
	while (File::file_length(filename) > MAX_FILE_LENGTH || File::file_length(filename) < MIN_FILE_LENGTH) {
		system("CLS");
		std::cout << "\n(!) ERROR: Specified file doesn't meet the requirements. (min length: " << MIN_FILE_LENGTH << ", max length: " << MAX_FILE_LENGTH << ")\n" << '\n';
		std::cout << "Please enter the filename you want to compress with it's extension (max " << MAX_FILENAME_LENGTH << " characters, no white spaces): ";
		std::cin.clear();
		std::cin.sync();
		if (!(std::cin >> filename)) return false;
	}
	std::vector<char> res;
	//get header
	std::ifstream a(filename, std::ios::binary | std::ios::in);
	Header ne(a);
	 std::cout << ne;
	// get frequencies
	FreqArr = ne.GetFreqArr();
	// create tree and add frequencies to the tree as nodes
	HuffmanTree dectree;
	for (int i = 0; i < GetCount(); i++) {
		dectree.Add(HuffmanNode(FreqArr[i].GetCharacter(), FreqArr[i].GetFrequency(), NULL, NULL));
		//std::cout << FreqArr[i].GetCharacter() << " - " << FreqArr[i].GetFrequency() << '\n';
	}
	// build the tree
	dectree.BuildTree();
	// calculate codes
	dectree.TraverseTree(dectree.GetRoot(), 0, -1);
	if (dectree.DecompressFile(a, res, ne.GetLength(), ne.GetLastCharacter()) == false) {
		std::cout << "Couldn't process." << '\n';
	}
	dectree.DeleteTree(dectree.GetRoot()); // delete all leaf nodes
	FreqArr.clear();
	FreqArr = std::vector<Freq>(); // this will de-allocate memory
	std::cin.clear();
	std::cin.sync();
	/*std::cout << "--- > content: --- >" << '\n';
	std::cout << res << '\n';*/
	a.close();
	try {
		std::ofstream c(ne.GetOriginalFilename(), std::ios::binary);
		if (!c)
			throw 20; 
		for (std::vector<char>::const_iterator i = res.begin(); i != res.end(); ++i) {
			c << *i;
		}
		//c << '\0';
		c.flush();
		c.close();
	}
	catch (int ex)
	{
		if(ex == 20)
			std::cout << "Couldn't write the content to the new file: " << ne.GetOriginalFilename() << '\n';
		return false;
	}
	catch (...) {
		std::cout << "Couldn't process the write operation." << '\n';
		return false;
	}
	if (Program::WELCOME_MESSAGE)
		system("CLS");
	Program::WELCOME_MESSAGE = true;
	std::cout << "File extraction succesful: " << filename << " -- > " << ne.GetOriginalFilename() << '\n';
	return true;
}
bool Huffman::Exit() {
	std::cout << "Goodbye! (viszontlátásra!)";
	exit(0);
	return true;
}