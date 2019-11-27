//#undef max
#include "Dialog.h"
#include <limits>

#undef max

using std::map;
using std::string;

void ShowMenu(size_t i)
{
	size_t sz =  MENU_SET[i].size();
	for (size_t k = 0; k != sz; ++k) {
		std::cout << MENU_SET[i][k]<<std::endl;
	}
}
void RunMenu(FileSystem cur, size_t i)
{
	int choise = 1;
	do {
		system("cls");
		ShowMenu(i);
		std::cout << ">>";
		std::cin >> choise;
		if (std::cin.eof()) {
			std::cout << "You ll return to main menu" << std::endl;
			choise = -1;
		}
		else
			if (choise < MENU_SET[i].size())
			{
				MENU_VECTOR[i][choise-1](cur);
				std::cout << "Press ENTER to continue";
				std::getchar();
			}
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	} while (choise > 0);
	if (i == 0) {
		cur.SaveSystem();
		throw std::exception("System saved, work finished");
	}
	else {
		RunMenu(cur, 0);
	}
}

//string menu_system[]

void SystemStat(FileSystem& cur)
{
	std::cout << cur.Info();
}
void WorkFile(FileSystem& cur)
{
	RunMenu(cur, file_);
}

void WorkCat(FileSystem& cur)
{
	RunMenu(cur, catalog_);
}
void EditUserTable(FileSystem& cur)
{
	RunMenu(cur, user_table_);
}
void ChangeCurUser(FileSystem& cur)
{
	ID id;
	std::cout << "Enter new user's ID: ";
	std::cin >> id;
	try {
		cur.ChangeCurUser(id);
	}
	catch (std::exception &ex) {
		throw ex;
	}
	std::cout << "New current user's ID: " << cur.GetCurUser() << std::endl;
}
void ChangeCurCat(FileSystem& cur)
{
	std::cout << "Enter adress of a new current catalog (start witn \"/\" to use absolute adress): ";
	string CatAdress;
	std::cin >> CatAdress;
	try {
		cur.GoTo(CatAdress);
		std::cout;///////////////////
	}
	catch (std::exception &ex) {
		throw ex;
	}

}
void SaveSystem(FileSystem& cur)
{

}

//string menu_user_table[]
void ShowUserTable(FileSystem& cur)
{
	std::cout << cur.ShowUserTable();
}
void AddUser(FileSystem& cur)
{
	string name;
	int key;
	std::cout << "Enter new user's name: ";
	std::cin >> name;
	std::cout << "Enter new user's key: ";
	std::cin >> key;
	cur.AddTo_UserTable(User(name, key));
}
void DeleteUser(FileSystem& cur)
{
	int id;
	std::cout << "Enter new user's ID: ";
	std::cin >> id;
	try {
		cur.DeleteFrom_UserTable(id);
	}
	catch (std::exception &ex) {
		throw ex;
	}
}
void EditUser(FileSystem& cur)
{
	int id, key;
	string name;
	std::cout << "Enter new user's ID: ";
	std::cin >> id;
	std::cout << "Enter new user's name: ";
	std::cin >> name;
	std::cout << "Enter new user's key: ";
	std::cin >> key;
	try {
		cur.Edit_UserTable(id, User(name, key));
	}
	catch (std::exception &ex) {
		throw ex;
	}
}

//string menu_catalog[]
void ShowCatalog(FileSystem& system)
{
	system.GetCurCat()->Show();
}
void RenameObject(FileSystem& system)
{
	string old_name, new_name;
	std::cout << "Enter current file name:";
	std::cin >> old_name;
	std::cout << "Enter new file name:";
	std::cin >> new_name;
	try {
		system.GetCurCat()->Rename(old_name, new_name, system.GetCurUser());
	}
	catch (std::exception& ex) {
		throw ex;
	}
}
void CopyObject(FileSystem& system)
{
	
}
void TransferObject(FileSystem& system)
{

}
void AddFromBuf(FileSystem& system)
{

}
void AddNewObject(FileSystem& system)
{

}
void ShowCatInfo(FileSystem& system)
{
	std::cout << system.GetCurCat()->Info();
}

//string menu_file[]
void OpenRead(FileSystem& cur)
{

}
void OpenWrite(FileSystem& cur)
{

}
void Run(FileSystem& cur)
{

}
void ShowInfo(FileSystem& cur)
{

}
void ShowCurAccess(FileSystem& cur)
{

}
void EditUserAccess(FileSystem& cur)
{

}
void ChangeType(FileSystem& cur)
{

}

//string menu_WOfile[]
void AddInfo(FileSystem& cur)
{

}
void ClearFile(FileSystem& cur)
{

}
void RewriteFile(FileSystem& cur)
{

}

//string menu_ROfile[]
void ShowFile(FileSystem& cur)
{

}

void CloseFile(FileSystem& cur)
{

}

//string menu_access[]
void AddAccess(FileSystem& cur)
{

}
void ChangeAccess(FileSystem& cur)
{

}
void ChangeGuestAccess(FileSystem& cur)
{

}
void DeleteAccess(FileSystem& cur)
{

}

//string menu_ENCaccess[]
void AddEncAccess(FileSystem& cur)
{

}
void DeleteEncAccess(FileSystem& cur)
{

}