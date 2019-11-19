#pragma once
#include "FileSystem.h"
using std::string;

string menu_base_system[]{ "1. Download a file system", "2. Create a new file sytem" };
string menu_system[]{ "1. Show system statistic", "2. Work with file", "3. Work with current catalog", "4. Edit user table",
	"5. Change current user","6. Change current catalog", "6. Save system", "7. Finish work" };
string menu_user_table[]{ "1. Show user table", "2. Add a new user", "3. Delete user", "4. Edit user profile", "5. Exit" };
string menu_catalog[]{ "1. Show catalog", "2. Rename object", "3. Copy object", "4. Transfer object",
	"5. Add file from buf", "6. Create a new object", "7. Show catalog info", "8. Exit" };
string menu_file[]{ "1. Open to read", "2. Open to write", "3. Run file", "4. Show file info", "5. Show my access rights", 
	"6. Edit users' access rigths table", "7. Change file type", "8. Exit" };
string menu_WOfile[]{ "1. Add info", "2. Clear file", "3. Rewrite file", "4. Close file" };
string menu_ROfile[]{ "1. Show file", "2. Close file" };