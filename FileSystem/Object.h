#pragma once

#include "TimeNDate.h"

#include <map>
#include <vector>
#define ID int

using std::string;
using std::pair;
using std::vector;
using std::map;

enum ObjectType {Catalog_, File_, EncryptedFile_};
string ObjectName[]{ "Catalog", "File", "Encrypted File" };

struct UserAccess
{
	bool read;
	bool write;
	bool run;
};

class Object;

class User {
protected:
	string name;
	int key;
	vector <Object*> myObjects;

	void AddObject(Object* newObj) {
		try {
			myObjects.push_back(newObj);
		}
		catch (std::exception &ex) {
			throw ex;
		}
	}
	void DelObject(string name) {
		vector<Object*>::iterator iter;
		iter = myObjects.begin;
		size_t sz = myObjects.size();
		while (iter != myObjects.end())
		{
			if ((*iter)->GetFileDescriptor->first == name) {
				myObjects.erase(iter);
			}
			iter++;
		}
		if (sz == myObjects.size())
			throw std::exception("File wasnt found and deleted");
	}
public:
	User(string nm, int kk) : name(nm), key(kk) {}
};

class Stream {
protected:
	string name;
	size_t offset;
	static const size_t size = 128;
public:
	Stream( size_t off, string nm = "MAIN") : name(nm), offset(off) {}
};

class Object
{
protected:
	size_t size;
	ID owner;
	map <ID, UserAccess> access;
	/*! user ID + his abilities*/
	UserAccess others_access;
	/*! abilities for other users*/
	pair <string, Catalog*> fileDescriptor;
	/*!file name + catalog pointer*/
public:
	Object();
	virtual ~Object();
	virtual int iAm() = 0;
	virtual string Info()  = 0;
	virtual void Read(ID user) = 0;
	virtual void Write(ID user) = 0;
	virtual void Run(string to, ID user) = 0;

	const map <ID, UserAccess>& GetAccessTable() const { return access; }
	UserAccess GetAccess(ID user);
	pair <string, Catalog*>& GetFileDescriptor() {return fileDescriptor;}
	const unsigned GetSize() { return size; }
	const ID GetOwner()  { return owner; }
	virtual void Delete() = 0;
}; 


class File : public Object
{
protected:
	vector<Stream>* streamDescriptor;
	Date created,
		 modified;
public:
	//File() = delete;
	File(ID user, map<ID, UserAccess> acc, UserAccess def, vector<Stream>* strDesc, 
		size_t sz, string name, Catalog* cat, Date creat = Date(), Date modi = Date())
	{
		created = creat;
		modified = modi;
		owner = user;
		size = sz;
		access = acc;
		others_access = def;
		streamDescriptor = strDesc;
		strDesc = nullptr;
		fileDescriptor = { name, cat };
	}

	string Info();
	void Read(ID user);
	void Write(ID user);
	void Run(string to, ID user);
	
	void Create();
	void Close();
	void Show();
	void Modify();
	virtual string ShowAccess(ID user);
	bool ChangeAccess(ID user);
	
	virtual int iAm() { return File_; } //type!
	void Delete();
};

class EncryptedFile :File
{
private:
	vector <ID> accesibleFor;
public:
	string ShowAccess(ID user);
	bool EncAccess(ID user);
	int iAm() { return EncryptedFile_;}

	vector <ID> &GetEncAccess() { return accesibleFor; }
};

class Catalog : public Object
{
protected:
	size_t virtualAdress;
	map <string, Object*>* catalogDescriptor; 
	/*!file name + file pointer*/
public:
	Catalog(ID user, map<ID, UserAccess> acc, UserAccess def, string name, Catalog* cat, size_t virtAdr, map <string, Object*>* catDesc, size_t sz = 0 )
	{
		owner = user;
		size = sz;
		access = acc;
		others_access = def;
		fileDescriptor = { name, cat };
		catalogDescriptor = catDesc;
		catDesc = nullptr;
	}
	string Info();
	void Read(ID user);
	// same as show
	void Write(ID user); //  add show
	void Run(string to, ID user); //пройти через каталог

	string Show();
	void Copy();
	void Replace();
	void Delete();
	void Rename(string, string, ID);

	map <string, Object*>* GetCatalogDescriptor() { return catalogDescriptor; }
	int iAm() { return Catalog_; }
	size_t CatalogNum();
};