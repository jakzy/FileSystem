#include"Dialog.h"
#include <fstream>
#include <cstdlib>
#undef max
using std::map;
using std::vector;
using std::pair;
using std::string;

int main()
{
	FileSystem system;
	
	std::ifstream usTable("Users.txt");
	if (!usTable) {
		std::cerr << "cannot open file" << std::endl;
		return 1;
	}
	int id, key;
	string name , buf;
	while (getline(usTable, buf)) {
		std::istringstream cur(buf);
		cur >> id >> name >> key;
		system.AddTo_UserTable(id, User(name, key));
	}

	std::ifstream structFile("Structure.txt");
	if (!structFile) {
		std::cerr << "cannot open file" << std::endl;
		return 1;
	}
	size_t main_block = 0;
	while (getline(structFile, buf)) {
		std::istringstream cur(buf);
		size_t cur_block;
		cur >> cur_block;
		if (cur_block != main_block) {
			main_block = cur_block;
			//изменить текущий каталог на такой, для которого инфа лежит в новом текущем блоке
			
		}
		if (cur.str().length() - 1)
		{
			char type = 0;
			cur >> type;
			size_t size = 0;
			ID owner = 0;
			cur >> size >> owner;

			std::istringstream str_accTable (cur.str().substr( cur.str().find('(')+1, (cur.str().find(')')- cur.str().find('('))));
	
			vector< pair<ID, UserAccess>> accTable;
			while (str_accTable.peek()!=')') {
				int id, acc;
				str_accTable >> id >> acc;
				UserAccess us_ac = { static_cast<bool>(acc/100), static_cast<bool>(acc/10%10), static_cast<bool>(acc%10) };
				accTable.push_back( pair<ID, UserAccess>(id, us_ac));
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
			Object* newObject;
			if (type == 'C') {
				//if ()
				Catalog newCat(id,  system.GetCurCat(), accTable,others, descr_offset, name, size);
			}
			else if (type == 'F') {
				File newFile(id, system.GetCurCat(), accTable, others, streamTable, size, name, created, modified);
			}
			else if (type == 'E') {
				std::cout << "Come here later" << std::endl;
				//EncryptedFile newEncFile(id, system.GetCurCat(), accTable, others, streamTable, size, name, created, modified);
			}
			
		}

	}
	std::getchar();
	try {
		RunMenu(system, 0);
	}
	catch (std::exception &ex) {
		std::cout << ex.what();
	}
	/*
	UserAccess guests = { false, false, false };
	UserAccess superUser = { true, true, true };
	vector<pair<ID, UserAccess>> acc;
	acc.push_back(pair<ID, UserAccess>(0, superUser));
	vector<Stream>* str = new vector<Stream>;
	str->push_back( Stream(system.GetSize()) );
	File newFile(0, acc, guests, str,0, "A random file", system.GetCurCat());
	Object* ptr = dynamic_cast<Object*>(&newFile);
	system.GetCurCat()->Write(system.GetCurUser(), ptr);
	std::cout << system.GetCurCat()->Show();
	std::cout << system.GetCurCat()->Info();*/
	return 0;
}