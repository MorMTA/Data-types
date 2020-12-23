#include "RepList.h"
#include <iostream>
using namespace std;

namespace project1
{
#pragma region Default Constructors

	RepList::RepList(District& district, Citizen& civ)
		: _winners(0), _votes(0), _district(district), _arr(1)
	{
		_arr.add(civ);
	}

#pragma endregion

#pragma region Overload Operators

	Citizen& RepList::operator[](int idx) const
	{
		if (!(0 <= idx && idx < _arr.getLength()))
		{
			std::cout << "RepList - index is out of range.\nRequested idx: " << idx << "\nArray length:  " << _arr.getLength() << std::endl;
			exit(-1);
		}

		return _arr[idx];
	}

	std::ostream& operator<<(std::ostream& os, const RepList& block)
	{
		os << "In district: " << block._district.getName() << endl;
		os << block._arr;

		return os;
	}

#pragma endregion
}