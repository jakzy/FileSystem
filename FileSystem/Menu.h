#pragma once
using std::string;
#include <functional>

//string menu_base_system[]{ "1. Download a file system", "2. Create a new file sytem" };
static vector<string> menu_system = { "1. Show system statistic", "2. Work with file in the buffer", "3. Work with current catalog", "4. Edit user table",
	"5. Change current user","6. Change current catalog", "7. Save system", "CTRL+Z to finish work" };
static vector<string> menu_user_table = { "1. Show user table", "2. Add a new user", "3. Delete user", "4. Edit user profile", "CTRL+Z to finish work" };
static vector<string> menu_catalog = { "1. Show catalog", "2. Rename object", "3. Copy object", "4. Transfer object",
	"5. Add file from buf", "6. Create a new object", "7. Show catalog info", "CTRL+Z to finish work" };
static vector<string> menu_file = { "1. Open to read", "2. Open to write", "3. Run file", "4. Show file info", "5. Show my access rights",
	"6. Edit users' access rigths table", "7. Change file type", "CTRL+Z to finish work" };
static vector<string> menu_WOfile = { "1. Add info", "2. Clear file", "3. Rewrite file", "CTRL+Z to finish work" };
static vector<string> menu_ROfile = { "1. Show file", "CTRL+Z to finish work" };
static vector<string> menu_access = { "1. Define access rights for a new user", "2. Change access rights for user", "3. Change guest access rights", "4. Delete user's access rights",
	"CTRL+Z to finish work" };
static vector<string> menu_ENC_access = { "1. Share access for a new user",  "2. Delete access rights for a user", "CTRL+Z to finish work" };

static vector< vector<string>> MENU_SET = { menu_system, menu_user_table, menu_catalog,
	menu_file, menu_WOfile, menu_ROfile, menu_access, menu_ENC_access };
enum MENU_NUM { system_, user_table_, catalog_, 
	file_, WOfile_, ROfile_, access_, ENC_access_};