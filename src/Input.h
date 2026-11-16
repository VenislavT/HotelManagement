#pragma once
#include "MyString.h"


bool read_line(const char* prompt, MyString& text);

bool read_number(const char* prompt, int& number);

bool read_text(const char* prompt, MyString& text, bool can_be_empty);
