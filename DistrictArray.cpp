#include "DistrictArray.h"
#include <iostream>

namespace project1
{
#pragma region Default Constructors

	DistrictArray::DistrictArray(int len)
		: _arr(new District* [len]), _len(0), _size(len)
	{
	}

#pragma endregion

#pragma region Overload operators

	District& DistrictArray::operator[](int idx) const
	{
		if (!(0 <= idx && idx < _len))
		{
			std::cout << "DistrictArray - index is out of range.\nRequested idx: " << idx << "\nArray length:  " << _len << std::endl;
			exit(-1);
		}

		return *_arr[idx];
	}

#pragma endregion

#pragma region Private Methods

	bool DistrictArray::increaseSize(int size)
	{
		District** temp = new District * [size];

		for (int i = 0; i < _len; i++)
			temp[i] = _arr[i];

		delete[] _arr;
		_arr = temp;
		_size = size;

		return true;
	}
#pragma endregion

#pragma region Public Methods

	bool DistrictArray::add(District& dis)
	{
		if (_len == _size)
			increaseSize(_size * 2 + 1);

		_arr[_len] = &dis;
		++_len;

		return true;
	}

	bool DistrictArray::setLength(int newlen)
	{
		if (newlen > _size)
			increaseSize(newlen);
		_len = newlen;

		return true;
	}

	int DistrictArray::indexOf(int ID)
	{
		for (int i = 0; i < this->getLength(); i++)
			if (this->_arr[i]->getID() == ID)
				return i;

		return -1;
	}

#pragma endregion
}