#ifndef _OBJECT_H_
#define _OBJECT_H_
#pragma once

#include "TimeNDate.h"
#include <fstream>
#include <cstdlib>

#include <map>
//#include <vector>
#include"My_vector.h"
#define ID int

//int struct_offset = 0;

using std::string;
using std::pair;
using my_vector::vector;
using std::map;

class Catalog;

enum ObjectType {Catalog_, File_, EncryptedFile_};
static string ObjectName[]{ "Catalog", "File", "Encrypted File" };

struct UserAccess
{
	bool read;
	bool write;
	bool run;
};


class Object
{
protected:
	size_t size;
	ID owner;
	vector < pair<ID, UserAccess> > access;
	/*! user ID + his abilities*/
	UserAccess others_access;
	/*! abilities for other users*/
	pair <string, Catalog*> fileDescriptor;
	/*!file name + parent catalog pointer*/
public:
	Object() {};
	virtual ~Object() {};
	virtual int iAm() = 0;
	virtual string Info() = 0;
	virtual string ShowAccess(ID user) = 0;
	virtual string Show(ID user) = 0;
	virtual Object* Copy(ID cur_user) = 0;
	void Set_DefaultAccess(UserAccess def, ID user) {
		if (user == owner)
			others_access = def;
		else
			throw std::exception("ACCESS DENIED");
	}
	void Add_Access(UserAccess def, ID new_user,  ID cur_user) {
		if (cur_user == owner) {
			vector< pair<ID, UserAccess>>::iterator iter = access.begin();
			while (iter != access.end())
				if (iter->first == new_user)
					throw std::exception("Access for this user is already defined");
			access.push_back(pair<ID, UserAccess>{new_user, def});
		}
		else
			throw std::exception("ACCESS DENIED");
	}
	//virtual void Copy() = 0;
	/*virtual void Write(ID user) = 0;
	virtual void Run(string to, ID user) = 0;*/

	/*const */vector< pair<ID, UserAccess> >& GetAccessTable() /*const*/ { return access; }
	UserAccess GetAccess(ID user);
	UserAccess Get_DefaultAccess() { return others_access; }
	pair <string, Catalog*>& GetFileDescriptor() { return fileDescriptor; }
	const unsigned GetSize() { return size; }
	const ID GetOwner() { return owner; }

	void Set_parent(Catalog* parent) {
		pair<string, Catalog*> new_descr = { fileDescriptor.first, parent };
		fileDescriptor = new_descr;
	}

	ID ChangeOwner(ID newOwner, ID curUser, ID adm)
	{
		if ((curUser == owner) || (curUser == adm))
			owner = newOwner;
		else
			throw std::exception("You aren't allowed to change owner of this file");
	}
	void IncSZ(size_t a) { size += a; }
	void DecSZ(size_t a) { size -= a; }
	virtual void Delete() = 0;
};

class User {
protected:
	string name;
	int key;
	vector <Object*> *myObjects;

	void AddObject(Object* newObj) {
		try {
			myObjects->push_back(newObj);
		}
		catch (std::exception &ex) {
			throw ex;
		}
	}
	void DelObject(string name) {
		vector<Object*>::iterator iter;
		iter = myObjects->begin();
		size_t sz = myObjects->size();
		while (iter != myObjects->end())
		{
			if ((*iter)->GetFileDescriptor().first == name) {
				myObjects->erase(iter);
			}
			iter++;
		}
		if (sz == myObjects->size())
			throw std::exception("File wasnt found and deleted");
	}
public:
	User(string nm, int kk ) : name(nm), key(kk) 
	{
		myObjects = new vector <Object*>;
	}
	//~User()
	//{
	//	//delete myObjects;
	//}
	string GetName() { return name; }
	int GetKey() { return key; }
	vector <Object*> *GetObjects() { return myObjects; }
};

class Stream {
protected:
	string name;
	size_t offset;
public:
	Stream( size_t off, string nm = "MAIN") : name(nm), offset(off) {}
	string Get_Name() { return name; }
	size_t Get_Offset() { return offset; }
	void Set_Name(string nm) { name = nm; }
	void Set_Offset(size_t n) { offset = n; }
};

