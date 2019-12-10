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
		std::cout << "Current user:\tID" << cur.GetCurUser() << std::endl;
		std::cout << "Current catalog:\t" << cur.GetCurCat()->GetFileDescriptor().first << std::endl;
		try { std::cout << cur.GetCurCat()->Show(cur.GetCurUser()); }
		catch (std::exception &ex) { std::cout << ex.what() << std::endl; }
		std::cout << "Buf:\t";
		cur.GetBuf() == nullptr ? (std::cout<< "empty" << std::endl) :
			(std::cout << ObjectName[cur.GetBuf()->iAm()] << "\t" << cur.GetBuf()->GetFileDescriptor().first << std::endl);
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
	if (cur.GetBuf() != nullptr)
	{
		if (cur.GetBuf()->iAm() == File_)
			RunMenu(cur, file_);
		else if (cur.GetBuf()->iAm() == Catalog_) {
			cur.Set_CurCat(static_cast<Catalog*>(cur.GetBuf()));
			RunMenu(cur, catalog_);
		}
		else if (cur.GetBuf()->iAm() == EncryptedFile_) {
			std::cout << "Come here later" << std::endl;
			std::getchar();
		}
	}
	else {
		std::cout << "Buffer is empty, add something there first" << std::endl;
		std::getchar();
	}

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
	try {
		std::cout << system.GetCurCat()->Show(system.GetCurUser());
	}
	catch (std::exception &ex) {
		std::cout << ex.what() << std::endl;
	}
	std::getchar();
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
		std::cout << "Object was succesfully renamed" << std::endl;
	}
	catch (std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}
	std::getchar();
}
void CopyObject(FileSystem& system)
{
	string object_name;
	std::cout << "Choose object (name): " << std::endl;
	std::cin >> object_name;
	try {
		map<string, Object*>::iterator iter = system.GetCurCat()->GetCatalogDescriptor()->find(object_name);
		if (iter != system.GetCurCat()->GetCatalogDescriptor()->end())
			system.Set_Buf(system.Copy(iter->second));
		std::cout << "Object was succesfully copied. \nNow you can work with it from main menu." << std::endl;
	}
	catch (std::exception &ex) {
		std::cout << ex.what() << std::endl;
	}
	std::getchar();
}
void TransferObject(FileSystem& system)
{
	string object_name;
	std::cout << "Choose object (name): " << std::endl;
	std::cin >> object_name;
	try {
		map<string, Object*>::iterator iter = system.GetCurCat()->GetCatalogDescriptor()->find(object_name);
		if (iter != system.GetCurCat()->GetCatalogDescriptor()->end()) {
			system.Set_Buf(system.Copy(iter->second));
			system.GetCurCat()->GetCatalogDescriptor()->erase(iter);
			Catalog *ptr = system.GetCurCat();
			while (ptr != nullptr) {
				ptr->DecSZ(system.GetBuf()->GetSize());
				ptr = ptr->GetFileDescriptor().second;
			}
		}
		std::cout << "Object was succesfully copied and removed from the catalog.\nNow you can work with it from main menu." << std::endl;
	}
	catch (std::exception &ex) {
		std::cout << ex.what() << std::endl;
	}
	std::getchar();
}
void AddFromBuf(FileSystem& system)
{
	try {
		system.GetCurCat()->Add(system.GetBuf(), system.GetCurUser());
		std::cout << "You succesfiully added an object from buf to current catalog." << std::endl;
	}
	catch (std::exception &ex) {
		std::cout << ex.what() << std::endl;
	}
	std::getchar();
}
void AddNewObject(FileSystem& system)
{
	std::cout << "What do you want to create?" << std::endl;
	for (size_t i = 0; i < 2; ++i) {
		std::cout << i << ". " << ObjectName[i] << std::endl;
	}
	size_t choise;
	try {
		std::cin >> choise;
		if ((std::cin.good()) && (choise < 2)) {
			Object * new_object = nullptr;
			Catalog *new_cat;
			File *new_file;
			bool read = 0, write = 0, run = 0;
			std::cout << "Set default user access (*read* *write* *run*, \"0\" for prohibited, \"1\" for accessible):" << std::endl;
			std::cin >> read >> write >> run;
			UserAccess def = { read, write, run };
			string name = "defaul_name";
			std::cout << "Enter name of the object:" << std::endl;
			std::cin >> name;
			size_t size = 0;
			vector<pair<ID, UserAccess>> new_acc;
			switch (choise) {
			case Catalog_:
				new_cat = new Catalog(system.GetCurUser(), system.GetCurCat(), new_acc, def, 0, name, size);
				new_object = new_cat;
				break;
			case File_:
				std::cout << "Enter size of the file:" << std::endl;
				std::cin >> name;
				new_file = new File(system.GetCurUser(), system.GetCurCat(), new_acc, def, new vector<Stream>, size, name);
				new_object = new_file;
				break;
			}
			system.GetCurCat()->Add(new_object, system.GetCurUser());
		}
		else std::cout << "Incorrect input" << std::endl;
	}
	catch (std::exception &ex) {
		std::cout << ex.what() << std::endl;
	}
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
	RunMenu(cur, ROfile_);
	std::getchar();
}
void OpenWrite(FileSystem& cur)
{
	RunMenu(cur, WOfile_);
	std::getchar();
}
void Run(FileSystem& cur)
{
	try {
		static_cast<File*>(cur.GetBuf())->Run(cur.GetCurUser());
	}
	catch (std::exception &ex) {
		std::cout << ex.what() << std::endl;
	}
	std::getchar();
}
void ShowInfo(FileSystem& cur)
{
	std::cout << cur.GetBuf()->Info();
	std::getchar();
}
void ShowCurAccess(FileSystem& cur)
{
	std::cout << cur.GetBuf()->ShowAccess(cur.GetCurUser());
	std::getchar();
}
void EditUserAccess(FileSystem& cur)
{
	RunMenu(cur, access_);
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
	std::cout << "Enter new information: " << std::endl;
	std::string data;
	std::cin >> data;
	try {
		static_cast <File*>(cur.GetBuf())->Rewrite(data, cur.GetCurUser());
		std::cout << "You succesfully edited this file" << std::endl;
	}
	catch (std::exception &ex) {
		std::cout << ex.what() << std::endl;
	}
	std::getchar();
}

