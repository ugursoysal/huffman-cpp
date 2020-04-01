#include "../include/dialogs.h"

Option::Option(const int option, std::string description, std::function<bool(void)> callback) : Option_Id(option), Description(description), CallBack(callback) { }

Dialog::Dialog(const char* text, Option one, Option two, Option three)
{
	std::cout << text << '\n';
	std::cout << "1. " << one.Description << '\n';
	std::cout << "2. " << two.Description << '\n';
	if (three.CallBack != NULL) std::cout << "3. " << three.Description << '\n';
	char c = NULL;
	do
	{
		std::cin >> c;
		if (((int)c) - 48 == one.Option_Id) {
			one.CallBack();
		}
		else if (((int)c) - 48 == two.Option_Id) {
			two.CallBack();
		}
		else if (three.CallBack != NULL && ((int)c) - 48 == three.Option_Id) {
			three.CallBack();
		}
	} while (((int)c) - 48 != one.Option_Id && ((int)c) - 48 != two.Option_Id && ((int)c) - 48 != three.Option_Id);
}