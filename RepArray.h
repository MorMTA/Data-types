#pragma once
#include "RepList.h"

namespace project1
{
	class RepArray
	{
	private:
		RepList** _arr;
		int _len, _size;
		bool increaseSize(int size);
	public:
		// Getters:
		int getLength() const { return _len; }
		int getVotesAtIndex(int idx) const { return (*_arr)[idx].getVotes(); }

		// Methods:
		bool add(RepList& cit);
		int indexOf(int district_id) const;
		bool setNumOfWinners(int district_id, int num) { return (*_arr)[indexOf(district_id)].setNumOfWinners(num); }
		int getNumOfWinners(int district_id) const { return (*_arr)[indexOf(district_id)].getNumOfWinners(); }

		// Overload operators
		RepList& operator[](int idx) const;

		// Constructors:
		explicit RepArray(int len = 0);
		RepArray(const RepArray&) = delete;
		~RepArray() { delete[] _arr; }
	};
}