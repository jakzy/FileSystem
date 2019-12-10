
#include "Object.h"


UserAccess Object::GetAccess(ID user) {
	vector<pair<ID, UserAccess>>::iterator iter = access.begin();
	for (iter; iter != access.end(); iter++)
	{
		if (iter->first == user)
			return iter->second;
	}
	return	others_access;
}

string File::Info() {
	std::ostringstream out;
	out << "File name: \"" << fileDescriptor.first << "\"" << std::endl;
	if (fileDescriptor.second!=nullptr)
		out << "Located in: \"" << fileDescriptor.second->GetFileDescriptor().first << "\"" << std::endl;
	out << "File size: " << size  << std::endl;
	out << "Created: " << created.Show() << std::endl;
	out << "Modified: " << modified.Show() << std::endl;
	out << "Owner: ID" << owner << std::endl;
	return out.str();
}
void File::Write(ID user) {
	if (GetAccess(user).write) {

	}
	else throw std::exception("You can't write into this file");
}
void File::Run(ID user) {
	UserAccess info;
	info = GetAccess(user);
	if ((info.run)||(user == 1))
		std::cout << "You successfully ran this incredible file. That was facinating!" << std::endl;
	else
		throw std::exception("ACCESS DENIED");
}

void File::Create() {
	std::cout << "Come here later" << std::endl;
	std::getchar();
}
void File::Close() {
	std::cout << "Come here later" << std::endl;
	std::getchar();
}
string File::Show(ID cur_user) {
	if ((GetAccess(cur_user).read) || (cur_user == 0)) {
		std::ifstream data("Data.txt");
		std::string buf;
		size_t i = 0;
		while (getline(data, buf)) {
			if (i == streamDescriptor->begin()->Get_Offset()) {
				data.close();
				return buf;
			}
			else {
				buf = "";
				++i;
			}
		}
		data.close();
		throw std::exception("DATA WAS CORRUPTED");
	}
	else
		throw std::exception("ACCESS DENIED");
}
void File::Rewrite(std::string new_line, ID cur_user) {
	if ((GetAccess(cur_user).write) || (cur_user == 0)) {
		std::ofstream new_data("Data_New.txt");
		size_t n = streamDescriptor->begin()->Get_Offset();
		std::ifstream old_data("Data.txt");
		std::string buf;
		size_t i = 0;
		while (getline(old_data, buf)) {
			if (i == n) {
				new_data << new_line;
			}
			else {
				new_data << buf;
				++i;
			}
		}
		remove("Data.txt");
		rename("Data_New.txt", "Data.txt");
		new_data.close();
	}
	else
		throw std::exception("ACCESS DENIED");
}

string File::ShowAccess(ID user) {
	UserAccess info = GetAccess(user);
	std::ostringstream out;
	if (user == owner)
		out << "You're the owner of the file" << std::endl;
	out << "Access to file \"" << fileDescriptor.first << "\":" << std::endl;
	out << "Read: " << (info.read ? "YES" : "NO") << std::endl;
	out << "Write: " << (info.write ? "YES" : "NO") << std::endl;
	out << "Run: " << (info.run ? "YES" : "NO") << std::endl;
	return out.str();
}
bool File::ChangeAccess(ID user) {
	return false;
}
Object* File::Copy(ID cur_user) {
	if ((GetAccess(cur_user).read) || (cur_user == 0)) {
		std::fstream data("Data.txt");
		std::string buf;
		File* new_file = new File(*this);
		size_t i = 0;
		while ( getline(data, buf) && (i < streamDescriptor->begin()->Get_Offset()) ) {
			++i;
		}
		if (i == streamDescriptor->begin()->Get_Offset()) {
			data.seekp(std::ios::end);
			data << buf;
			data.seekp(0);
			while (getline(data, buf)) {
				++i;
			}
			new_file->Set_StreamTable()->push_back(Stream(i));
			return new_file;
		}
		data.close();
	}
	else
		throw std::exception("ACCESS DENIED");
}

