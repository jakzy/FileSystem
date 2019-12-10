#pragma once
#include "FileSystem.h"
#include "Menu.h"
#undef max

using my_vector::vector;
//using std::vector;

void ShowMenu(size_t i);
void RunMenu(FileSystem &cur, size_t i);

//string menu_system[]
void SystemStat(FileSystem& cur);
void EditUserTable(FileSystem& cur);
void WorkCat(FileSystem& cur);
void WorkFile(FileSystem& cur);
void ChangeCurUser(FileSystem& cur);
void ChangeCurCat(FileSystem& cur);
void SaveSystem(FileSystem& cur);

//string menu_user_table[]
void ShowUserTable(FileSystem& cur);
void AddUser(FileSystem& cur);
void DeleteUser(FileSystem& cur);
void EditUser(FileSystem& cur);

//string menu_catalog[]
void ShowCatalog(FileSystem& system);
void RenameObject(FileSystem& system);
void CopyObject(FileSystem& system);
void TransferObject(FileSystem& system);
void AddFromBuf(FileSystem& system);
void AddNewObject(FileSystem& system);
void ShowCatInfo(FileSystem& system);

//string menu_file[]
void OpenRead(FileSystem& fs);
void OpenWrite(FileSystem& fs);
void Run(FileSystem& fs);
void ShowInfo(FileSystem& fs);
void ShowCurAccess(FileSystem& fs);
void EditUserAccess(FileSystem& fs);
void ChangeType(FileSystem& fs);

//string menu_WOfile[]
void AddInfo(FileSystem &fs);
void ClearFile(FileSystem &fs);
void RewriteFile(FileSystem &fs);

//string menu_ROfile[]
void ShowFile(FileSystem &fs);

//string menu_access[]
void AddAccess(FileSystem &fs);
void ChangeAccess(FileSystem &fs);
void ChangeGuestAccess(FileSystem &fs);
void DeleteAccess(FileSystem &fs);

//string menu_ENCaccess[]
void AddEncAccess(FileSystem &fs);
void DeleteEncAccess(FileSystem &fs);

//arrays

static vector< std::function<void(FileSystem &fs)> > system_menu = { SystemStat, WorkFile, WorkCat, EditUserTable, ChangeCurUser, ChangeCurCat, SaveSystem };
static vector< std::function<void(FileSystem &fs)> > user_table_menu = { ShowUserTable, AddUser, DeleteUser, EditUser };
static vector< std::function<void(FileSystem &fs)> > catalog_menu = { ShowCatalog, RenameObject, CopyObject, TransferObject, AddFromBuf, AddNewObject, ShowCatInfo };
static vector< std::function<void(FileSystem &fs)> > file_menu = { OpenRead, OpenWrite, Run, ShowInfo, ShowCurAccess, EditUserAccess, ChangeType };
static vector< std::function<void(FileSystem &fs)> > WOfile_table_menu = { AddInfo, ClearFile, RewriteFile };
static vector< std::function<void(FileSystem &fs)> > ROfile_table_menu = { ShowFile };
static vector< std::function<void(FileSystem &fs)> > access_menu = { AddAccess, ChangeAccess, ChangeGuestAccess, DeleteAccess };
static vector< std::function<void(FileSystem &fs)> > enc_access_menu = { AddEncAccess, DeleteEncAccess };

static vector< vector<std::function<void(FileSystem &fs)>> > MENU_VECTOR = { system_menu, user_table_menu, catalog_menu, 
	file_menu, WOfile_table_menu, ROfile_table_menu, access_menu, enc_access_menu };

inline void Clear_input() {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}