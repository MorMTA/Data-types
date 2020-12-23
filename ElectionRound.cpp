#include "ElectionRound.h"

namespace project1
{
	bool ElectionRound::setDateForElection(Date date)
	{
		int day = date.getDay();
		Month month = date.getMonth();
		int year = date.getYear();

		_day_of_election.setDate(day, month, year);

		return true;
	}

	bool ElectionRound::checkBasicRequirements(DistrictArray& districts, PartyArray& parties)
	{
		if (districts.getLength() == 0)
			return false;

		for (int i = 0; i < districts.getLength(); i++)
		{
			int total = 0;
			int district_id = districts[i].getID();
			int party_size = parties.getLength();

			for (int i = 0; i < party_size; i++)
				total += parties[i].getNumOfRepsFromDistrict(district_id);

			if (districts[i].getNumOfRepresentatives() > total)
			{
				cout << "Not all sits are taken yet! More representativies can be chosen!" << endl << endl;
				return false;
			}
		}

		return true;
	}

	bool ElectionRound::Start(CitizenArray& citizens, DistrictArray& districts, PartyArray& parties)
	{
		if (!checkBasicRequirements(districts, parties))
			return false;

		cout << endl << "Election date: " << _day_of_election << endl;

		// in each district and party calculate and set all the representatives for the election
		for (int i = 0; i < districts.getLength(); i++)
		{
			districts[i].resetRepsList();
			if (districts[i].getTotalVotes() == 0)
			{
				cout << "The people has to vote in each district! No votes no election!" << endl << endl;
				return false;
			}
			calcRepsInDistrict(districts[i], parties);
		}

		// print all the require information for each district
		for (int i = 0; i < districts.getLength(); i++)
			outputForEachDistrict(districts[i], citizens, parties);

		parties.mySort();

		cout << endl << "party's presidents in a descending order:" << endl;
		for (int i = 0; i < parties.getLength(); i++)
			cout << i + 1 << ". " << parties[i].getPresidentName() << endl;
		cout << endl;

		return true;
	}

	// print each district as required
	void ElectionRound::outputForEachDistrict(District& cur_district, CitizenArray& citizens, PartyArray& parties)
	{
		cout << "------------------------------" << endl << endl;

		// Print id, name, num of representatives.
		cout << "District " << cur_district.getID() << ": " << cur_district.getName() << endl;
		cout << "Has " << cur_district.getNumOfRepresentatives() << " representatives" << endl;

		// Print the winner for this district.
		Party& winner_party = calcWinnerInDistrict(cur_district, parties);
		cout << "The winner in this district is " << winner_party.getPresidentName();
		cout << " from " << winner_party.getName() << endl;

		// Print each party details
		for (int i = 0; i < parties.getLength(); i++)
			outputForEachPartyInDistrict(cur_district, parties[i]);

		cout << cur_district.percentageOfVotes() << "% citizens voted" << endl;

		cout << endl << "------------------------------" << endl;
	}

	// Print each party as required for a single district
	void ElectionRound::outputForEachPartyInDistrict(District& cur_district, Party& cur_party)
	{
		int district_id = cur_district.getID();

		if (cur_party.getNumOfWinners(district_id) == 0)
			return;

		cout << endl << "-" << endl;

		// Print all the representatives in this party to this district
		cout << "Representatives from party " << cur_party.getName() << ":" << endl;
		int num_of_winners = cur_party.getNumOfWinners(district_id);
		for (int j = 0; j < num_of_winners; j++)
			cout << cur_party.getRepresentativeByIndex(j, district_id).getName() << endl;

		cout << endl << "Number of voices in the whole district: " << cur_party.getVotesAtDistrict(district_id) << endl;

		// Get the percentage of votes this party got for this district
		int party_votes = cur_party.getVotesAtDistrict(district_id);
		int total_votes = cur_district.getTotalVotes();
		double percentage = (static_cast<int>(static_cast<double>(party_votes) / total_votes * 100));

		// Print every little detail of the party
		cout << "The party got " << percentage << "% of all votes in this district" << endl;
		cout << "The president of this party is: " << cur_party.getPresidentName() << endl;
		cout << "This party got " << cur_party.getTotalVotes() << " votes and has ";
		cout << cur_party.getTotalWinners() << " representatives in the country" << endl;

		cout << "-" << endl << endl;
	}

