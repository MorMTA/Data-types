#include "Party.h"
#include <iostream>
using namespace std;

namespace project1
{
	int Party::_current_id = 0;

	#pragma region Default Constructors

	Party::Party(String Name, Citizen& civ, int votes)
		: _name(Name), _president(civ), _id(++_current_id), _reps(0), _won_districts(0)
	{
	}

	#pragma endregion

	#pragma region Overload Operators

	std::ostream& operator<<(std::ostream& os, const Party& par)
	{
		// Print party details
		os << "Party " << par.getID();
		os << ": " << par._name << endl;

		// print president details
		os << "Party president: " << par._president.getName() << endl;

		// print all the representatives in each district
		if (par._reps.getLength() == 0)
			os << "List of representatives is empty.";

		for (int i = 0; i < par._reps.getLength(); i++)
			os << endl << par._reps[i];

		return os;
	}

	#pragma endregion

	#pragma region Private Methods

	const Citizen& Party::searchPresidentIDinList(int ID) const
	{
		int len = _reps.getLength();

		for (int i = 0; i < len; i++)
		{
			const RepList& cur_list = _reps[i];
			int cur_len = cur_list.getLength();

			for (int j = 0; j < cur_len; j++)
				if (cur_list[j].getID() == ID)
					return cur_list[j];
		}

		std::cout << "Party has to have a president.";
		exit(-2);
	}

	#pragma endregion

	#pragma region Public Methods

	int Party::findDistrictID(int district_id) const
	{
		for (int i = 0; i < _reps.getLength(); i++)
			if (_reps[i].getDistrict().getID() == district_id)
				return i;

		return -1;
	}

	bool Party::addRep(Citizen& civ, District& district)
	{
		int idx = findDistrictID(district.getID());

		if (idx == -1)
		{
			RepList* new_block = new RepList(district, civ);
			_reps.add(*new_block);
		}
		else
			_reps[idx].add(civ);

		return true;
	}

	int Party::getTotalVotes() const
	{
		int total = 0;
		for (int i = 0; i < _reps.getLength(); i++)
			total += _reps[i].getVotes();

		return total;
	}

	int Party::getNumOfRepresentatives() const
	{
		int total = 0;
		for (int i = 0; i < _reps.getLength(); i++)
			total += _reps[i].getLength();

		return total;
	}

	int Party::getNumOfRepsFromDistrict(int district_id) const
	{
		int idx = findDistrictID(district_id);
		if (idx != -1)
			return _reps[idx].getLength();

		return false;
	}

	bool Party::addVote(int district_id)
	{
		int idx = findDistrictID(district_id);
		if (idx != -1)
			return _reps[idx].addVote();

		return false;
	}

	int Party::getVotesAtDistrict(int district_id) const
	{
		int idx = findDistrictID(district_id);
		if (idx != -1)
			return _reps[idx].getVotes();

		return 0;
	}

	Citizen& Party::getRepresentativeByIndex(int idx, int district_id) const
	{
		int district_idx = findDistrictID(district_id);
		RepList& list = _reps[district_idx];
		return list[idx];
	}

	int Party::getTotalWinners() const
	{
		int total = 0;
		for (int i = 0; i < _reps.getLength(); i++)
			total += _reps[i].getNumOfWinners();

		return total;
	}

	#pragma endregion
}