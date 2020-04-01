#ifndef DEFCONST_H
#define DEFCONST_H
// DECLARATIONS
constexpr auto STR_WELCOME = "Welcome!\n This is an implementation of a compression method using Huffman Algorithm.\nProject is designed for the homework assignment of Basics of Programming 2 lecture in BME, HUNGARY\nDeveloped by A. Ugur Soysal (neptun: CDQ7TE)\n";
constexpr auto STR_MAIN_DIALOG = "\nTell me what you want to do?";
constexpr auto STR_MAIN_CHOICE1 = "Compress a file";
constexpr auto STR_MAIN_CHOICE2 = "Extract a file";
constexpr auto STR_MAIN_CHOICE3 = "Exit";
constexpr auto MAX_FILENAME_LENGTH = 32;
constexpr auto MAX_FILE_LENGTH = 16000000;
constexpr auto MIN_FILE_LENGTH = 2;
class Program {
public:
	static bool WELCOME_MESSAGE;
};
#endif
