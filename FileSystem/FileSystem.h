#pragma once
#include "Object.h"
#include <random>

class FileSystem
{
protected:
	Catalog* root;
	ID ADMIN; // == 0
	map <ID, User> userTable;

	ID curUser;
	Catalog* curCatalog;
	Object* buf;
	static ID guest; // == 1

	size_t size;
	size_t capacity;
public:
	
	FileSystem() {
		ADMIN = 0;
		curUser = ADMIN;
		map<ID, UserAccess> def;
		UserAccess acc = { 1,1,1 };
		def.insert({ ADMIN, acc });
		root = &Catalog(ADMIN, def, acc, "/", nullptr, 0, nullptr) ; 
		//Catalog(ID user, map<ID, UserAccess> acc, UserAccess def, string name, Catalog* cat, size_t virtAdr, map <string, Object*>* catDesc, size_t sz = 0)
		curCatalog = root;
		buf = nullptr;
		guest = 1;
		userTable.insert({ 0, {"ADMIN",1} }); //KEYS???????????
		userTable.insert({ 1, {"guest",0} });
	}
	
	Catalog* GetCur() { return curCatalog; }

	void Start(ID user);
	void Finish();
	//!Edit user table
	ID AddTo_UserTable(User);
	void DeleteFrom_UserTable(ID user);
	void Edit_UserTable(ID, User);

	void ChangeFileType(File&);
	string Info();
	void Rename(string oldName, string newName);
	void Delete(string name);

	void SaveSystem();

	string GoTo(string& input);
};