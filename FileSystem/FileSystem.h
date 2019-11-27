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
		vector< pair<ID, UserAccess> > def;
		UserAccess acc = { 1,1,1 };
		def.push_back(pair<ID, UserAccess>( ADMIN, acc ));
		map <string, Object*>* catDesc_temp = new map <string, Object*>;
		root = new Catalog (ADMIN, nullptr, def, acc);

		curCatalog = root;
		buf = nullptr;
		//userTable.insert({ 0, {"ADMIN",1} }); //KEYS???????????
		//userTable.insert({ 1, {"guest",0} });
	}
	
	Catalog* GetRoot() { return root; }
	Catalog* GetCurCat() { return curCatalog; }
	map <ID, User>& GetUserTable() { return userTable; };
	ID GetCurUser() { return curUser; }
	ID GetAdmin() {return ADMIN;}
	size_t GetSize() { return size; }
	size_t GetCapacity() { return capacity; }
	void Start(ID user);
	void Finish();
	//!Edit user table
	string ShowUserTable();
	ID AddTo_UserTable(User);
	ID AddTo_UserTable(ID, User);
	void DeleteFrom_UserTable(ID user);
	void Edit_UserTable(ID, User);

	void ChangeCurUser(ID newUser);
	void ChangeFileType(File&);
	string Info();
	void Rename(string oldName, string newName);
	void Delete(string name);

	void SaveSystem() {};

	string GoTo(string& input);
};