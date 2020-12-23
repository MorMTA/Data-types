#pragma once
#include "String.h"
#include "Date.h"

using namespace str;
using namespace date;

namespace project1
{
	class District;

	class Citizen
	{
	private:
		String _name;
		const int _id;
		Date _dayOfBirth;
		District& _district;
		bool _right;
		bool _is_representative;

	public:
		// Getters:
		const String& getName() const { return this->_name; }
		int getID() const { return this->_id; }
		const Date& GetDayOfBirth() const { return this->_dayOfBirth; }
		District& getDistrict() const { return this->_district; }
		bool getRight() const { return this->_right; }
		bool getRepStatus() const { return _is_representative; }

		// Setters:
		bool setName(String name) { this->_name = name; return true; }
		bool setRight(bool right) { this->_right = right; return true; }
		bool setRepStatus(bool val) { _is_representative = val; return true; }

		// Overload operators:
		Citizen& operator=(const Citizen&) = delete;
		friend std::ostream& operator<<(std::ostream&, const Citizen&);

		// Constructors
		Citizen(String Name, int ID, Date DayOfBirth, District& District, bool right=true);
		Citizen(const Citizen&) = delete;
		~Citizen() {}
	};
}