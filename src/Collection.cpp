#include "Collection.h"
#include "Input.h"
#include <algorithm>
#include <cstdlib>

const char ROOMS_FILE[] = "data/rooms.txt";
const char RESERVATIONS_FILE[] = "data/reservations.txt";

bool fewer_beds(const Room& a, const Room& b) {
	return a.get_beds_count() < b.get_beds_count();
}

bool earlier_reservation(const Reservation& a, const Reservation& b) {
	if (a.get_room_number() != b.get_room_number()) {
		return a.get_room_number() < b.get_room_number();
	}
	return days_diff(a.get_arrival(), b.get_arrival()) > 0;
}

void Collection::read_all() {
	rooms.clear();
	reservations.clear();
	MyString line;

	ifstream rooms_file(ROOMS_FILE);
	if (!rooms_file.is_open()) {
		cout << "Error opening " << ROOMS_FILE << endl;
	}
	while (getline(rooms_file, line)) {
		Room room;
		if (read_one_room(line, room)) {
			rooms.push_back(room);
		}
	}
	rooms_file.close();

	ifstream reservations_file(RESERVATIONS_FILE);
	while (getline(reservations_file, line)) {
		Reservation reservation;
		if (read_one_reservation(line, reservation)) {
			reservations.push_back(reservation);
		}
	}
	reservations_file.close();

	sort(reservations.begin(), reservations.end(), earlier_reservation);
}

void Collection::save_rooms() {
	ofstream file(ROOMS_FILE);
	if (!file.is_open()) {
		cout << "Error saving " << ROOMS_FILE << endl;
		return;
	}
	for (int i = 0; i < rooms_count(); i++) {
		file << rooms[i].get_room_number() << "/" << rooms[i].get_beds_count() << "/" << rooms[i].get_is_closed() << endl;
	}
	file.close();
}

void Collection::save_reservations() {
	sort(reservations.begin(), reservations.end(), earlier_reservation);

	ofstream file(RESERVATIONS_FILE);
	if (!file.is_open()) {
		cout << "Error saving " << RESERVATIONS_FILE << endl;
		return;
	}
	for (int i = 0; i < reservations_count(); i++) {
		const Reservation& r = reservations[i];
		file << r.get_room_number() << "/" << r.get_arrival() << "/" << r.get_leave() << "/"
			<< r.get_name() << "/" << r.get_additional_info() << endl;
	}
	file.close();
}

int Collection::rooms_count() const {
	return (int)rooms.size();
}

int Collection::reservations_count() const {
	return (int)reservations.size();
}

Room& Collection::operator[] (int index) {
	return rooms[index];
}

const Room& Collection::operator[] (int index) const {
	return rooms[index];
}

const Reservation& Collection::get_reservation(int index) const {
	return reservations[index];
}

void Collection::add_reservation(const Reservation& reservation) {
	reservations.push_back(reservation);
}

void Collection::remove_reservation(int index) {
	reservations.erase(reservations.begin() + index);
}

int Collection::find_room_index(int room_number) const {
	for (int i = 0; i < rooms_count(); i++) {
		if (rooms[i].get_room_number() == room_number) {
			return i;
		}
	}
	return -1;
}

int Collection::conflicting_reservation(int room_number, const Date& from, const Date& to) const {
	for (int i = 0; i < reservations_count(); i++) {
		if (reservations[i].get_room_number() == room_number && reservations[i].overlaps(from, to)) {
			return i;
		}
	}
	return -1;
}

void Collection::show_rooms() const {
	for (int i = 0; i < rooms_count(); i++) {
		cout << rooms[i] << endl;
	}
}

int Collection::show_free_rooms(const Date& from, const Date& to, int min_beds) const {
	vector<Room> free_rooms;
	for (int i = 0; i < rooms_count(); i++) {
		if (!rooms[i].get_is_closed() && rooms[i].get_beds_count() >= min_beds &&
			conflicting_reservation(rooms[i].get_room_number(), from, to) == -1) {
			free_rooms.push_back(rooms[i]);
		}
	}

	stable_sort(free_rooms.begin(), free_rooms.end(), fewer_beds);

	for (int i = 0; i < (int)free_rooms.size(); i++) {
		cout << free_rooms[i] << endl;
	}
	return (int)free_rooms.size();
}

int Collection::show_reservations() const {
	for (int i = 0; i < reservations_count(); i++) {
		cout << reservations[i] << endl;
	}
	if (reservations_count() == 0) {
		cout << "No reservations." << endl;
	}
	return reservations_count();
}

int Collection::show_reservations_of_room(int room_number) const {
	int count = 0;
	for (int i = 0; i < reservations_count(); i++) {
		if (reservations[i].get_room_number() == room_number) {
			cout << reservations[i] << endl;
			count++;
		}
	}
	if (count == 0) {
		cout << "No reservations." << endl;
	}
	return count;
}

int Collection::choose_reservation() const {
	if (reservations_count() == 0) {
		cout << "There are no reservations." << endl;
		return -1;
	}

	for (int i = 0; i < reservations_count(); i++) {
		cout << i + 1 << ". " << reservations[i] << endl;
	}
	cout << endl;

	int number;
	while (true) {
		if (!read_number("Choose reservation (0 to go back): ", number) || number == 0) {
			return -1;
		}
		if (number >= 1 && number <= reservations_count()) {
			return number - 1;
		}
		cout << "There is no reservation with number " << number << ". Try again." << endl;
	}
}

MyString Collection::split_field(const MyString& source, int& index, char separator) const {
	int counter = 0;
	int temp = index;
	while (index < source.get_size() && source[index] != separator) {
		counter++;
		index++;
	}
	char* str = new char[counter + 1];
	counter = 0;
	while (temp < source.get_size() && source[temp] != separator) {
		str[counter] = source[temp];
		temp++;
		counter++;
	}
	str[counter] = '\0';
	index++;
	MyString field(str);
	delete[] str;
	return field;
}

bool Collection::read_date(const MyString& text, Date& date) const {
	int i = 0;
	int day = atoi(split_field(text, i, '.').c_str());
	int month = atoi(split_field(text, i, '.').c_str());
	int year = atoi(split_field(text, i, '.').c_str());

	return date.set_year(year) && date.set_month(month) && date.set_day(day);
}

bool Collection::read_one_room(const MyString& line, Room& room) const {
	int i = 0;
	int number = atoi(split_field(line, i, '/').c_str());
	int beds = atoi(split_field(line, i, '/').c_str());
	int closed = atoi(split_field(line, i, '/').c_str());

	if (!room.set_room_number(number) || !room.set_beds_count(beds)) {
		return false;
	}
	room.set_is_closed(closed == 1);
	return true;
}

bool Collection::read_one_reservation(const MyString& line, Reservation& reservation) const {
	int i = 0;
	int number = atoi(split_field(line, i, '/').c_str());
	MyString arrival_text = split_field(line, i, '/');
	MyString leave_text = split_field(line, i, '/');
	MyString name = split_field(line, i, '/');
	MyString info = split_field(line, i, '/');

	Date arrival, leave;
	if (number <= 0 || !read_date(arrival_text, arrival) || !read_date(leave_text, leave) || name.get_size() == 0) {
		return false;
	}

	reservation = Reservation(number, arrival, leave, name, info);
	return true;
}
