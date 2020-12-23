#pragma once
#include "Party.h"
#include <iostream>

namespace project1
{
	class PartyArray
	{
	private:
		Party** _arr;
		int _len, _size;
		bool increaseSize(int size);
	public:
		// Getters:
		int getLength() const { return _len; }

		// Setters:
		bool setLength(int size);

		// Methods:
		bool add(Party& par);
		int indexOf(int id);
		void mySort();

		// Overload operators
		Party& operator[](int idx) const;

		// Constructors:
		explicit PartyArray(int len = 0);
		PartyArray(const PartyArray&) = delete;

		// Close application method
		void Dispose() {
			for (int i = 0; i < _len; i++)
				delete _arr[i];
			delete[] _arr;
		}
	};
}