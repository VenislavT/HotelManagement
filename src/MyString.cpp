#include "MyString.h"

MyString::MyString() {
	str = new char[1];
	str[0] = '\0';
	size = 0;
}

MyString::MyString(const char* str) {
	if (str == nullptr) {
		this->str = new char[1];
		this->str[0] = '\0';
		this->size = 0;
	}
	else {
		this->size = (int)strlen(str);
		this->str = new char[size + 1];
		strcpy(this->str, str);
	}
}

MyString::MyString(const MyString& other) {
	copy_from(other);
}

MyString::MyString(MyString&& other) {
	str = other.str;
	size = other.size;

	other.str = new char[1];
	other.str[0] = '\0';
	other.size = 0;
}

MyString& MyString::operator=(const MyString& other) {
	if (this != &other) {
		free();
		copy_from(other);
	}
	return *this;
}

MyString& MyString::operator=(MyString&& other) {
	if (this != &other) {
		free();
		str = other.str;
		size = other.size;

		other.str = new char[1];
		other.str[0] = '\0';
		other.size = 0;
	}
	return *this;
}

MyString::~MyString() {
	free();
}

int MyString::get_size() const {
	return size;
}

const char* MyString::c_str() const {
	return str;
}

char& MyString::operator[] (int index) {
	if (index < 0 || index >= size) {
		throw "Invalid index";
	}
	return str[index];
}

const char& MyString::operator[] (int index) const {
	if (index < 0 || index >= size) {
		throw "Invalid index";
	}
	return str[index];
}

MyString& MyString::operator+=(const MyString& other) {
	char* concat = new char[size + other.size + 1];
	strcpy(concat, str);
	strcat(concat, other.str);
	free();
	str = concat;
	size = size + other.size;
	return *this;
}

istream& operator>>(istream& is, MyString& obj) {
	char buff[1024];
	is.width(1024);
	is >> buff;
	obj = MyString(buff);
	return is;
}

istream& getline(istream& is, MyString& obj) {
	char buff[1024];
	is.getline(buff, 1024);
	obj = MyString(buff);
	return is;
}

ostream& operator<<(ostream& os, const MyString& obj) {
	os << obj.str;
	return os;
}

void MyString::copy_from(const MyString& other) {
	size = other.size;
	str = new char[size + 1];
	strcpy(str, other.str);
}

void MyString::free() {
	delete[] str;
}

MyString operator+(const MyString& lhs, const MyString& rhs) {
	MyString copy(lhs);
	copy += rhs;
	return copy;
}

bool operator==(const MyString& lhs, const MyString& rhs) {
	return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

bool operator!=(const MyString& lhs, const MyString& rhs) {
	return strcmp(lhs.c_str(), rhs.c_str()) != 0;
}

bool operator>(const MyString& lhs, const MyString& rhs) {
	return strcmp(lhs.c_str(), rhs.c_str()) > 0;
}

bool operator<(const MyString& lhs, const MyString& rhs) {
	return strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

bool operator>=(const MyString& lhs, const MyString& rhs) {
	return strcmp(lhs.c_str(), rhs.c_str()) >= 0;
}

bool operator<=(const MyString& lhs, const MyString& rhs) {
	return strcmp(lhs.c_str(), rhs.c_str()) <= 0;
}
