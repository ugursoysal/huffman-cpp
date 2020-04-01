#ifndef HNODE_H
#define HNODE_H

class HuffmanNode {
	char Data;
	int Frequency;
	HuffmanNode *left;
	HuffmanNode *right;
public:
	HuffmanNode();
	HuffmanNode(char ch, int frequency, HuffmanNode *l, HuffmanNode *r);
	int GetFrequency();
	char GetCharacter();
	char GetLeftCharacter();
	char GetRightCharacter();
	HuffmanNode *GetLeft();
	HuffmanNode *GetRight();
};

#endif