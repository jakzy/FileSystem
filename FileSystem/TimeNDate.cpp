#include "pch.h"
#include "TimeNDate.h"
#undef min

using std::string;

Time::Time(){
	SYSTEMTIME time;
	GetSystemTime(&time);
	sec = time.wSecond;
	min = time.wMinute;
	hour = time.wHour;
}
Time::Time(size_t hour, size_t min, size_t sec) : hour(hour), min(min), sec(sec) {}
void Time::SetTime(size_t hr, size_t mn, size_t sc) {
	hour = hr;
	min = mn;
	sec = sc;
}
string Time::Show() {
	std::ostringstream out;
	out << hour << " " << min << " " << sec;
	return out.str();
}

Date::Date()
{
	SYSTEMTIME t;
	GetSystemTime(&t);
	time = Time();
	day = t.wDay;
	month = t.wMonth;
	year = t.wYear;
}
void Date::SetDate(size_t hour, size_t min, size_t sec, size_t dy, size_t mon, size_t yr){
	day = dy; 
	month = mon;
	year = yr;
	time = Time(hour, min, sec);
}
string Date::Show() {
	std::ostringstream out;
	out << day << " " << month << " " << year << "\t" << time.Show();
	return out.str();
}
