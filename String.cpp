#include "String.h"
#include <iostream>

namespace str
{
	#pragma region Default Constructors

	String::String()
		: String("")
	{
	}

	String::String(const char* str)
		: _arr(nullptr), _size(0), _len(0)
	{
		setString(str);
	}

	// Copy constructor
	String::String(const String& str)
		: _len(str._len), _size(str._size)
	{
		_arr = new char[_size];
		myMemcpy(_arr, str._arr, _size * sizeof(char));
	}

	#pragma endregion

	#pragma region Overload Operators

	std::ostream& operator<<(std::ostream& os, const String& str)
	{
		os << str._arr;
		return os;
	}

	const String& String::operator=(const String& str)
	{
		setString(str._arr);
		return *this;
	}

	const String& String::operator=(const char* str)
	{
		setString(str);
		return *this;
	}

	const String& String::operator+(const String& str)
	{
		addString(str._arr, str._len);
		return *this;
	}

	const String& String::operator+(const char* str)
	{
		addString(str, Len(str));
		return *this;
	}

	char& String::operator[](int idx)
	{
		if (0 <= idx && idx < _len)
			return _arr[idx];

		std::cout << "Index is out of range.";
		exit(-2);
	}

	#pragma endregion

	#pragma region Private Methods

	void String::increaseSize(int requested_len)
	{
		char* temp = _arr;
		_arr = new char[requested_len];

		if (temp != nullptr)
			myMemcpy(_arr, temp, (_len) * sizeof(char));

		_size = requested_len;
		_len = requested_len;

		delete[] temp;
	}

	void String::setString(const char* str)
	{
		int str_len = Len(str);

		if (_size <= str_len + 1)
			increaseSize(str_len + 1);

		myMemcpy(_arr, str, str_len * sizeof(char));
		_arr[str_len] = '\0';
	}

	void String::addString(const char* str, int str_len)
	{
		int len = _len + str_len - 1;
		int temp_len = _len;

		char* temp = _arr;

		if (_size <= len + 1)
			increaseSize(len + 1);

		myMemcpy(_arr + temp_len - 1, str, str_len * sizeof(char));
		_arr[len] = '\0';
	}

	#pragma endregion

	#pragma region Public Functions

	int String::Len(const char* str)
	{
		int i;
		for (i = 0; str[i] != '\0'; i++)
			;
		return i;
	}

	void myMemcpy(char* dest, const char* src, int n)
	{
		for (int i = 0; i < n; i++)
			dest[i] = src[i];
	}

	#pragma endregion
}