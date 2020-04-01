#ifndef DIALOGS_H
#define DIALOGS_H
#include <iostream>
#include <string>
#include <functional>

class Option {
public:
	int Option_Id;
	std::string Description;
	std::function<bool(void)> CallBack;
	Option(const int option, const std::string description, std::function<bool(void)> callback);
};
class Dialog {
public:
	Dialog(const char* text, Option one, Option two, Option three);
};

#endif
