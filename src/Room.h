#pragma once
#include <iostream>
using namespace std;

class Room
{
public:

	Room();
	Room(int room_number, int beds_count, bool is_closed);

	int get_room_number() const;
	int get_beds_count() const;
	bool get_is_closed() const;

	bool set_room_number(int room_number);
	bool set_beds_count(int beds_count);
	void set_is_closed(bool is_closed);

	friend ostream& operator<<(ostream& os, const Room& room);

private:

	int room_number = 1;
	int beds_count = 1;
	bool is_closed = false;

};
