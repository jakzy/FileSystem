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
void RunMenu(FileSystem &cur, size_t i)
{
	
	int choise = 1;
	do {
		system("cls");
		std::cout << "Current user:\t" << cur.GetCurUser() << std::endl;
		std::cout << "Current catalog:\t" << cur.GetCurCat()->GetFileDescriptor().first << std::endl;
		std::cout << cur.GetCurCat()->Show();
		std::cout << "Buf:\t";
		cur.GetBuf() == nullptr?(std::cout<<"empty" << std::endl):
			(std::cout << ObjectName[cur.GetBuf()->GetFileDescriptor().second->iAm()] << "\t" << cur.GetBuf()->GetFileDescriptor().first << std::endl);
		std::cout << "******************************************" << std::endl;
		ShowMenu(i);
		std::cout << ">>";
		std::cin >> choise;
		if (std::cin.eof()) {
			switch (i) {
			case 0:
				break;
			case 4:
				std::cout << "You ll return to FILE menu" << std::endl;
				break;
			case 5:
				std::cout << "You ll return to FILE menu" << std::endl;
				break;
			case 6:
				std::cout << "You ll return to FILE menu" << std::endl;
				break;
			default:
				std::cout << "You ll return to main menu" << std::endl;
				break;
			}
			choise = -1;
		}
		else
			if ((choise < MENU_SET[i].size()) && (choise > 0))
			{
				MENU_VECTOR[i][choise-1](cur);
				//std::cout << "Press ENTER to continue";
				//std::getchar();
			}
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	} while (choise > 0);
	if (i == system_) {
		cur.SaveSystem();
		throw std::exception("Work finished");
	}
	else {
		switch (i) {
		case WOfile_:
			RunMenu(cur, file_);
			break;
		case ROfile_:
			RunMenu(cur, file_);
			break;
		case access_:
			RunMenu(cur, file_);
			break;
		default:
			RunMenu(cur, system_);
			break;
		}
	}
}

//string menu_system[]

void SystemStat(FileSystem& cur)
{
	std::cout << cur.Info();
	std::getchar();
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
	std::cout << cur.GetUserTable().find(id)->second.GetName() << ", welcome!"<<std::endl;
	std::cout << "New current user's ID: " << cur.GetCurUser() << std::endl;
	std::getchar();
}
void ChangeCurCat(FileSystem& cur)
{
	std::cout << "Enter adress of a new current catalog (start with \"/\" to use absolute adress): ";
	string CatAdress;
	std::cin >> CatAdress;
	try {
		cur.GoTo(CatAdress);
	}
	catch (std::exception &ex) {
		std::cout << ex.what() << std::endl;
		std::getchar();
	}
}
void SaveSystem(FileSystem& cur)
{
	cur.Save_UserTable("Users.txt");
	cur.Save_Structure("Structure3.txt");
	std::cout << "System saved" << std::endl;
	std::getchar();
}

//string menu_user_table[]
void ShowUserTable(FileSystem& cur)
{
	std::cout << cur.ShowUserTable();
	std::getchar();
}
void AddUser(FileSystem& cur)
{
	string name;
	int key;
	std::cout << "Enter new user's name: ";
	std::cin >> name;
	std::cout << "Enter new user's key: ";
	std::cin >> key;
	try {
		cur.AddTo_UserTable(User(name, key));
	}
	catch (std::exception &ex) {
		std::cout << ex.what() << std::endl;
	}
}
void DeleteUser(FileSystem& cur)
{
	int id;
	std::cout << "Enter ID of the user to delete: ";
	std::cin >> id;
	try {
		cur.DeleteFrom_UserTable(id);
	}
	catch (std::exception &ex) {
		std::cout << ex.what() << std::endl;
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
		std::cout << ex.what() << std::endl;
	}
}

//string menu_catalog[]
void ShowCatalog(FileSystem& system)
{
	std::cout << system.GetCurCat()->Show();
}
void RenameObject(FileSystem& system)
{
	string old_name, new_name;
	std::cout << "Enter current object name:";
	std::cin >> old_name;
	std::cout << "Enter new object name:";
	std::cin >> new_name;
	try {
		system.Rename(old_name, new_name);
	}
	catch (std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}
}
void CopyObject(FileSystem& system)
{
	string object_name;
	std::cout << "Choose object (name): " << std::endl;
	std::cin >> object_name;

	std::getchar();
}
void TransferObject(FileSystem& system)
{
	std::cout << "Come here later" << std::endl;
	std::getchar();
}
void AddFromBuf(FileSystem& system)
{
	std::cout << "Come here later" << std::endl;
	std::getchar();
}
void AddNewObject(FileSystem& system)
{
	std::cout << "Come here later" << std::endl;
	std::getchar();
}
void ShowCatInfo(FileSystem& system)
{
	std::cout << system.GetCurCat()->Info();
	std::getchar();
}

//string menu_file[]
void OpenRead(FileSystem& cur)
{
	std::cout << "Come here later" << std::endl;
	std::getchar();
}
void OpenWrite(FileSystem& cur)
{
	std::cout << "Come here later" << std::endl;
	std::getchar();
}
void Run(FileSystem& cur)
{
	std::cout << "Come here later" << std::endl;
	std::getchar();
}
void ShowInfo(FileSystem& cur)
{
	cur.GetBuf()->Info();
}
void ShowCurAccess(FileSystem& cur)
{
	std::cout << "Come here later" << std::endl;
	std::getchar();
}
void EditUserAccess(FileSystem& cur)
{
	std::cout << "Come here later" << std::endl;
	std::getchar();
}
void ChangeType(FileSystem& cur)
{
	std::cout << "Come here later" << std::endl;
	std::getchar();
}

//string menu_WOfile[]
void AddInfo(FileSystem& cur)
{
	std::cout << "Come here later" << std::endl;
	std::getchar();
}
void ClearFile(FileSystem& cur)
{
	std::cout << "Come here later" << std::endl;
	std::getchar();
}
void RewriteFile(FileSystem& cur)
{
	std::cout << "Come here later" << std::endl;
	std::getchar();
}

//string menu_ROfile[]
void ShowFile(FileSystem& cur)
{
	std::cout << "Come here later" << std::endl;
	std::getchar();
}

void CloseFile(FileSystem& cur)
{
	std::cout << "Come here later" << std::endl;
	std::getchar();
}

//string menu_access[]
void AddAccess(FileSystem& cur)
{
	std::cout << "Come here later" << std::endl;
	std::getchar();
}
void ChangeAccess(FileSystem& cur)
{
	std::cout << "Come here later" << std::endl;
	std::getchar();
}
void ChangeGuestAccess(FileSystem& cur)
{
	std::cout << "Come here later" << std::endl;
	std::getchar();
}
void DeleteAccess(FileSystem& cur)
{
	std::cout << "Come here later" << std::endl;
	std::getchar();
}

//string menu_ENCaccess[]
void AddEncAccess(FileSystem& cur)
{
	std::cout << "Come here later" << std::endl;
	std::getchar();
}
void DeleteEncAccess(FileSystem& cur)
{
	std::cout << "Come here later" << std::endl;
	std::getchar();
}