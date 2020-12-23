#pragma once
#include "CitizenArray.h"
#include "District.h"
#include <iostream>

namespace project1
{
	class RepList
	{
	private:
		District& _district;
		int _votes;
		int _winners;
		CitizenArray _arr;
	public:
		// Getters:
		int getLength() const { return _arr.getLength(); }
		District& getDistrict() const { return _district; }
		int getVotes() const { return _votes; }
		int getNumOfWinners() const { return _winners; }

		// Public Methods
		bool add(Citizen& civ) { return _arr.add(civ); }
		bool addVote() { _votes++; return true; }
		bool setNumOfWinners(int num) { _winners = num; return true; }

		// Overload Operators
		Citizen& operator[](int idx) const;
		friend std::ostream& operator<<(std::ostream&, const RepList&);

		// Constructors
		RepList(District& district, Citizen& civ);
	};
}