//string menu_ROfile[]
void ShowFile(FileSystem& cur)
{
	try {
		std::cout << "File \"" << cur.GetBuf()->GetFileDescriptor().first << "\" data: \""
			<< cur.GetBuf()->Show(cur.GetCurUser()) << "\"" << std::endl;
	}
	catch (std::exception &ex) {
		std::cout << ex.what() << std::endl;
	}
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
	ID id;
	std::cout << "Enter ID of a new user:" << std::endl;
	std::cin >> id;
	bool read = 0, write = 0, run = 0;
	std::cout << "Set the user's access (*read* *write* *run*, \"0\" for prohibited, \"1\" for accessible):" << std::endl;
	std::cin >> read >> write >> run;
	UserAccess def = { read, write, run };
	try {
		cur.GetBuf()->Add_Access(def, id, cur.GetCurUser());
	}
	catch (std::exception &ex) {
		std::cout << ex.what() << std::endl;
	}
	std::getchar();
}
void ChangeAccess(FileSystem& cur)
{
	std::cout << "Come here later" << std::endl;
	std::getchar();
}
void ChangeGuestAccess(FileSystem& cur)
{
	bool read = 0, write = 0, run = 0;
	std::cout << "Set default user access (*read* *write* *run*, \"0\" for prohibited, \"1\" for accessible):" << std::endl;
	std::cin >> read >> write >> run;
	UserAccess def = { read, write, run };
	try {
		cur.GetBuf()->Set_DefaultAccess(def, cur.GetCurUser());
	}
	catch (std::exception &ex) {
		std::cout << ex.what() << std::endl;
	}
	std::getchar();
}
void DeleteAccess(FileSystem& cur)
{
	std::cout << "Enter user's ID:" << std::endl;

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