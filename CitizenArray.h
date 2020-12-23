#pragma once
#include "Citizen.h"


namespace project1
{
	class Exceptions;

	class CitizenArray
	{
	private:
		Citizen** _arr;
		int _len, _size;
		bool increaseSize(int size);
	public:
		// Getters:
		int getLength() const { return _len; }

		// Setters:
		bool setLength(int size);

		// Methods:
		bool add(Citizen& cit);
		bool clear();
		int indexOf(int ID);

		// Overload operators
		Citizen& operator[](int idx) const;
		friend std::ostream& operator<<(std::ostream&, const CitizenArray&);
		const CitizenArray& operator=(const CitizenArray&);

		// Constructors:
		explicit CitizenArray(int len = 0);
		CitizenArray(const CitizenArray&) = delete;

		// Close application method
		void Dispose() {
			for (int i = 0; i < _len; i++)
				delete _arr[i];
			delete[] _arr;
		}
	};
}