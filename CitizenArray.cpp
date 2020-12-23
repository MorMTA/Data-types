#include "CitizenArray.h"
#include <iostream>
using namespace std;

namespace project1
{
#pragma region Default Constructors

	CitizenArray::CitizenArray(int len)
		: _arr(new Citizen* [len]), _len(0), _size(len)
	{
	}

#pragma endregion

#pragma region Overload Operators

	Citizen& CitizenArray::operator[](int idx) const
	{
		if (!(0 <= idx && idx < _len))
		{
			std::cout << "CitizenArray - index is out of range.\nRequested idx: " << idx << "\nArray length:  " << _len << std::endl;
			exit(-1);
		}

		return *_arr[idx];
	}

	ostream& operator<<(ostream& os, const CitizenArray& arr)
	{
		for (int i = 0; i < arr._len; i++)
			os << *(arr._arr[i]);

		return os;
	}

	const CitizenArray& CitizenArray::operator=(const CitizenArray& other)
	{
		if (this != &other)
		{
			_len = other._len;
			_size = other._size;
			delete[] _arr;
			_arr = new Citizen * [_size];
			for (int i = 0; i < _len; i++)
				_arr[i] = other._arr[i];
		}

		return *this;
	}

#pragma endregion

#pragma region Private Methods

	bool CitizenArray::increaseSize(int size)
	{
		Citizen** temp = new Citizen * [size];

		for (int i = 0; i < _len; i++)
			temp[i] = _arr[i];

		delete[] _arr;
		_arr = temp;
		_size = size;

		return true;
	}

#pragma endregion

#pragma region Public Methods

	bool CitizenArray::add(Citizen& civ)
	{
		if (_len == _size)
			increaseSize(_size * 2 + 1);

		_arr[_len] = &civ;
		++_len;

		return true;
	}

	bool CitizenArray::clear()
	{
		_len = 0;

		return true;
	}

	bool CitizenArray::setLength(int newlen)
	{
		if (newlen > _size)
			increaseSize(newlen);
		_len = newlen;

		return true;
	}

	int CitizenArray::indexOf(int ID)
	{
		for (int i = 0; i < this->getLength(); i++)
			if (this->_arr[i]->getID() == ID)
				return i;

		return -1;
	}

#pragma endregion
}