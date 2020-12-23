#include "Checks.h"
#include <iostream>
using namespace std;

namespace project1
{
	bool Checks::check_input_of_new_citizen(int citizen_idx, int district_idx)
	{
		if (district_idx == -1)
		{
			cout << "No district was found by this district id!" << endl << endl;
			return false;
		}
		if (citizen_idx != -1)
		{
			cout << "Citizen exists already!" << endl << endl;
			return false;
		}

		return true;
	}

	bool Checks::check_input_of_new_party(int citizen_idx, CitizenArray& citizen_array, DistrictArray& district_array)
	{
		if (citizen_idx == -1)
		{
			cout << "Party's president doesnt exist!" << endl << endl;
			return false;
		}

		Citizen& civ = citizen_array[citizen_idx];
		int district_id = civ.getDistrict().getID();

		if (district_id == -1)
		{
			cout << "There is no such a district.";
			return false;
		}
		if (civ.getRepStatus() == true)
		{
			cout << "This citizen already a representative!" << endl << endl;
			return false;
		}

		return true;
	}

	bool Checks::check_input_of_new_rep(int citizen_idx, int party_idx, int district_idx, CitizenArray& citizen_array)
	{
		if (citizen_idx == -1)
		{
			cout << "No such citizen exists!" << endl << endl;
			return false;
		}
		if (party_idx == -1)
		{
			cout << "No such party exists!" << endl << endl;
			return false;
		}
		if (district_idx == -1)
		{
			cout << "No such district exists!" << endl << endl;
			return false;
		}
		if (citizen_array[citizen_idx].getRepStatus() == true)
		{
			cout << "This citizen already a representative!" << endl << endl;
			return false;
		}

		return true;
	}

	bool Checks::check_input_of_vote(int citizen_idx, int party_idx, CitizenArray& citizen_array, PartyArray& party_array)
	{
		if (citizen_idx == -1)
		{
			cout << "No such citizen exists!" << endl << endl;
			return false;
		}
		if (party_idx == -1)
		{
			cout << "No such party exists!" << endl << endl;
			return false;
		}

		Citizen& citizen = citizen_array[citizen_idx];
		Party& party = party_array[party_idx];
		int party_district_idx = party.findDistrictID(citizen.getDistrict().getID());

		if (citizen.getRight() == false)
		{
			cout << "This citizen has no voting right!" << endl << endl;
			return false;
		}
		if (party_district_idx == -1)
		{
			cout << "No representatives to this citizen's district." << endl << endl;
			return false;
		}

		return true;
	}
}