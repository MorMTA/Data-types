#pragma once
#include "CitizenArray.h"
#include "DistrictArray.h"
#include "PartyArray.h"
#include "Date.h"
#include "myMath.h"
#include <iostream>
using namespace date;
using namespace myMath;
using namespace std;

namespace project1
{
	class ElectionRound
	{
	private:
		Date _day_of_election;
		void outputForEachDistrict(District& cur_district, CitizenArray& citizens, PartyArray& parties);
		void outputForEachPartyInDistrict(District& district, Party& party);
		Party& calcWinnerInDistrict(District& cur_district, PartyArray& parties);
		bool checkBasicRequirements(DistrictArray& districts, PartyArray& parties);

		void calcRepsInDistrict(District& cur_district, PartyArray& parties);
		int** getPartyReps(PartyArray& parties, int total_reps, int total_votes, int district_id);
		void setCorrectlyReps(PartyArray& parties, int** party_reps, int district_id);
	public:
		bool setDateForElection(Date date);
		bool Start(CitizenArray& citizens, DistrictArray& districts, PartyArray& parties);

		ElectionRound() : _day_of_election() {};
	};
}