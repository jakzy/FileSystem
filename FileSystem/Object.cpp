#include "pch.h"
#include "Object.h"


Object::Object()
{

}


Object::~Object()
{

}

UserAccess Object::GetAccess(ID user) {
	map<ID, UserAccess>::iterator iter = access.find(user);
	if (iter == access.end())
		return others_access;
	else
		return iter->second;
}

string File::Info() {
	std::ostringstream out;
	out << "File name: \"" << fileDescriptor.first << "\"" << std::endl;
	out << "Located in: \"" << fileDescriptor.second << "\"" << std::endl;
	out << "File size: " << size  << std::endl;
	out << "Created: " << created.Show << std::endl;
	out << "Modified: " << modified.Show << std::endl;
	out << "Owner: ID" << owner << std::endl;
	return out.str();
}
void File::Read() {

}
void File::Write() {

}
void File::Run(ID user) {
	UserAccess info;
	info = GetAccess(user);
	if (info.run)
		std::cout << "You successfully ran this incredible file. That was facinating!" << std::endl;
	else
		throw std::exception("This file isn't accessible for you to run");
}

void File::Create() {

}
void File::Close() {

}
void File::Show() {

}
void File::Modify() {

}
string File::ShowAccess(ID user) {
	UserAccess info = GetAccess(user);
	std::ostringstream out;
	out << "Access to file \"" << fileDescriptor.first << "\":" << std::endl;
	out << "Read: " << (info.read ? "YES" : "NO") << std::endl;
	out << "Write: " << (info.write ? "YES" : "NO") << std::endl;
	out << "Run: " << (info.run ? "YES" : "NO") << std::endl;
	return out.str();
}
bool File::ChangeAccess(ID user) {

}
void File::Delete() {
	streamDescriptor->clear();
}

bool EncryptedFile::EncAccess(ID user) {
	vector<ID>::iterator iter;
	iter = accesibleFor.begin();
	for (iter; iter != accesibleFor.end; iter++)
	{
		if ((*iter) == user)
			return true;
	}
	return false;
}
string EncryptedFile::ShowAccess(ID user) {
	if (EncAccess(user)) {
		File*file = dynamic_cast <File*> (this);
		return file->ShowAccess(user);
	}
	else 
		return "You dont have any access to this file";

}

size_t Catalog::CatalogNum() {
	size_t k = 0;
	map <string, Object*>::iterator iter;
	iter = catalogDescriptor->begin();
	for (iter; iter != catalogDescriptor->end(); iter++)
		if ((*iter).second->iAm() == Catalog_)
			++k;
	return k;
}
string Catalog::Info() {
	std::ostringstream out;
	out << "Catalog name: \"" << fileDescriptor.first << "\"" << std::endl;
	out << "Located in: \"" << (*fileDescriptor.second).fileDescriptor.first << "\"" << std::endl;
	out << "Catalog size: " << size << std::endl;
	out << "Objects in this catalog: " << CatalogNum() << " catalogs, "<< (catalogDescriptor->size()- CatalogNum()) << " files."<< std::endl;
	return out.str();
}
void Catalog::Read() {

}
void Catalog::Write() {
	//add file&
}
void Catalog::Run() {

}
string Catalog::Show() {
	map <string, Object*>::iterator iter;
	iter = catalogDescriptor->begin();
	std::ostringstream out;
	out << "Files in catalog \"" << fileDescriptor.first << "\":" << std::endl;
	for (iter; iter != catalogDescriptor->end(); iter++)
		out << ObjectName[(*iter).second->iAm()] << " \"" << iter->first << "\"" << std::endl;
	return out.str();
}
void Catalog::Copy() {

}
void Catalog::Replace() {

}
void Catalog::Delete() {
	map <string, Object*>::iterator iter;
	iter = catalogDescriptor->begin();
	for (iter; iter != catalogDescriptor->end(); iter++)
	{
		(*iter).second->Delete();
		catalogDescriptor->erase(iter);
	}
}
void Catalog::Rename(string oldName, string newName, ID curUser) {
	map <string, Object*>::iterator iter;
	iter = catalogDescriptor->find(oldName);
	if (iter == catalogDescriptor->end())
		throw std::exception("This object doesnt exist in this catalog");
	else {
		if ((*iter).second->iAm() != Catalog_) {
			File *file = dynamic_cast<File*>((*iter).second);
			if ((curUser != file->GetOwner()))
				throw std::exception("Only owner can change name of this file");
		}
		(*iter).second->GetFileDescriptor().first = newName;
		catalogDescriptor->insert({ newName, iter->second });
		catalogDescriptor->erase(oldName);
	}
}