#include "Reservation.h"

Reservation::Reservation() {

}

Reservation::Reservation(int room_number, const Date& arrival, const Date& leave, const MyString& name, const MyString& additional_info) {
	set_room_number(room_number);
	set_arrival(arrival);
	set_leave(leave);
	set_name(name);
	set_additional_info(additional_info);
}

int Reservation::get_room_number() const {
	return room_number;
}
const Date& Reservation::get_arrival() const {
	return arrival;
}
const Date& Reservation::get_leave() const {
	return leave;
}
const MyString& Reservation::get_name() const {
	return name;
}
const MyString& Reservation::get_additional_info() const {
	return additional_info;
}

void Reservation::set_room_number(int room_number) {
	this->room_number = room_number;
}
void Reservation::set_arrival(const Date& arrival) {
	this->arrival = arrival;
}
void Reservation::set_leave(const Date& leave) {
	this->leave = leave;
}
void Reservation::set_name(const MyString& name) {
	this->name = name;
}
void Reservation::set_additional_info(const MyString& additional_info) {
	this->additional_info = additional_info;
}


bool Reservation::overlaps(const Date& from, const Date& to) const {
	return days_diff(arrival, to) > 0 && days_diff(from, leave) > 0;
}

int Reservation::nights_in_period(const Date& from, const Date& to) const {
	Date start = arrival;
	if (days_diff(start, from) > 0) {
		start = from;
	}
	Date end = leave;
	if (days_diff(end, to) < 0) {
		end = to;
	}

	int nights = days_diff(start, end);
	if (nights < 0) {
		return 0;
	}
	return nights;
}

ostream& operator<<(ostream& os, const Reservation& reservation) {
	os << "Room " << reservation.room_number << " | " << reservation.arrival << " - " << reservation.leave
		<< " | " << reservation.name << " | " << reservation.additional_info;
	return os;
}