	// Check who won in this district
	Party& ElectionRound::calcWinnerInDistrict(District& district, PartyArray& parties)
	{
		int district_id = district.getID();
		int total_votes = district.getTotalVotes();
		int max_percentage_party_id = 1;
		int max_percentage = 0;

		for (int j = 0; j < parties.getLength(); j++)
		{
			Party& cur_party = parties[j];

			int cur_party_votes = cur_party.getVotesAtDistrict(district_id);
			int cur_total_votes = total_votes;
			int percentage = static_cast<int>((static_cast<double>(cur_party_votes) / cur_total_votes) * 100);

			if (max_percentage < percentage)
			{
				max_percentage = percentage;
				max_percentage_party_id = cur_party.getID();
			}
			else if (max_percentage == percentage)
			{
				int max_idx = parties.indexOf(max_percentage_party_id);
				if (parties[max_idx].getID() > cur_party.getID())
					max_percentage_party_id = cur_party.getID();
			}
		}

		int winner_idx = parties.indexOf(max_percentage_party_id);
		parties[winner_idx].addWon();
		return parties[winner_idx];
	}

	// Get an ORDER list of all the representatives each party has to give.
	int** ElectionRound::getPartyReps(PartyArray& parties, int total_reps, int total_votes, int district_id)
	{
		int size = parties.getLength();

		int** party_reps = new int* [size];
		int* party_remainders = new int[size];

		int percentage, party_votes, max_idx;
		double ratio;

		// Get total representatives
		for (int i = 0; i < size; i++)
		{
			party_reps[i] = new int[2];
			party_reps[i][0] = i;

			// Get percentage
			party_votes = parties[i].getVotesAtDistrict(district_id);
			ratio = (static_cast<double>(party_votes) / total_votes);
			percentage = static_cast<int>(total_reps * ratio * 100);

			// Do math.. lol
			party_reps[i][1] = percentage / 100;
			total_reps -= percentage / 100;
			party_remainders[i] = percentage % 100;
		}

		// Complete the missing representatives
		for (int i = 0; i < total_reps; i++)
		{
			max_idx = MyMath::max_in_arr(party_remainders, size);
			party_remainders[max_idx] = 0;
			party_reps[max_idx][1] += 1;
		}

		delete[] party_remainders;
		return party_reps;
	}

	// check that every party has enough reps to send. if not, give the option to someone else
	void ElectionRound::setCorrectlyReps(PartyArray& parties, int** party_reps, int district_id)
	{
		int size = parties.getLength();

		// Check if the party has enough reps to give, if not reserve it to other party in winning row.
		int reserved = 0;
		for (int i = 0; i < size; i++)
		{
			int is_enough_reps = party_reps[i][1] - parties[party_reps[i][0]].getNumOfRepsFromDistrict(district_id);
			if (is_enough_reps > 0)
			{
				reserved += is_enough_reps;
				party_reps[i][1] -= is_enough_reps;
			}
		}
		// add the reserved representative by order if there is extra representatives
		for (int i = 0; i < size; i++)
		{
			int cur_reps = party_reps[i][1] - parties[party_reps[i][0]].getNumOfRepsFromDistrict(district_id);
			if (cur_reps < 0)
			{
				party_reps[i][1] -= cur_reps;
				reserved += cur_reps;
			}
		}
	}

	// set from each party number of representatives as required
	void ElectionRound::calcRepsInDistrict(District& cur_district, PartyArray& parties) 
	{
		int district_id = cur_district.getID();
		int size = parties.getLength();

		// each cell has 2 values: first - index of party pos in array, second - num of reps
		int total_reps = cur_district.getNumOfRepresentatives();
		int total_votes = cur_district.getTotalVotes();

		int** party_reps = getPartyReps(parties, total_reps, total_votes, district_id);

		setCorrectlyReps(parties, party_reps, district_id);

		// Set representatives in district
		for (int i = 0; i < size; i++)
		{
			parties[party_reps[i][0]].setNumOfWinners(district_id, party_reps[i][1]);

			for (int k = 0; k < party_reps[i][1]; k++)
			{
				Citizen& cur = parties[party_reps[i][0]].getRepresentativeByIndex(k, district_id);
				cur_district.addRepresentative(cur);
			}
		}

		for (int i = 0; i < size; i++)
			delete[] party_reps[i];
		delete[] party_reps;
	}
}