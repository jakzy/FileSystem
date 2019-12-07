#include"FileSystem.h"

#undef max

using std::vector;
using std::map;

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

string FileSystem::ShowUserTable()
{
	map <ID, User>::iterator iter = userTable.begin();
	std::ostringstream out;
	for (iter; iter!=userTable.end(); iter++)
	{
		out << iter->first << "\t" << iter->second.GetName();
		curUser == ADMIN ? (out << "\t" << iter->second.GetKey()) : out;
		out << std::endl;
	}
	return out.str();
}
ID FileSystem::AddTo_UserTable(User newUser) {
	if (curUser != ADMIN)
		throw std::exception("Only ADMIN can edit user table");
	else {
		ID id = 0;
		map <ID, User>::iterator iter;
		iter = userTable.end();
		iter--;
		id = iter->first + 1;
		userTable.insert({ id, newUser });
		return id;
	}
}
ID FileSystem::AddTo_UserTable(ID id, User newUser)
{
	if (curUser != ADMIN)
		throw std::exception("Only ADMIN can edit user table");
	else {
		userTable.insert({ id, newUser });
		return id;
	}
}
void FileSystem::DeleteFrom_UserTable(ID user) {
	if (curUser != ADMIN)
		throw std::exception("Only ADMIN can edit user table");
	else {
		if (user == ADMIN)
			throw std::exception("You can't delete ADMIN");
		else {
			map <ID, User>::iterator iter;
			iter = userTable.find(user);
			if (iter == userTable.end())
				throw std::exception("User with such ID doesn't exist");
			else {
				vector <Object*>::iterator itFile = iter->second.GetObjects()->begin();
				vector <Object*>* adm = userTable.find(ADMIN)->second.GetObjects();
				
				for (size_t i = 0; i < iter->second.GetObjects()->size(); )
				{
					vector <Object*>::iterator itFile = iter->second.GetObjects()->begin();
					(*itFile)->ChangeOwner(ADMIN, curUser, ADMIN);
					adm->push_back(*itFile);
					iter->second.GetObjects()->erase(itFile);
				}


		/*		while ((iter->second.GetObjects()->size() > 0)&&(itFile != iter->second.GetObjects()->end())) {
					(*itFile)->ChangeOwner(ADMIN, curUser, ADMIN);
					adm->push_back(*itFile);
					iter->second.GetObjects()->erase(itFile);
				}*/
				userTable.erase(iter);
			}

		}
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

void FileSystem::ChangeCurUser(ID newID)
{
	map <ID, User>::iterator iter = userTable.find(newID);
	if (iter == userTable.end())
		throw std::exception("This user doesn't exist in this system");
	else
		curUser = newID;
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
	std::queue <Object*> objects_in_work;
	std::ostringstream result;
	objects_in_work.push(root);
	while (objects_in_work.size() != 0) {
		if (objects_in_work.front()->iAm() == Catalog_) {
			map<string, Object*>::iterator iter = (static_cast <Catalog*>(objects_in_work.front()))->GetCatalogDescriptor()->begin();
			for (iter; iter != (static_cast <Catalog*>(objects_in_work.front()))->GetCatalogDescriptor()->end(); iter++)
				objects_in_work.push(iter->second);
		}
		result << objects_in_work.front()->Info() << std::endl;
		objects_in_work.pop();
	}
	return result.str();
}
void FileSystem::Rename(string oldName, string newName) {
	try {
		(*curCatalog).Rename(oldName, newName, curUser);
	}
	catch (std::exception &ex) {
		throw ex;
	}
}

Object* FileSystem::Copy(Object* cur) {
	Object* result;
	if (cur->iAm() == Catalog_) {
		result = new Catalog(*(static_cast<Catalog*>(cur)));
		static_cast<Catalog*>(result)->Set_CatalogDescriptor();
		map<string, Object*>::iterator iter = static_cast<Catalog*>(cur)->GetCatalogDescriptor()->begin();
		for (iter; iter != (static_cast<Catalog*>(cur)->GetCatalogDescriptor()->end()); iter++) {
			(static_cast<Catalog*>(result)->GetCatalogDescriptor().insert(("new_" + iter->first), Copy(iter->second));
		}
	}
	else if (cur->iAm() == File_) {
		result = new File(*(static_cast<File*>(cur)));
		result->GetFileDescriptor().first += "new_";
		return result;
	}
}

void FileSystem::Delete(string name) {
	map <string, Object*>::iterator iter;
	iter = (*curCatalog).GetCatalogDescriptor()->find(name);
	if (iter == (*curCatalog).GetCatalogDescriptor()->end())
		throw std::exception("This object doesnt exist in this catalog");
	else {
		if (curUser != (*iter).second->GetOwner())
			throw std::exception("Only owner can delete this object");
		else {
			(*iter).second->Delete();
			(*curCatalog).GetCatalogDescriptor()->erase(name);
		}
	}
}
string FileSystem::GoTo(string& input) {
	size_t i = input.find_first_of('/');
	string next("");
	try {
		next = input.substr(0, i);
		input.erase(i, next.length() + 1);
	}
	catch (std::exception &ex) {
		return input;
	}
	if (i == 0) {
		curCatalog = root;
		GoTo(input);
	}
	else{
		map <string, Object*>::iterator iter;
		iter = (*curCatalog).GetCatalogDescriptor()->find(next);
		if (iter == (*curCatalog).GetCatalogDescriptor()->end()) {
			throw std::exception("Invalid catalog adress");
		}
		else {
			if ( /*(input.find_first_of('/') != input.npos) && */(iter->second->iAm() == Catalog_) ) {
				curCatalog = dynamic_cast<Catalog*>(iter->second);
				GoTo(input);
			}
		}
	}
	return input;
}
void FileSystem::Add(Object* added) {
	try {
		curCatalog->Write(curUser, added);
	}
	catch (std::exception &ex) {
		throw ex;
	}
};

Catalog* FileSystem::Find_NewCurCat(size_t descr, Catalog* current) {
	Catalog* res = nullptr;
	map<string, Object*>::iterator iter;
	iter = current->GetCatalogDescriptor()->begin();
	while ((iter != current->GetCatalogDescriptor()->end()) && (res == nullptr)) {
		if (iter->second->iAm() == Catalog_) {
			Catalog* cat = static_cast<Catalog*> (iter->second);
			if (cat->Get_virtAdr() == descr)
				res = cat;
			else
				res =  Find_NewCurCat(descr, cat);
		}
		iter++;
	}
	return res;
}

void FileSystem::Fill_UserTable(std::string FILE_usTable)
{
	std::ifstream usTable(FILE_usTable);
	if (!usTable) {
		throw std::exception ("Can't open this file");
	}
	int id, key;
	std::string name, buf;
	while (getline(usTable, buf)) {
		std::istringstream cur(buf);
		cur >> id >> name >> key;
		AddTo_UserTable(id, User(name, key));
	}
	usTable.close();
}
void FileSystem::Save_UserTable(std::string FILE_usTable)
{
	std::ofstream usTable(FILE_usTable);
	if (!usTable) {
		throw std::exception("Can't open this file");
	}
	std::string name;
	map <ID, User>::iterator iter = userTable.begin();
	for(iter; iter != userTable.end(); iter++) {
		usTable << iter->first << "\t" << iter->second.GetName() << "\t" << iter->second.GetKey() << std::endl;
	}
	usTable.close();
}

void FileSystem::Fill_Structure(std::string FILE_structure)
{
	std::ifstream structFile(FILE_structure);
	std::string buf;
	int id = 0, key = 0;
	bool root_fl = 1;

	size_t main_block = 0;
	while (getline(structFile, buf)) {
		std::istringstream cur(buf);
		size_t cur_block;
		cur >> cur_block;
		if (cur_block != main_block) {
			main_block = cur_block;
			curCatalog = (Find_NewCurCat(cur_block, root) == nullptr ? curCatalog : Find_NewCurCat(cur_block, root));
		}
		if (cur.str().length() - 1)
		{
			char type = 0;
			cur >> type;
			size_t size = 0;
			ID owner = 0;
			cur >> size >> owner;

			std::istringstream str_accTable(cur.str().substr(cur.str().find('(') + 1, (cur.str().find(')') - cur.str().find('('))));

			vector< pair<ID, UserAccess>> accTable;
			while (str_accTable.peek() != ')') {
				int id, acc;
				str_accTable >> id >> acc;
				UserAccess us_ac = { static_cast<bool>(acc / 100), static_cast<bool>(acc / 10 % 10), static_cast<bool>(acc % 10) };
				accTable.push_back(pair<ID, UserAccess>(id, us_ac));
			}
			cur.ignore(std::numeric_limits<std::streamsize>::max(), ')');

			int acc;
			cur >> acc;
			UserAccess others = { static_cast<bool>(acc / 100), static_cast<bool>(acc / 10 % 10), static_cast<bool>(acc % 10) };

			string name;
			cur >> name;

			vector<Stream> *streamTable = new vector<Stream>;
			std::istringstream str_Table(cur.str().substr(cur.str().rfind('(') + 1, (cur.str().find(')') - cur.str().rfind('('))));
			size_t hour, min, sec,
				day, month, year;
			Date created;
			Date modified;
			size_t descr_offset;
			switch (type) {
			case 'C':
				str_Table >> descr_offset;
				cur.ignore(std::numeric_limits<std::streamsize>::max(), ')');
				break;
			case 'F':
				while (str_Table.peek() != ')') {
					int offset;
					string stream_nm;
					str_Table >> stream_nm >> offset;
					streamTable->push_back(Stream(offset, stream_nm));
				}
				cur.ignore(std::numeric_limits<std::streamsize>::max(), ')');
				cur >> hour >> min >> sec >> day >> month >> year;
				created.SetDate(hour, min, sec, day, month, year);
				cur >> hour >> min >> sec >> day >> month >> year;
				modified.SetDate(hour, min, sec, day, month, year);
				break;
			case 'E':
				while (str_Table.peek() != ')') {
					int offset;
					string stream_nm;
					str_Table >> stream_nm >> offset;
					streamTable->push_back(Stream(offset, stream_nm));
				}
				cur.ignore(std::numeric_limits<std::streamsize>::max(), ')');
				cur >> hour >> min >> sec >> day >> month >> year;
				created.SetDate(hour, min, sec, day, month, year);
				cur >> hour >> min >> sec >> day >> month >> year;
				modified.SetDate(hour, min, sec, day, month, year);
				break;
			default:
				throw std::exception("ERROR TYPE. CHECK FILE");
				break;
			}
			Object* newObject = nullptr;
			if (type == 'C') {
				//if ()
				Catalog *newCat = new Catalog(owner, GetCurCat(), accTable, others, descr_offset, name, size);
				newObject = newCat;
			}
			else if (type == 'F') {
				File *newFile = new File(owner, GetCurCat(), accTable, others, streamTable, size, name, created, modified);
				newObject = newFile;
			}
			else if (type == 'E') {
				std::cout << "Come here later" << std::endl;
				//EncryptedFile newEncFile(id, system.GetCurCat(), accTable, others, streamTable, size, name, created, modified);
			}
			map<ID, User>::iterator iter = userTable.find(owner);
			iter->second.GetObjects()->push_back(newObject);
			if (root_fl) {
				root->GetAccessTable() = static_cast <Catalog*>(newObject)->GetAccessTable();
				root->ChangeOwner(static_cast <Catalog*>(newObject)->GetOwner(), ADMIN, ADMIN);
				root->IncSZ(static_cast <Catalog*>(newObject)->GetSize());
				root_fl = 0;
			}
			else
				curCatalog->GetCatalogDescriptor()->insert(pair<string, Object*>(name, newObject));
		}

	}
	structFile.close();
}
void FileSystem::Save_Structure(std::string FILE_structure)
{
	std::ofstream structure(FILE_structure);
	if (!structure) {
		throw std::exception("Can't open/create this file");
	}
	size_t cur_block = 0, next_free_block = 1,
		   catSZ = 0;
	std::queue <Object*> objects_in_work;
	std::queue <size_t> catalog_SZ;
	objects_in_work.push(root);
	bool root_fl = 1;

	while (objects_in_work.size() != 0) {
		std::ostringstream result_string;
		Object* cur = objects_in_work.front();
		result_string << cur_block << "\t" << (ObjectName[cur->iAm()])[0] << "\t" << cur->GetSize() << "\t" << cur->GetOwner() << "\t";

		vector < pair<ID, UserAccess> >::iterator iter = cur->GetAccessTable().begin();
		result_string << "(";
		for (iter; iter != cur->GetAccessTable().end(); iter++)
			result_string << iter->first << " " << iter->second.read << iter->second.write << iter->second.run << "\t";
		result_string << ")\t";

		result_string << cur->Get_DefaultAccess().read << cur->Get_DefaultAccess().write << cur->Get_DefaultAccess().run << "\t" << cur->GetFileDescriptor().first << "\t";

		if (cur->iAm() == Catalog_) {
			catalog_SZ.push(catSZ);
			map<string, Object*>::iterator iter = (static_cast <Catalog*>(cur))->GetCatalogDescriptor()->begin();
			for (iter; iter != (static_cast <Catalog*>(cur))->GetCatalogDescriptor()->end(); iter++) {
				objects_in_work.push(iter->second);
				catalog_SZ.back()++;
			}
			result_string << "(" << next_free_block++ << ")";
			//cur_block++;
		}
		else if (cur->iAm() == File_) {
			vector<Stream>::iterator iter = (static_cast <File*>(cur))->Get_StreamTable()->begin();
			result_string << "(";
			for (iter; iter != (static_cast <File*>(cur))->Get_StreamTable()->end(); iter++)
				result_string << iter->Get_Name() << " " << iter->Get_Offset() << "\t";
			result_string << ")\t";

			result_string << (static_cast <File*>(cur))->Get_Created().Show() << "\t" << (static_cast <File*>(cur))->Get_Modified().Show();
		}
		else if (cur->iAm() == EncryptedFile_) {
			std::cout << "Come here later" << std::endl;
		}
		objects_in_work.pop();
		if (--catalog_SZ.front() == 0) {
			cur_block++;
			catalog_SZ.pop();
		}
		structure << result_string.str() << std::endl;
		if (root_fl) {
			cur_block++;
			root_fl = FALSE;
		}
	}
}