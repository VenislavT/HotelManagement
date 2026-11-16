#include "Available_rooms.h"

void Available_rooms::run() {
	data.read_all();
	cout << "--Rooms--" << endl;
	data.show_rooms();
	cout << endl;
	cout << "--Reservations--" << endl;
	data.show_reservations();
	cout << endl;

	Date from, to;
	if (!input_period("From", from, "To", to)) {
		return;
	}

	cout << endl;
	cout << "Free rooms from " << from << " to " << to << ":" << endl;
	if (data.show_free_rooms(from, to, 1) == 0) {
		cout << "No free rooms." << endl;
	}
}
