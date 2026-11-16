#include "Close_room.h"
#include "Input.h"

void Close_room::run() {
	data.read_all();
	cout << "--Rooms--" << endl;
	data.show_rooms();
	cout << endl;

	int room_number, index;
	while (true) {
		if (!read_number("Room to close or open: ", room_number)) {
			return;
		}
		index = data.find_room_index(room_number);
		if (index != -1) {
			break;
		}
		cout << "Room " << room_number << " does not exist." << endl;
	}

	bool now_closed = !data[index].get_is_closed();
	data[index].set_is_closed(now_closed);
	data.save_rooms();

	cout << endl;
	if (now_closed) {
		cout << "Room " << room_number << " is closed. New guests can not be registered in it." << endl;
		cout << "Its reservations stay:" << endl;
		data.show_reservations_of_room(room_number);
	}
	else {
		cout << "Room " << room_number << " is open again." << endl;
	}
}
