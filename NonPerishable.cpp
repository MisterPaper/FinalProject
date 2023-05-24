//Name: Adiel Roytgarts
//100068220
//aroytgarts1@myseneca.ca
//Date: April 10th, 2023
#include "NonPerishable.h"

namespace sdds
{
	char NonPerishable::itemType() const
	{
		return 'N';
	}
	std::ostream& NonPerishable::write(std::ostream& ost) const 
	{
		Item::write(ost);
		if (*this)
		{
			if (m_displayType == POS_LIST)
				ost << "     N / A   |\n";
			else if (m_displayType == POS_FORM)
				ost << "=============^\n";
		}
		return ost;
	}
}
