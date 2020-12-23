#include "District.h"
#include <iostream>

using namespace std;
namespace project1
{
	int District::_current_id = 0;

	#pragma region Default Constructor

	District::District(String name, int num_of_represents)
		: _name(name), _num_of_representatives(num_of_represents), _citizens(), _id(++_current_id), _total_votes(0)
	{
	}

	#pragma endregion

	#pragma region Overload Operators

	bool District::operator==(const District& dst) const
	{
		return _id == dst._id;
	}

	std::ostream& operator<<(std::ostream& os, const District& dis)
	{
		os << "District ID: " << dis._id << endl;
		os << "District name: " << dis._name << endl;
		os << "Number of representatives: " << dis._num_of_representatives << endl;
		return os;
	}

	#pragma endregion
}