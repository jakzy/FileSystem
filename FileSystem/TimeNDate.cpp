#include "pch.h"
#include "TimeNDate.h"

using std::string;

Time::Time(){
	SYSTEMTIME time;
	sec = time.wSecond;
	min = time.wMinute;
	hour = time.wHour;
}
string Time::Show() {
	std::ostringstream out;
	out << hour << ":" << min << ":" << sec;
	return out.str();
}

Date::Date()
{
	SYSTEMTIME t;
	time = Time();
	day = t.wDay;
	month = t.wMonth;
	year = t.wYear;
}
string Date::Show() {
	std::ostringstream out;
	out << day << "/" << month << "/" << year << "\t" << time.Show;
	return out.str();
}
