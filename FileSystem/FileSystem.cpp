#include"FileSystem.h"

void FileSystem::Start(ID user) {
	map<ID, User>::iterator iter;
	iter = userTable.find(user);
	if (iter == userTable.end())
		throw std::exception("This user doesn't exist, ADMIN can add them");
	else {
		curUser = user;
	}
}
void FileSystem::Finish() {
	curUser = guest;
	curCatalog = root;
	//save system
}
ID FileSystem::AddTo_UserTable(User newUser) {
	if (curUser != ADMIN)
		throw std::exception("Only ADMIN can edit user table");
	else {
		SYSTEMTIME t;
		srand(t.wSecond);
		ID id = 0;
		do {
			ID id = rand();
			map <ID, User>::iterator iter;
			iter = userTable.find(id);
			if (iter == userTable.end())
				userTable.insert({ id, newUser });
		} while (id == 0);
		return id;
	}
}
void FileSystem::DeleteFrom_UserTable(ID user) {
	if (curUser != ADMIN)
		throw std::exception("Only ADMIN can edit user table");
	else {
		if (user == ADMIN)
			throw std::exception("You can't delete ADMIN");
		//удалить пользователя: удалить из таблицы пользователей, СДЕЛАТЬ АДМИНА НОВЫМ ВЛАДЕЛЬЦЕМ ВСЕХ ФАЙЛОВ, удалить из списков управления доступом для всех файлов системы. НЕЛЬЗЯ УДАЛИТЬ АДМИНА
	}
}

void FileSystem::Edit_UserTable(ID id, User newInfo) {
	if (curUser != ADMIN)
		throw std::exception("Only ADMIN can edit user table");
	else {
		map <ID, User>::iterator iter;
		iter = userTable.find(id);
		if (iter == userTable.end())
			throw std::exception("User with this ID doesn't exist");
		else
			(*iter).second = newInfo;
	}
}

void FileSystem::ChangeFileType(File& file) {
	map<ID, User>::iterator iter;
	iter = userTable.find(curUser);
	if (iter->first != file.GetOwner())
		throw std::exception("This user can't change type of this file");
	else {
		if (file.iAm() == EncryptedFile_) {
			//удалить таблицу доступа, расшифровать, удалить поток SYMKEY (конструктор обычного от зашифрованного)
		}
		else {
			//заполнить таблицу доступа, зашифровать, добавить поток SYMKEY (конструктор зашифрованного от обычного)
		}
	}
}
string FileSystem::Info() {

}

void FileSystem::Rename(string oldName, string newName) {
	try {
		(*curCatalog).Rename(oldName, newName, curUser);
	}
	catch (std::exception &ex) {
		throw ex;
	}
}

void FileSystem::Delete(string name) {
	map <string, Object*>::iterator iter;
	iter = (*curCatalog).GetCatalogDescriptor->find(name);
	if (iter == (*curCatalog).GetCatalogDescriptor->end())
		throw std::exception("This object doesnt exist in this catalog");
	else {
		if (curUser != (*iter).second->GetOwner())
			throw std::exception("Only owner can delete this object");
		else {
			(*iter).second->Delete();
			(*curCatalog).GetCatalogDescriptor->erase(name);
		}
	}
}

string FileSystem::GoTo(string& input) {
	size_t i = input.find_first_of('/');
	string next = input.substr(i, input.find_first_of('/', i + 1));
	input.erase(i, input.find_first_of('/', i + 1));
	if (i == 0) {
		curCatalog = root;
		GoTo(input);
	}
	else{
		map <string, Object*>::iterator iter;
		iter = (*curCatalog).GetCatalogDescriptor.find(next);
		if (next == (*curCatalog).GetCatalogDescriptor.end()) {
			throw std::exception("Incorrect file adress");
		}
		else {
			if ( (input.find_first_of('/') != input.npos) && (iter->second->iAm == Catalog_) ) {
				curCatalog = dynamic_cast<Catalog*>(iter->second);
				GoTo(input);
			}
		}
	}
	return input;
}