//Name: Adiel Roytgarts
//100068220
//aroytgarts1@myseneca.ca
//Date: April 10th, 2023
#include <iostream>
#include "Perishable.h"

using namespace std;

namespace sdds
{
	char Perishable::itemType() const
	{
		return 'P';
	}

	std::istream& Perishable::read(std::istream& ist)
	{
		Item::read(ist);

		if (*this && !ist.fail())
		{
			Date temp;

			temp.dateOnly(true);
			cout << "Expiry date (YYYY/MM/DD)\n";
			cout << "> ";
			ist >> temp;

			if (temp)
				m_date = temp;
			else
				error = m_date.error();
		}

		return ist;
	}

	std::ostream& Perishable::write(std::ostream& ost) const
	{
		Item::write(ost);
		if (*this)
		{
			if (m_displayType == POS_LIST)
			{
				ost << "  " << (Date&)m_date << " |\n";
			}
			else if (m_displayType == POS_FORM)
			{
				ost << "Expiry date: " << (Date&)m_date << '\n' << "=============^\n";
			}
		}

		return ost;
	}

	std::ofstream& Perishable::save(std::ofstream& ofst) const 
	{
		Item::save(ofst);

		if (*this)
		{
			ofst << "," << (Date&)m_date;
		}

		return ofst;
	}

	std::ifstream& Perishable::load(std::ifstream& ifst)
	{
		Item::load(ifst);
		if (*this && ifst)
		{
			Date temp;
			temp.dateOnly(true);
			ifst.ignore(1);
			ifst >> temp;

			if (temp)
			{
				m_date = temp;
			}
			else
			{
				error = m_date.error();
			}
		}

		return ifst;
	}

}