#include "Application.h"
#include "Checks.h"
#include "myMath.h"
using namespace myMath;

namespace project1
{
	#pragma region Default Constructors

	Application::Application()
		: _citizens(), _parties(), _districts(), _election_round()
	{
	}

	Application::~Application()
	{
		// Delete all the content inside the dynamic arrays
		_citizens.Dispose();
		_districts.Dispose();
		_parties.Dispose();
	}

	#pragma endregion

	#pragma region Public Methods

	void Application::Run()
	{
		bool isRunning = true;
		int input;

		setDate();

		while (isRunning)
		{
			printMenu();

			cin >> input;

			isRunning = showMenu(input);
		}
	}

	#pragma endregion

	#pragma region Private Methods

	#pragma region Menu

	bool Application::setDate()
	{
		cout << "What a beautiful day to elect!" << endl;
		cout << "Enter date for the election (dd mm yyyy): ";
		Date temp;
		cin >> temp;
		return _election_round.setDateForElection(temp);
	}

	void Application::printMenu()
	{
		cout << "Please enter a number between 1 to 10" << endl;
		cout << "1. Add a district" << endl;
		cout << "2. Add a citizen" << endl;
		cout << "3. Add a party" << endl;
		cout << "4. Add a citizen as a representative" << endl;
		cout << "5. Present all districts" << endl;
		cout << "6. Present all citizens" << endl;
		cout << "7. Present all parties" << endl;
		cout << "8. Vote! it is your democratic right!" << endl;
		cout << "9. Present election results" << endl;
		cout << "10. Exit" << endl;
	}

	bool Application::showMenu(int input)
	{
		bool res = true;

		switch (input)
		{
		case 1:
			addDistrict();
			break;
		case 2:
			addCitizen();
			break;
		case 3:
			addParty();
			break;
		case 4:
			addCitizenAsRepresentative();
			break;
		case 5:
			print(Print::Districts);
			break;
		case 6:
			print(Print::Citizens);
			break;
		case 7:
			print(Print::Parties);
			break;
		case 8:
			vote();
			break;
		case 9:
			showElection();
			break;
		case 10:
			cout << "Exit" << endl;
			res = false;
			break;
		default:
			break;
		}

		return res;
	}

	#pragma endregion

	#pragma region Add Methods

	bool Application::addDistrict()
	{
		// Getting input
		char name[MAX_LEN];
		int size;
		cout << "Enter name: ";
		cin >> name;
		cout << "Enter num of representatives: ";
		cin >> size;

		// Add new district
		District* d = new District(name, size);
		_districts.add(*d);

		cout << "New District added!" << endl << endl;
		return true;
	}

	bool Application::addCitizen()
	{
		// Getting input
		char name[MAX_LEN];
		int citizen_id, district_id;
		Date birthDate;
		cout << "Enter name: ";
		cin >> name;
		cout << "Enter ID: ";
		cin >> citizen_id;
		cout << "Enter Birth date (dd mm yyyy): ";
		cin >> birthDate;
		cout << "Enter district ID: ";
		cin >> district_id;

		// Checking validity
		int district_idx = _districts.indexOf(district_id);
		int citizen_idx = _citizens.indexOf(citizen_id);

		bool valid = Checks::check_input_of_new_citizen(citizen_idx, district_idx);
		if (!valid)
			return false;

		// Add new citizen
		District& citizen_district = _districts[district_idx];
		Citizen* new_citizen = new Citizen(name, citizen_id, birthDate, citizen_district);

		_citizens.add(*new_citizen);
		citizen_district.addCitizen(*new_citizen);

		cout << "New Citizen added!" << endl << endl;
		return true;
	}

	bool Application::addParty()
	{
		// Getting input
		char name[MAX_LEN];
		int president_id;
		cout << "Enter name: ";
		cin >> name;
		cout << "Enter president ID: ";
		cin >> president_id;

		// Checking validity
		int citizen_idx = this->_citizens.indexOf(president_id);

		bool valid = Checks::check_input_of_new_party(citizen_idx, _citizens, _districts);
		if (!valid)
			return false;

		// Add new Party
		Party* party = new Party(name, _citizens[citizen_idx]);

		_parties.add(*party);

		cout << "New Party added!" << endl << endl;
		return true;
	}

	bool Application::addCitizenAsRepresentative()
	{
		// Getting input
		int citizen_id, party_id, district_id;
		cout << "Enter citizen ID: ";
		cin >> citizen_id;
		cout << "Enter party ID: ";
		cin >> party_id;
		cout << "Enter district ID: ";
		cin >> district_id;

		// Checking validity
		int citizen_idx = _citizens.indexOf(citizen_id);
		int party_idx = _parties.indexOf(party_id);
		int district_idx = _districts.indexOf(district_id);

		bool valid = Checks::check_input_of_new_rep(citizen_idx, party_idx, district_idx, _citizens);
		if (!valid)
			return false;

		// Add citizen as representative to party
		_parties[party_idx].addRep(_citizens[citizen_idx], _districts[district_idx]);
		_citizens[citizen_idx].setRepStatus(true);


		cout << "Representative added to the list!" << endl << endl;
		return true;
	}

	#pragma endregion

	#pragma region Prints Methods

	void Application::print(Print val)
	{
		const char* frame = "********************";

		cout << endl << frame << endl << endl;

		if (val == Print::Citizens)
			printCitizens();
		else if (val == Print::Districts)
			printDistricts();
		else
			printParties();

		cout << frame << endl << endl;
	}

	void Application::printDistricts()
	{
		if (_districts.getLength() == 0)
			cout << "No districts were found!" << endl;

		for (int i = 0; i < _districts.getLength(); i++)
			cout << _districts[i] << endl;
	}

	void Application::printCitizens()
	{
		if (_citizens.getLength() == 0)
			cout << "No citizens were found!" << endl;

		for (int i = 0; i < this->_citizens.getLength(); i++)
		{
			cout << _citizens[i];
			cout << "Citizen district: " << _citizens[i].getDistrict().getName() << endl << endl;
		}
	}

	void Application::printParties()
	{
		if (_parties.getLength() == 0)
			cout << "No parties were found!" << endl;

		for (int i = 0; i < _parties.getLength(); i++)
			cout << _parties[i] << endl << endl;
	}

	#pragma endregion

	bool Application::vote()
	{
		// Getting input
		int citizen_id, party_id;
		cout << "Enter citizen ID: ";
		cin >> citizen_id;
		cout << "Enter party ID you want to vote for: ";
		cin >> party_id;
		cout << endl;

		// Checking validity
		int citizen_idx = _citizens.indexOf(citizen_id);
		int party_idx = _parties.indexOf(party_id);

		bool valid = Checks::check_input_of_vote(citizen_idx, party_idx, _citizens, _parties);
		if (!valid)
			return false;

		// Make the vote count
		Citizen& civ = _citizens[citizen_idx];
		Party& party = _parties[party_idx];
		District& district = civ.getDistrict();

		civ.setRight(false);
		party.addVote(district.getID());
		district.addVote();

		cout << "You, citizen id: " << citizen_id;
		cout << " successfully voted to the party: " << party.getName() << endl;
		cout << "Thank you for using your democratic right good citizen!" << endl << endl;

		return true;
	}

	bool Application::showElection()
	{
		_election_round.Start(_citizens, _districts, _parties);
		return true;
	}

	#pragma endregion
}