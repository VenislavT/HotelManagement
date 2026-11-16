#pragma once
#include <iostream>
#include <fstream>
using namespace std;

class Date
{
public:
	Date();
	Date(int day, int month, int year);

	int get_day() const;
	int get_month() const;
	int get_year() const;

	bool set_day(int day);
	bool set_month(int month);
	bool set_year(int year);

	int count_leap_years() const;
	int to_days() const;
	friend ostream& operator<<(ostream& os, const Date& date);
	bool input_date();
private:
	int day = 1;
	int month = 1;
	int year = 2000;
	bool leap_year() const;
	int days_in_month() const;
};

int days_diff(const Date& date1, const Date& date2);

bool input_period(const char* first_title, Date& first, const char* second_title, Date& second);
