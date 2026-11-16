#include "Input.h"
#include <cstdlib>

bool read_line(const char* prompt, MyString& text) {
	cout << prompt;
	getline(cin, text);
	return text != "/back";
}

bool is_number(const MyString& text) {
	if (text.get_size() == 0 || text.get_size() > 9) {
		return false;
	}
	for (int i = 0; i < text.get_size(); i++) {
		if (text[i] < '0' || text[i] > '9') {
			return false;
		}
	}
	return true;
}

bool read_number(const char* prompt, int& number) {
	MyString text;
	while (true) {
		if (!read_line(prompt, text)) {
			return false;
		}
		if (is_number(text)) {
			number = atoi(text.c_str());
			return true;
		}
		cout << "Please enter a number." << endl;
	}
}

bool has_slash(const MyString& text) {
	for (int i = 0; i < text.get_size(); i++) {
		if (text[i] == '/') {
			return true;
		}
	}
	return false;
}

bool read_text(const char* prompt, MyString& text, bool can_be_empty) {
	while (true) {
		if (!read_line(prompt, text)) {
			return false;
		}
		if (has_slash(text)) {
			cout << "The symbol / is not allowed. Try again." << endl;
		}
		else if (text.get_size() == 0 && !can_be_empty) {
			cout << "This field can not be empty. Try again." << endl;
		}
		else {
			if (text.get_size() == 0) {
				text = "-";
			}
			return true;
		}
	}
}
