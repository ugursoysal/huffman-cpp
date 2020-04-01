#include "../include/pch.h"
#include "../include/dialogs.h"
#include "../include/huffman.h"
#include <iostream>

int main()
{
	while (1) {
		if(!Program::WELCOME_MESSAGE)
			std::cout << STR_WELCOME;
		Option options[3] =
		{
			Option(1, STR_MAIN_CHOICE1, &Huffman::Compress),
			Option(2, STR_MAIN_CHOICE2, &Huffman::Extract),
			Option(3, STR_MAIN_CHOICE3, &Huffman::Exit)
		};
		Dialog Ok(STR_MAIN_DIALOG, options[0], options[1], options[2]);
	}
	return 0;
}
