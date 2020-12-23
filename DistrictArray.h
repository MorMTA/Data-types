#pragma once
#include "District.h"

namespace project1
{
	class DistrictArray
	{
	private:
		District** _arr;
		int _len, _size;
		bool increaseSize(int size);
	public:
		// Getters:
		int getLength() const { return _len; }

		// Setters:
		bool setLength(int size);

		// Methods:
		bool add(District& dis);
		int indexOf(int ID);

		// Overload operators
		District& operator[](int idx) const;

		// Constructors:
		explicit DistrictArray(int len = 0);
		DistrictArray(const DistrictArray&) = delete;

		// Close application method
		void Dispose() {
			for (int i = 0; i < _len; i++)
				delete _arr[i];
			delete[] _arr;
		}
	};
}