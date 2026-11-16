#include "Interface.h"
#include "Input.h"
#include <cstdlib>

void Interface::run() {
	while (true) {
		system("cls");
		cout << "-------- Hotel --------" << endl;
		cout << "1. Register guest" << endl;
		cout << "2. Available rooms (free rooms in a period)" << endl;
		cout << "3. Find room (free rooms for a number of guests)" << endl;
		cout << "4. Release room (check out or cancel a reservation)" << endl;
		cout << "5. Report (occupied nights per room in a period)" << endl;
		cout << "6. Close or open room (for repair or cleaning)" << endl;
		cout << "0. Exit" << endl;
		cout << "-----------------------" << endl;

		MyString choice;
		read_line("Choose an option: ", choice);
		while (choice.get_size() != 1 || choice[0] < '0' || choice[0] > '6') {
			read_line("Wrong option! Choose again: ", choice);
		}

		if (choice == "0") {
			cout << endl;
			cout << "Goodbye!" << endl;
			break;
		}

		system("cls");
		cout << "(type /back at any prompt to return to the menu)" << endl;
		cout << endl;

		if (choice == "1") {
			cout << "|Register guest|" << endl;
			Registration operation;
			operation.run();
		}
		else if (choice == "2") {
			cout << "|Available rooms|" << endl;
			Available_rooms operation;
			operation.run();
		}
		else if (choice == "3") {
			cout << "|Find room|" << endl;
			Find_room operation;
			operation.run();
		}
		else if (choice == "4") {
			cout << "|Release room|" << endl;
			Release operation;
			operation.run();
		}
		else if (choice == "5") {
			cout << "|Report|" << endl;
			Report operation;
			operation.run();
		}
		else if (choice == "6") {
			cout << "|Close or open room|" << endl;
			Close_room operation;
			operation.run();
		}

		cout << endl;
		system("pause");
	}
}
