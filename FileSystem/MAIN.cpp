#include"Dialog.h"

#undef max
using std::map;
using std::vector;
using std::pair;
using std::string;

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
	std::getchar();
	try {
		RunMenu(system, 0);
	}
	catch (std::exception &ex) {
		std::cout << ex.what();
	}
	system.Save_UserTable("Users.txt");
	/*
	UserAccess guests = { false, false, false };
	UserAccess superUser = { true, true, true };
	vector<pair<ID, UserAccess>> acc;
	acc.push_back(pair<ID, UserAccess>(0, superUser));
	vector<Stream>* str = new vector<Stream>;
	str->push_back( Stream(system.GetSize()) );
	File newFile(0, acc, guests, str,0, "A random file", system.GetCurCat());
	Object* ptr = dynamic_cast<Object*>(&newFile);
	system.GetCurCat()->Write(system.GetCurUser(), ptr);
	std::cout << system.GetCurCat()->Show();
	std::cout << system.GetCurCat()->Info();*/
	return 0;
}