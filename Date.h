#pragma once
#include <iostream>

namespace date
{
	enum class Month
	{
		January = 1,
		February,
		March,
		April,
		May,
		June,
		July,
		August,
		September,
		October,
		November,
		December
	};

	class Date
	{
	private:
		static const int _years_range[2];
		int _day, _year;
		Month _month;
		void validateDate();
	public:
		static const int days_in_month[12];
		int getDay() { return _day; }
		bool setDay(int day);
		Month getMonth() { return _month; }
		bool setMonth(Month month);
		int getYear() { return _year; }
		bool setYear(int year);

		bool setDate(int day, Month month, int year);

		bool operator==(const Date& date) const;
		bool operator!=(const Date& date) const { return !(*this == date); }
		bool operator>(const Date& date) const;
		bool operator>=(const Date& date) const { return ((*this > date) || (*this == date)); }
		bool operator<(const Date& date) const { return !(*this >= date); }
		bool operator<=(const Date& date) const { return !(*this < date); }
		friend std::ostream& operator<<(std::ostream&, const Date&);
		friend std::istream& operator>>(std::istream&, Date&);

		Date();
		Date(int day, Month month, int year);
	};
}