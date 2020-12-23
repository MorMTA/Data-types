#include "PartyArray.h"
#include <iostream>
#include <algorithm>

namespace project1
{
	static int PartyCmp(const void* ap, const void* bp);

	PartyArray::PartyArray(int len)
		: _arr(new Party* [len]), _len(0), _size(len)
	{
	}

	Party& PartyArray::operator[](int idx) const
	{
		if (!(0 <= idx && idx < _len))
		{
			std::cout << "PartyArray - index is out of range.\nRequested idx: " << idx << "\nArray length:  " << _len << std::endl;
			exit(-1);
		}

		return *_arr[idx];
	}

	bool PartyArray::increaseSize(int size)
	{
		Party** temp = new Party * [size];

		for (int i = 0; i < _len; i++)
			temp[i] = _arr[i];

		delete[] _arr;
		_arr = temp;
		_size = size;

		return true;
	}

	bool PartyArray::add(Party& par)
	{
		if (_len == _size)
			increaseSize(_size * 2 + 1);

		_arr[_len] = &par;
		++_len;

		return true;
	}

	bool PartyArray::setLength(int newlen)
	{
		if (newlen > _size)
			increaseSize(newlen);
		_len = newlen;

		return true;
	}

	int PartyArray::indexOf(int id)
	{
		for (int i = 0; i < this->getLength(); i++)
		{
			if (this->_arr[i]->getID() == id)
				return i;
		}
		return -1;
	}

	void PartyArray::mySort()
	{
		qsort(_arr, _len, sizeof(Party*), PartyCmp);
	}

	int PartyCmp(const void* ap, const void* bp)
	{
		Party** a = (Party**)ap;
		Party** b = (Party**)bp;

		return ((*b)->getDistrictsWons() - (*a)->getDistrictsWons());
	}
}