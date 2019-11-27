#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <Windows.h>

using std::string;

class Time {
private:
	size_t sec, min, hour;
public:
	Time();
	Time(size_t hour, size_t min, size_t sec);
	void SetTime(size_t hour, size_t min, size_t sec);

	string Show();
};

class Date {
private:
	Time time;
	size_t day,
		   month,
		   year;
public:
	Date();
	void SetDate(size_t hour, size_t min, size_t sec, size_t dy, size_t month, size_t year);
	string Show();
};
