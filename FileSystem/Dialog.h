#pragma once
#include "FileSystem.h"
#include "Menu.h"
//string menu_base_system[]

//string menu_system[]
void SystemStat(FileSystem& cur);
void WorkFile(FileSystem& cur);
void WorkCat(FileSystem& cur);
void EditUserTable(FileSystem& cur);
void ChangeCurUser(FileSystem& cur);
void ChangeCurCat(FileSystem& cur);
void SaveSystem(FileSystem& cur);
void FinishWork(FileSystem& cur);

//string menu_user_table[]
void AddUser(map<ID, User>& userTable);
void DeleteUser(map<ID, User>& userTable);
void EditUser(map<ID, User>& userTable);
//void FinishWork(map<ID, User>& userTable);

//string menu_catalog[]
void ShowCatalog(FileSystem& system);
void RenameObject(FileSystem& system);
void CopyObject(FileSystem& system);
void TransferObject(FileSystem& system);
void AddFromBuf(FileSystem& system);
void AddNewObject(FileSystem& system);
void ShowInfo(FileSystem& system);
void Exit(FileSystem& cur);

//string menu_file[]
void OpenRead(FileSystem& cur, File& file);
void OpenWrite(FileSystem& cur, File& file);
void Run(FileSystem& cur, File& file);
void ShowInfo(FileSystem& cur, File& file);
void ShowCurAccess(FileSystem& cur, File& file);
void EditUserAccess(FileSystem& cur, File& file);
void ChangeType(FileSystem& cur, File& file);
void Exit(FileSystem& cur, File& file);

//string menu_WOfile[]
void AddInfo(File&file);
void ClearFile(File& file);
void RewriteFile(File& file);

//string menu_ROfile[]
void ShowFile(File& file);

void CloseFile(File& file);

//string menu_access[]
void AddAccess(File& file);
void ChangeAccess(File& file);
void ChangeGuestAccess(File& file);
void DeleteAccess(File& file);
void Exit(File& file);

//string menu_ENCaccess[]
void AddAccess(EncryptedFile& file);
void DeleteAccess(EncryptedFile& file);
void Exit(EncryptedFile& file);