bool EncryptedFile::EncAccess(ID user) {
	vector<ID>::iterator iter;
	iter = accessibleFor.begin();
	for (iter; iter != accessibleFor.end(); iter++)
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
		if (iter->second->iAm() == Catalog_)
			++k;
	return k;
}
string Catalog::Info() {
	std::ostringstream out;
	out << "Catalog name: \"" << fileDescriptor.first << "\"" << std::endl;
	if (fileDescriptor.second != nullptr)
		out << "Located in: \"" << fileDescriptor.second->fileDescriptor.first << "\"" << std::endl;
	else out << "This is ROOT catalog" << std::endl;
	out << "Catalog size: " << size << std::endl;
	out << "Objects in this catalog: " << CatalogNum() << " catalogs, "<< (catalogDescriptor->size()- CatalogNum()) << " files."<< std::endl;
	return out.str();
}
void Catalog::Write(ID user, Object* added) {
	if ((GetAccess(user).write)||(user == 1)) {
		pair<string, Object*> add = {added->GetFileDescriptor().first, added};
		GetCatalogDescriptor()->insert(add);
		IncSZ(added->GetSize());
	}
	else throw std::exception("ACCESS DENIED");
}
void Catalog::Run(string to, ID user) {
	if (GetAccess(user).run) {

	}
	else throw std::exception("You can't go through this catalog");
}
string Catalog::Show(ID user) {
	if ((user == owner)||(user == 0)) {
		map <string, Object*>::iterator iter;
		iter = catalogDescriptor->begin();
		std::ostringstream out;
		out << "Objects in catalog \"" << fileDescriptor.first << "\":" << std::endl;
		for (iter; iter != catalogDescriptor->end(); iter++)
			out << ObjectName[(*iter).second->iAm()] << "\t \"" << iter->first << "\"" << std::endl;
		return out.str();
	}
	else
		throw std::exception("ACCESS DENIED");
}
string Catalog::ShowAccess(ID user) {
	UserAccess info = GetAccess(user);
	std::ostringstream out;
	if (user == owner)
		out << "You're the owner of the catalog" << std::endl;
	out << "Access to catalog \"" << fileDescriptor.first << "\":" << std::endl;
	out << "Read: " << (info.read ? "YES" : "NO") << std::endl;
	out << "Write: " << (info.write ? "YES" : "NO") << std::endl;
	out << "Go through: " << (info.run ? "YES" : "NO") << std::endl;
	return out.str();
}

Object* Catalog::Copy(ID cur_user) {
	if ((GetAccess(cur_user).read) || (cur_user == 0)) {
		Catalog* result = new Catalog(*this);
		result->Set_CatalogDescriptor();
		map<string, Object*>::iterator iter = catalogDescriptor->begin();
		for (iter; iter != catalogDescriptor->end(); iter++) {
			result->GetCatalogDescriptor()->insert(pair<string, Object*>(iter->first, iter->second->Copy(cur_user))); ////!
		}
		return result;
	}
	else
		throw std::exception("ACCESS DENIED");
}
void Catalog::Add(Object* new_object, ID cur_user) {
	if (new_object == nullptr)
		throw std::exception("Object doesnt exist");
	try {
		if ((GetAccess(cur_user).write) || (cur_user == 0)) {
			catalogDescriptor->insert(pair <string, Object*>(new_object->GetFileDescriptor().first, new_object));
			new_object->Set_parent(this);
			Catalog* ptr = this;
			while (ptr != nullptr) {
				ptr->IncSZ(new_object->GetSize());
				ptr = ptr->fileDescriptor.second;
			}
		}
		else
			throw std::exception("ACCESS DENIED");
	}
	catch (std::exception &ex) {
		throw ex;
	}
}
void Catalog::Delete() {
	map <string, Object*>::iterator iter = catalogDescriptor->begin();
	for (iter; iter != catalogDescriptor->end(); iter++)
	{
		iter->second->Delete();
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