class File : public Object
{
protected:
	vector<Stream>* streamDescriptor;
	Date created,
		 modified;
public:
	//File() = delete;
	File(ID user, Catalog* cat, vector< pair<ID, UserAccess> > acc, UserAccess def, vector<Stream>* strDesc, 
		size_t sz, string name,  Date creat = Date(), Date modi = Date())
	{
		created = creat;
		modified = modi;
		owner = user;
		size = sz;
		access = acc;
		others_access = def;
		streamDescriptor = strDesc;
		strDesc = nullptr;
		fileDescriptor = pair<string, Catalog*>{ name, cat };
	}

	File(File &f) {
		created = Date();
		modified = Date();
		owner = f.owner;
		size = f.size;
		access =f.access;
		others_access = f.others_access;
		streamDescriptor = nullptr;
		string name = f.fileDescriptor.first + "_copied";
		fileDescriptor =  pair<string, Catalog*>{ name, f.fileDescriptor.second };
	}

	vector<Stream> *Get_StreamTable(){ return streamDescriptor; };
	Date Get_Created() { return created; }
	Date Get_Modified() { return modified; }

	vector<Stream> *Set_StreamTable() { streamDescriptor = new vector<Stream>; return streamDescriptor; };

	string Info();
	void Read(ID user);
	void Write(ID user);
	void Run(ID user);
	
	void Create();
	void Close();
	string Show(ID cur_user);
	void Rewrite(string, ID);
	Object* Copy(ID cur_user);
	void Delete() {}
	string ShowAccess(ID user);
	bool ChangeAccess(ID user);
	
	virtual int iAm() { return File_; } //type!
	
};

class EncryptedFile :File
{
private:
	vector <ID> accessibleFor;
	//int control;
public:
	string ShowAccess(ID user);
	bool EncAccess(ID user);
	int iAm() { return EncryptedFile_;}

	vector <ID> &GetEncAccess() { return accessibleFor; }
};

class Catalog : public Object
{
protected:
	size_t virtualAdress; //number of block
	map <string, Object*>* catalogDescriptor; 
	/*!file name + file pointer*/
public:
	Catalog(ID user,  Catalog* cat, vector< pair<ID, UserAccess>> acc,UserAccess def = { 0,0,0 }, size_t virtAdr = 0,  
		 string name = "/", size_t sz = 0, map <string, Object*>* catDesc = new map <string, Object*>)
	{
		owner = user;
		access = acc;
		others_access = def;
		fileDescriptor = { name, cat };
		catalogDescriptor = catDesc;
		size = sz;
		virtualAdress = virtAdr;
		//
	}
	Catalog(Catalog &c)
	{
		owner = c.owner;
		size = c.owner;
		access = c.access;
		others_access = c.others_access;
		virtualAdress = 0;
		string name = c.fileDescriptor.first + "_shortcut";
		map <string, Object*>* catDesc = new map <string, Object*>;
		catDesc->insert(c.catalogDescriptor->begin(), c.catalogDescriptor->end());
		fileDescriptor = pair<string, Catalog*>{ name, c.fileDescriptor.second };
	}
		
	size_t Get_virtAdr() { return virtualAdress; }
	void Set_CatalogDescriptor(map<string, Object*>* newDescr = new map<string, Object*>) { catalogDescriptor = newDescr; }

	string Info();
	void Read(ID user);
	// same as show
	void Write(ID user, Object* added); //  add show
	void Run(string to, ID user); //пройти через каталог

	string Show(ID user);
	string ShowAccess(ID user);
	Object* Copy(ID cur_user);
	void Add(Object*, ID cur_user);
	void Delete();
	void Rename(string, string, ID);

	map <string, Object*>* GetCatalogDescriptor() { return catalogDescriptor; }
	int iAm() { return Catalog_; }
	size_t CatalogNum();
};
#endif // !_OBJECT_H_