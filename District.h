#pragma once
#include "String.h"
#include "Date.h"
#include "CitizenArray.h"
using namespace str;
using namespace date;

namespace project1
{
	class District
	{
	private:
		static int _current_id;

		String _name;
		const int _id;
		CitizenArray _citizens;
		int _total_votes;
		int _num_of_representatives;
		CitizenArray _representatives;

	public:
		// Getters:
		const String& getName() const { return _name; }
		int getID() const { return _id; }
		int getNumOfRepresentatives() const { return _num_of_representatives; }
		int getNumOfCitizens() const { return _citizens.getLength(); }
		int getTotalVotes() const { return _total_votes; }

		// Setters:
		bool setName(String name) { _name = name; }

		// Methods:
		bool addCitizen(Citizen& civ) { _citizens.add(civ); return true; }
		bool addVote() { ++_total_votes; return true; }
		bool addRepresentative(Citizen& civ) { return _representatives.add(civ); }
		double percentageOfVotes() const { return (static_cast<double>(_total_votes) / _citizens.getLength()) * 100; }
		bool resetRepsList() { return _representatives.clear(); }

		// Overload operators:
		bool operator==(const District&) const;
		District& operator=(const District&) = delete;
		friend std::ostream& operator<<(std::ostream&, const District&);

		// Constructors:
		District(String name, int num_of_represents);
		District(const District&) = delete;
		~District() {}

		// Close application method
		void Dispose() {
			_citizens.Dispose();
			_representatives.Dispose();
		}
	};
}