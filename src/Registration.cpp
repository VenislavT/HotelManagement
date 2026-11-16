#include "Registration.h"
#include "Input.h"

void Registration::run() {
	data.read_all();
	cout << "--Rooms--" << endl;
	data.show_rooms();
	cout << endl;

	int room_number;
	while (true) {
		if (!read_number("Enter room number: ", room_number)) {
			return;
		}
		int index = data.find_room_index(room_number);
		if (index == -1) {
			cout << "Room " << room_number << " does not exist." << endl;
		}
		else if (data[index].get_is_closed()) {
			cout << "Room " << room_number << " is closed for repair or cleaning." << endl;
		}
		else {
			break;
		}
	}
	cout << endl;

	cout << "--Reservations of room " << room_number << "--" << endl;
	data.show_reservations_of_room(room_number);
	cout << endl;

	Date arrival, leave;
	while (true) {
		if (!input_period("Arrival", arrival, "Departure", leave)) {
			return;
		}

		int conflict = data.conflicting_reservation(room_number, arrival, leave);
		if (conflict == -1) {
			break;
		}
		cout << endl;
		cout << "The room is taken: " << data.get_reservation(conflict) << endl;
		cout << "Choose other dates." << endl;
		cout << endl;
	}
	cout << endl;

	MyString name, additional_info;
	if (!read_text("Name of guest: ", name, false)) {
		return;
	}
	if (!read_text("Additional info (Enter to skip): ", additional_info, true)) {
		return;
	}

	Reservation reservation(room_number, arrival, leave, name, additional_info);
	data.add_reservation(reservation);
	data.save_reservations();

	cout << endl;
	cout << "Registered: " << reservation << endl;
}
