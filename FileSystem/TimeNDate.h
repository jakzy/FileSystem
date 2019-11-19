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
	string Show();
};
