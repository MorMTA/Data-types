#include "Citizen.h"
#include <iostream>
using namespace std;
using namespace str;
using namespace date;

namespace project1
{
	Citizen::Citizen(String Name, int ID, Date DayOfBirth, District& District, bool right)
		: _is_representative(false) , _name(Name), _id(ID), _dayOfBirth(DayOfBirth), _district(District), _right(right)
	{
	}

	std::ostream& operator<<(std::ostream& os, const Citizen& cit)
	{
		os << "Citizen name: " << cit._name << endl;
		os << "Citizen ID: " << cit._id << endl;
		os << "Citizen date of birth: " << cit._dayOfBirth << endl;
		//os << "Citizen district: " << cit._district << endl;

		return os;
	}
}