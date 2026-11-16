#include "Report.h"

const char REPORT_FILE[] = "data/report.txt";

void Report::run() {
	data.read_all();
	cout << "--Reservations--" << endl;
	data.show_reservations();
	cout << endl;

	Date from, to;
	if (!input_period("From", from, "To", to)) {
		return;
	}

	int period_nights = days_diff(from, to);
	ofstream file(REPORT_FILE);

	cout << endl;
	cout << "Occupied nights from " << from << " to " << to << " (" << period_nights << " nights):" << endl;
	file << "Occupied nights from " << from << " to " << to << " (" << period_nights << " nights):" << endl;

	for (int i = 0; i < data.rooms_count(); i++) {
		int room_number = data[i].get_room_number();

		int nights = 0;
		for (int j = 0; j < data.reservations_count(); j++) {
			if (data.get_reservation(j).get_room_number() == room_number) {
				nights += data.get_reservation(j).nights_in_period(from, to);
			}
		}

		int percent = nights * 100 / period_nights;
		cout << "Room " << room_number << ": " << nights << " (" << percent << "%)" << endl;
		file << "Room " << room_number << ": " << nights << " (" << percent << "%)" << endl;
	}

	file.close();
	cout << endl;
	cout << "Saved to " << REPORT_FILE << endl;
}
