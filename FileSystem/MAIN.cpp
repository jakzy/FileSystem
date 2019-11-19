#include"FileSystem.h"
using std::map;
using std::vector;
using std::pair;
using std::string;


int main()
{
	//create a new system or download an old one?
	
	//create a new system
	FileSystem system;
	//std::cout << system.Info();
	UserAccess guests = { false, false, false };
	UserAccess superUser = { true, true, true };
	map<ID, UserAccess> acc;
	acc.insert(pair<ID, UserAccess>(0, superUser));
	vector<Stream>* str = new vector<Stream>;
	str->push_back( Stream(system.GetSize()) );
	File newFile(0, acc, guests, str,0, "A random file", system.GetCurCat());
	Object* ptr = dynamic_cast<Object*>(&newFile);
	system.GetCurCat()->Write(system.GetCurUser(), ptr);
	std::cout<<system.GetCurCat()->Show();
	std::cout << system.GetCurCat()->Info();
	//download an od system
	

	//do some stuff with the system

	//finish work (rewrite info in the file)
	
	return 0;
}