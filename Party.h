#pragma once
#include "String.h"
#include "RepArray.h"

using namespace str;

namespace project1
{
	class Party
	{
	private:
		static int _current_id;

		String _name;
		int _id;
		Citizen& _president;
		RepArray _reps;
		int _won_districts; // count wons

		const Citizen& searchPresidentIDinList(int ID) const;
	public:
		// Getters:
		const String& getName() const { return this->_name; }
		const String& getPresidentName() const { return _president.getName(); }
		int getID() const { return this->_id; }
		int getNumOfRepresentatives() const ;
		int getNumOfRepsFromDistrict(int district_id) const;
		Citizen& getRepresentativeByIndex(int idx, int district_id) const;
		int getVotesAtDistrict(int district_id) const;
		int getTotalVotes() const;
		int getNumOfWinners(int district_id) const { return _reps.getNumOfWinners(district_id); }
		int getTotalWinners() const;
		int getDistrictsWons() const { return _won_districts; }

		// Setters:
		bool setName(String name) { this->_name = name; return true; }
		bool setNumOfWinners(int district_id, int num) { return _reps.setNumOfWinners(district_id, num); }

		// Methods:
		bool addRep(Citizen& civ, District& district);
		bool addVote(int district_id);
		bool addWon() { ++_won_districts; return true; }
		int findDistrictID(int district_id) const;

		// Overload Operators:
		Party& operator=(const Party&) = delete;
		friend std::ostream& operator<<(std::ostream&, const Party&);

		// Constructors:
		Party(String Name, Citizen& civ, int votes = 0);
		Party(const Party&) = delete;
		~Party() {}
	};
}