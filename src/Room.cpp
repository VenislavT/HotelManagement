#include "Room.h"

Room::Room() {

}

Room::Room(int room_number, int beds_count, bool is_closed) {
	set_room_number(room_number);
	set_beds_count(beds_count);
	set_is_closed(is_closed);
}

int Room::get_room_number() const {
	return room_number;
}
int Room::get_beds_count() const {
	return beds_count;
}
bool Room::get_is_closed() const {
	return is_closed;
}

bool Room::set_room_number(int room_number) {
	if (room_number <= 0) {
		return false;
	}
	this->room_number = room_number;
	return true;
}
bool Room::set_beds_count(int beds_count) {
	if (beds_count <= 0) {
		return false;
	}
	this->beds_count = beds_count;
	return true;
}
void Room::set_is_closed(bool is_closed) {
	this->is_closed = is_closed;
}

ostream& operator<<(ostream& os, const Room& room) {
	os << "Room " << room.room_number << " | " << room.beds_count;
	if (room.beds_count == 1) {
		os << " bed";
	}
	else {
		os << " beds";
	}
	if (room.is_closed) {
		os << " | CLOSED";
	}
	return os;
}
