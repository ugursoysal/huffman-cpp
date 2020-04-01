#ifndef HCODE_H
#define HCODE_H

class HuffmanCode {
	char Character;
	long Code; // calculated huffman code
	size_t Size; // length of the code
public:
	HuffmanCode() : Character('*'), Code(0), Size(0) { }
	HuffmanCode(char ch, long code, size_t size) : Character(ch), Code(code), Size(size) { }
	char GetCharacter();
	long GetCode();
	size_t GetSize();
};

#endif