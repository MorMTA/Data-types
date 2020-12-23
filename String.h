#pragma once
#include <iostream>

namespace str
{
	class String
	{
	private:
		char* _arr;
		int _size;
		int _len;

		void increaseSize(int requested_len);
		void setString(const char* str);
		void addString(const char* str, int str_len);
	public:
		const char& getString() const { return *_arr; }
		int getLength() { return _len - 1; } // Without '\0'
		static int Len(const char* str);

		friend std::ostream& operator<<(std::ostream&, const String&);
		const String& operator=(const String&);
		const String& operator=(const char*);
		const String& operator+(const String&);
		const String& operator+(const char*);
		char& operator[](int idx);

		String();
		String(const char* str);
		String(const String&);
		~String() { delete[] _arr; }
	};

	void myMemcpy(char* dest, const char* src, int n);
}