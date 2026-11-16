#pragma once
#include <vector>
#include "Room.h"
#include "Reservation.h"
#include "MyString.h"

class Collection
{
public:

	void read_all();
	void save_rooms();
	void save_reservations();

	int rooms_count() const;
	int reservations_count() const;
	Room& operator[] (int index);
	const Room& operator[] (int index) const;
	const Reservation& get_reservation(int index) const;

	void add_reservation(const Reservation& reservation);
	void remove_reservation(int index);

	int find_room_index(int room_number) const;
	int conflicting_reservation(int room_number, const Date& from, const Date& to) const;

	void show_rooms() const;
	int show_free_rooms(const Date& from, const Date& to, int min_beds) const;
	int show_reservations() const;
	int show_reservations_of_room(int room_number) const;
	int choose_reservation() const;

private:
	vector<Room> rooms;
	vector<Reservation> reservations;

	MyString split_field(const MyString& source, int& index, char separator) const;
	bool read_one_room(const MyString& line, Room& room) const;
	bool read_one_reservation(const MyString& line, Reservation& reservation) const;
	bool read_date(const MyString& text, Date& date) const;
};
