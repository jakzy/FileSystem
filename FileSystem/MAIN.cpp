#include"Dialog.h"

int main()
{
	FileSystem system;
	
	try {
		system.Fill_UserTable("Users.txt");
		std::cout << "User table was got from file" << std::endl;
	}
	catch (std::exception &ex) {
		std::cout << ex.what();
	}
	try {
		system.Fill_Structure("Structure.txt");
		std::cout << "Structure of the system was got from file" << std::endl;
	}
	catch (std::exception &ex) {
		std::cout << ex.what();
	}
	system.Set_CurCat(system.GetRoot());
	std::getchar();
	try {
		RunMenu(system, 0);
	}
	catch (std::exception &ex) {
		std::cout << ex.what();
	}
	return 0;
}