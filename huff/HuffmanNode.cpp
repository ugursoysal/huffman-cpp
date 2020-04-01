#include <stddef.h> // NULL pointer 
#include "../include/huffmannode.h"

HuffmanNode::HuffmanNode() : Data('*'), Frequency(0), left(NULL), right(NULL) { }
HuffmanNode::HuffmanNode(char ch, int frequency, HuffmanNode *l, HuffmanNode *r) : Data(ch), Frequency(frequency), left(l), right(r) { }

int HuffmanNode::GetFrequency() {
	return Frequency;
}
char HuffmanNode::GetCharacter() {
	return Data;
}
char HuffmanNode::GetLeftCharacter() {
	return left->Data;
}
char HuffmanNode::GetRightCharacter() {
	return right->Data;
}
HuffmanNode *HuffmanNode::GetLeft() {
	return left;
}
HuffmanNode *HuffmanNode::GetRight() {
	return right;
}