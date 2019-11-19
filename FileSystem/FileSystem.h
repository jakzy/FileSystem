#pragma once
#include "Object.h"
#include <random>

using std::map;
using std::vector;
using std::pair;
using std::string;

class FileSystem
{
protected:
	Catalog* root;
	static const ID ADMIN = 0;
	map <ID, User> userTable;

	ID curUser;
	Catalog* curCatalog;
	Object* buf;
	static const ID guest = 1;

	size_t size;
	size_t capacity;
public:
	
	FileSystem() {
		curUser = ADMIN;
		map<ID, UserAccess> def;
		UserAccess acc = { 1,1,1 };
		def.insert(pair<ID, UserAccess>( ADMIN, acc ));
		map <string, Object*>* catDesc_temp = new map <string, Object*>;
		root = new Catalog (ADMIN, def, nullptr, 0,  acc);
		//Catalog(ID user, map<ID, UserAccess> acc, UserAccess def, string name, Catalog* cat, size_t virtAdr, map <string, Object*>* catDesc, size_t sz = 0)
		curCatalog = root;
		buf = nullptr;
		userTable.insert({ 0, {"ADMIN",1} }); //KEYS???????????
		userTable.insert({ 1, {"guest",0} });
	}
	
	Catalog* GetRoot() { return root; }
	Catalog* GetCurCat() { return curCatalog; }
	ID GetCurUser() { return curUser; }
	size_t GetSize() { return size; }
	size_t GetCapacity() { return capacity; }
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

	void SaveSystem() {};

	string GoTo(string& input);
};