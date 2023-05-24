//Name: Adiel Roytgarts
//100068220
//aroytgarts1@myseneca.ca
//Date: April 5th, 2023

#include "PosIO.h"

namespace sdds
{
	std::ostream& operator<<(std::ostream& ost, PosIO& pos)
	{
		pos.write(ost);

		return ost;
	}

	std::ofstream& operator<<(std::ofstream& ost, PosIO& pos)
	{
		pos.save(ost);

		return ost;
	}

	std::istream& operator>>(std::istream& ist, PosIO& pos)
	{
		pos.read(ist);

		return ist;
	}

	std::ifstream& operator>>(std::ifstream& ifst, PosIO& pos)
	{
		pos.load(ifst);

		return ifst;
	}

}