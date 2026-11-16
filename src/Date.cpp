#include "Date.h"
#include "Input.h"

Date::Date() {

}

Date::Date(int day, int month, int year) {
	set_year(year);
	set_month(month);
	set_day(day);
}

int Date::get_day() const {
	return day;
}
int Date::get_month() const {
	return month;
}
int Date::get_year() const {
	return year;
}

bool Date::set_day(int day) {
	if (day < 1 || day > days_in_month()) {
		return false;
	}
	this->day = day;
	return true;
}

bool Date::set_month(int month) {
	if (month < 1 || month > 12) {
		return false;
	}
	this->month = month;
	return true;
}

bool Date::set_year(int year) {
	if (year < 1) {
		return false;
	}
	this->year = year;
	return true;
}

bool Date::leap_year() const {
	return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
}

int Date::days_in_month() const {
	if (month == 2) {
		if (leap_year()) {
			return 29;
		}
		return 28;
	}
	if (month == 4 || month == 6 || month == 9 || month == 11) {
		return 30;
	}
	return 31;
}

int Date::count_leap_years() const {
	int count = 0;
	for (int i = 1; i < year; i++) {
		if (((i % 4 == 0) && (i % 100 != 0)) || (i % 400 == 0)) {
			count++;
		}
	}
	return count;
}

int Date::to_days() const {
	int months_days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	int days = (year - 1) * 365 + count_leap_years();
	for (int i = 0; i < month - 1; i++) {
		days += months_days[i];
	}
	if (month > 2 && leap_year()) {
		days++;
	}
	return days + day;
}

int days_diff(const Date& date1, const Date& date2) {
	return date2.to_days() - date1.to_days();
}

ostream& operator<<(ostream& os, const Date& date)
{
	os << date.day << "." << date.month << "." << date.year;
	return os;
}

bool Date::input_date() {
	int new_year;
	while (true) {
		if (!read_number("Enter year: ", new_year)) {
			return false;
		}
		if (set_year(new_year)) {
			break;
		}
		cout << "Year must be a positive number. Try again." << endl;
	}

	int new_month;
	while (true) {
		if (!read_number("Enter month: ", new_month)) {
			return false;
		}
		if (set_month(new_month)) {
			break;
		}
		cout << "Month must be from 1 to 12. Try again." << endl;
	}

	int new_day;
	while (true) {
		if (!read_number("Enter day: ", new_day)) {
			return false;
		}
		if (set_day(new_day)) {
			break;
		}
		cout << "This month has " << days_in_month() << " days. Try again." << endl;
	}

	return true;
}

bool input_period(const char* first_title, Date& first, const char* second_title, Date& second) {
	cout << "----" << first_title << "----" << endl;
	if (!first.input_date()) {
		return false;
	}

	cout << "----" << second_title << "----" << endl;
	if (!second.input_date()) {
		return false;
	}

	while (days_diff(first, second) <= 0) {
		cout << second_title << " must be after " << first << ". Try again." << endl;
		if (!second.input_date()) {
			return false;
		}
	}
	return true;
}
