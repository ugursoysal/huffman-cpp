#include "../include/tree.h"
#include "../include/header.h"
#include <iostream>
#include <fstream>

int HuffmanTree::GetCount() {
	return Tree.size();
}
int HuffmanTree::GetCodeCount() {
	return Codes.size();
}

void HuffmanTree::PrintCode(int index) {
	size_t buffsize = Codes[index].GetSize();
	std::cout << "[" << index << "] : " << Codes[index].GetCharacter() << " - " << Codes[index].GetCode() << " - " << buffsize << " = ";
	long code = Codes[index].GetCode();
	for (size_t i = 0; i < buffsize; i++) {
		std::cout << code % 2;
		code = code >> 1;
	}
	std::cout << '\n';
}
void HuffmanTree::Add(HuffmanNode node) {
	Tree.push_back(node);
}
void HuffmanTree::AddCode(HuffmanCode code) {
	Codes.push_back(code);
}
char HuffmanTree::GetElementChar(int index) {
	return Tree[index].GetCharacter();
}
int HuffmanTree::GetElementFrequency(int index) {
	return Tree[index].GetFrequency();
}

HuffmanNode *HuffmanTree::GetElement(int index) {
	return &Tree[index];
};

char HuffmanTree::GetCharByCode(std::string code) {
	HuffmanNode *curr = &Tree[0];
	size_t c = 0;
	while (c != code.size() && curr->GetLeft() != NULL && curr->GetRight() != NULL) {
		if (code[c] == '0') {
			curr = curr->GetLeft();
		}
		else if (code[c] == '1') {
			curr = curr->GetRight();
		}
		c++;
	}
	return curr->GetCharacter();
};
HuffmanCode HuffmanTree::GetCodeByChar(char c) {
	for (size_t i = 0; i < Codes.size(); i++) {
		if (Codes[i].GetCharacter() == c) return Codes[i];
	}
	return HuffmanCode(NULL, 0, 0);
};
bool HuffmanTree::CompressFile(const std::string fname, std::vector<char> content, Header header) {
	std::ofstream c(fname, std::ios::binary | std::ios::out);
	if (!c)
		throw 20;
	char buffer = 0;
	int buff_size = 0;
	long code = 0;
	size_t codesize = 0;
	HuffmanCode huffmancode;
	size_t x = 0;
	 std::cout << header;
	header.Write(c);
	for (std::vector<char>::const_iterator i = content.begin(); i != content.end(); ++i) {
		huffmancode = GetCodeByChar(*i);
		if (huffmancode.GetCharacter() == NULL) throw 30;
		code = huffmancode.GetCode();
		codesize = huffmancode.GetSize();
		for (size_t j = 0; j < codesize; j++) {
			buff_size++;
			if ((code >> (codesize - j -1)) % 2) buffer += 1;
			if (buff_size == 8) {
				c << buffer;
				buffer = 0;
				buff_size = 0;
			} else
				buffer *= 2;
		}
	}
	c << '\0';
	c.flush();
	c.close();
	return true;
}

bool HuffmanTree::DecompressFile(std::ifstream &file, std::vector<char> &result, long Length, char last) {
	if (!file)
		throw 20;

	int buff_size = 0;
	char code = 0;
	char tmp = 0;
	size_t codesize = 0;
	HuffmanNode *node = GetRoot();
	while ((long) result.size() < Length - 1) { // length - 1 because we will end the content manually with the last character
		file.get(tmp);
		for (int j = 7; j > -1; j--) {
			code = tmp >> j;
			if (abs(code % 2) == 1) 
				node = node->GetRight();
			else 
				node = node->GetLeft();
			if (node->GetCharacter() != '*') {
				result.push_back(node->GetCharacter());
				node = GetRoot();
				code = 0;
			}
		}
	}
	if(result.back() != last) // check if the last inserted character is true
		result.push_back(last); // add if false, end the operation
	return true;
}
HuffmanNode *HuffmanTree::GetRoot() {
	return &Tree[0];
}
void HuffmanTree::DeleteTree(HuffmanNode *root) {
	if (root != NULL) {
		DeleteTree(root->GetLeft());
		DeleteTree(root->GetRight());
		if (root != GetRoot()) // root node is the first cell of a vector-type variable. deallocation operation will throw an exception on root node
			delete root;
	}
}
void HuffmanTree::TraverseTree(HuffmanNode *root, long buffer, size_t buffsize) {
	if (root != NULL) {
		buffsize += 1;
		TraverseTree(root->GetLeft(), (buffer * 2), buffsize);
		TraverseTree(root->GetRight(), (buffer * 2) + 1, buffsize);
		if (root->GetCharacter() != '*') {
			/*long reverse_bits = 0;
			for (size_t i = 0; i < buffsize; i++) {
				reverse_bits *= 2;
				reverse_bits += ((buffer >> i) % 2);
			}*/
			AddCode(HuffmanCode(root->GetCharacter(), buffer, buffsize));
		}
	}
}
bool HuffmanTree::BuildTree() {
	int count = GetCount();
	if (count < 1) return false;
	for (int i = 0; i < count-1; i++) {
		HuffmanNode *p1 = new HuffmanNode(Tree[0]); // copy of first cell in the vector
		HuffmanNode *p2 = new HuffmanNode(Tree[1]); // second
		HuffmanNode newnode = HuffmanNode('*', p1->GetFrequency() + p2->GetFrequency(), p1, p2);
		for (int j = 0; j < GetCount() - 1; j++) {
			if (j == GetCount() - 2 || Tree[j+2].GetFrequency() > newnode.GetFrequency()) {
				Tree[j] = newnode;
				if (j > GetCount() - 3) break;
				j++;
				Tree[j] = Tree[j+1];
				for (int k = j + 1; k < GetCount() - 1; k++) {
					Tree[k] = Tree[k + 1];
				}
				break;
			}
			else {
				Tree[j] = Tree[j + 2];
			}
		}
		Tree.erase(Tree.begin() + GetCount() - 1, Tree.end());
	}
	return true;
}