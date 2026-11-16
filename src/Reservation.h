#pragma once
#include "MyString.h"
#include "Date.h"

class Reservation
{
public:

	Reservation();
	Reservation(int room_number, const Date& arrival, const Date& leave, const MyString& name, const MyString& additional_info);

	int get_room_number() const;
	const Date& get_arrival() const;
	const Date& get_leave() const;
	const MyString& get_name() const;
	const MyString& get_additional_info() const;

	void set_room_number(int room_number);
	void set_arrival(const Date& arrival);
	void set_leave(const Date& leave);
	void set_name(const MyString& name);
	void set_additional_info(const MyString& additional_info);

	bool overlaps(const Date& from, const Date& to) const;
	int nights_in_period(const Date& from, const Date& to) const;

	friend ostream& operator<<(ostream& os, const Reservation& reservation);

private:

	int room_number = 0;
	Date arrival;
	Date leave;
	MyString name;
	MyString additional_info;

};
