#include "Find_room.h"
#include "Input.h"

void Find_room::run() {
	data.read_all();
	cout << "--Rooms--" << endl;
	data.show_rooms();
	cout << endl;
	cout << "--Reservations--" << endl;
	data.show_reservations();
	cout << endl;

	int guests;
	while (true) {
		if (!read_number("Number of guests: ", guests)) {
			return;
		}
		if (guests > 0) {
			break;
		}
		cout << "There must be at least 1 guest." << endl;
	}
	cout << endl;

	Date from, to;
	if (!input_period("Arrival", from, "Departure", to)) {
		return;
	}

	cout << endl;
	cout << "Rooms for " << guests << " from " << from << " to " << to << " (best match first):" << endl;
	if (data.show_free_rooms(from, to, guests) == 0) {
		cout << "No suitable rooms." << endl;
	}
}
