#pragma once
#include "CitizenArray.h"
#include "PartyArray.h"
#include "DistrictArray.h"

namespace project1
{
	class Checks
	{
	private:
	public:
		static bool check_input_of_new_citizen(int citizen_idx, int district_idx);
		static bool check_input_of_new_party(int citizen_idx, CitizenArray& citizen_array, DistrictArray& district_array);
		static bool check_input_of_new_rep(int citizen_idx, int party_idx, int district_idx, CitizenArray& citizen_array);
		static bool check_input_of_vote(int citizen_idx, int party_idx, CitizenArray& citizen_array, PartyArray& party_array);
	};
}