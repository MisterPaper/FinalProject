//Name: Adiel Roytgarts
//100068220
//aroytgarts1@myseneca.ca
//Date: April 5th, 2023

#ifndef SDDS_POSIO_H
#define SDDS_POSIO_H

#include <fstream>
#include <iostream>

namespace sdds
{
	class PosIO
	{
	public:
		virtual std::ostream& write(std::ostream&) const = 0;

		virtual std::istream& read(std::istream&) = 0;

		virtual std::ofstream& save(std::ofstream&) const = 0;

		virtual std::ifstream& load(std::ifstream&) = 0;

		virtual ~PosIO() = default;
	};


	std::ostream& operator<<(std::ostream&, PosIO& pos);
	std::ofstream& operator<<(std::ofstream&, PosIO& pos);

	std::istream& operator>>(std::istream&, PosIO& pos);
	std::ifstream& operator>>(std::ifstream&, PosIO& pos);
}

#endif

