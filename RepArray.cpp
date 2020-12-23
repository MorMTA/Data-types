#include "RepArray.h"
#include <iostream>

namespace project1
{
#pragma region Default Constructors

	RepArray::RepArray(int len)
		: _arr(new RepList*[len]), _len(0), _size(len)
	{
	}

#pragma endregion

#pragma region Overload Operators

	RepList& RepArray::operator[](int idx) const
	{
		if (!(0 <= idx && idx < _len))
		{
			std::cout << "RepArr - index is out of range.\nRequested idx: " << idx << "\nArray length:  " << _len << std::endl;
			exit(-1);
		}

		return *_arr[idx];
	}

#pragma endregion

#pragma region Private Methods

	bool RepArray::increaseSize(int size)
	{
		auto temp = new RepList*[size];

		for (int i = 0; i < _len; i++)
			temp[i] = _arr[i];

		delete[] _arr;
		_arr = temp;
		_size = size;

		return true;
	}

#pragma endregion

#pragma region Public Methods

	bool RepArray::add(RepList& cit)
	{
		if (_len == _size)
			increaseSize(_size * 2 + 1);

		_arr[_len] = &cit;
		++_len;

		return true;
	}

	int RepArray::indexOf(int district_id) const
	{
		for (int i = 0; i < _len; i++)
			if (_arr[i]->getDistrict().getID() == district_id)
				return i;

		return -1;
	}

#pragma endregion
}