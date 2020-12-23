#pragma once
#include <iostream>
#include "CitizenArray.h"
#include "DistrictArray.h"
#include "PartyArray.h"
#include "ElectionRound.h"

using namespace std;

namespace project1
{
	enum class Print
	{
		Districts,
		Citizens,
		Parties
	};

	const int MAX_LEN = 255;

	class Application
	{
	private:
		CitizenArray _citizens;
		PartyArray _parties;
		DistrictArray _districts;
		ElectionRound _election_round;

		bool setDate();
		bool showMenu(int input);
		// 1-4
		bool addCitizen();
		bool addParty();
		bool addDistrict();
		bool addCitizenAsRepresentative();
		// 5-7
		void print(Print val);
		void printDistricts();
		void printParties();
		void printCitizens();
		void printMenu();
		// 8-9
		bool vote();
		bool showElection();
	public:
		void Run();

		Application();
		~Application();
	};
}