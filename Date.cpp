#include "Date.h"

namespace date
{
	const int Date::days_in_month[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	const int Date::_years_range[2] = { 1900, 2100 };

#pragma region Default Constructors

	Date::Date(int day, Month month, int year)
		: _day(day), _month(month), _year(year)
	{
		validateDate();
	}

	Date::Date()
		: Date(1, Month::January, _years_range[0])
	{
	}

#pragma endregion

#pragma region Overload Operators

	bool Date::operator==(const Date& date) const
	{
		return ((_day == date._day) && (_month == date._month) && (_year == date._year));
	}

	bool Date::operator>(const Date& date) const
	{
		if (_year > date._year)
			return true;
		else if (_year < date._year)
			return false;

		if (_month > date._month)
			return true;
		else if (_month < date._month)
			return false;

		if (_day > date._day)
			return true;
		return false;
	}

	std::ostream& operator<<(std::ostream& os, const Date& date)
	{
		os << date._day << "/" << static_cast<int>(date._month) << "/" << date._year;
		return os;
	}

	std::istream& operator>>(std::istream& ins, Date& date)
	{
		Date* new_date = new Date;
		int d, m, y;
		ins >> d >> m >> y;

		new_date->setDate(d, static_cast<Month>(m), y);
		date = *new_date;

		return ins;
	}

	#pragma endregion

	void Date::validateDate()
	{
		if (!(1 <= _day && _day <= days_in_month[static_cast<int>(_month)]))
			_day = 1;

		if (!(1 <= static_cast<int>(_month) && static_cast<int>(_month) <= 12))
			_month = Month::January;

		if (!(_years_range[0] <= _year && _year <= _years_range[1]))
			_year = _years_range[0];
	}

	bool Date::setDate(int day, Month month, int year)
	{
		bool res;
		res = setDay(day);
		res &= setMonth(month);
		res &= setYear(year);
		return res;
	}

	bool Date::setDay(int day)
	{
		if (!(1 <= static_cast<int>(_month) && static_cast<int>(_month) <= 12))
			return false;

		if (!(1 <= day && day <= days_in_month[static_cast<int>(_month)]))
			return false;

		_day = day;
		return true;
	}

	bool Date::setMonth(Month month)
	{
		if (!(1 <= static_cast<int>(month) && static_cast<int>(month) <= 12))
			return false;

		if (!(1 <= _day && _day <= days_in_month[static_cast<int>(_month)]))
			_day = 1;

		_month = month;
		return true;
	}

	bool Date::setYear(int year)
	{
		if (!(_years_range[0] <= _year && _year <= _years_range[1]))
			return false;

		_year = year;
		return true;
	}
}
