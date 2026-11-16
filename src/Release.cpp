#include "Release.h"

void Release::run() {
	data.read_all();

	cout << "Which reservation to release?" << endl;
	int index = data.choose_reservation();
	if (index == -1) {
		return;
	}

	cout << endl;
	cout << "Released: " << data.get_reservation(index) << endl;
	data.remove_reservation(index);
	data.save_reservations();
}
