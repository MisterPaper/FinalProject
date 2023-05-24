//Name: Adiel Roytgarts
//100068220
//aroytgarts1@myseneca.ca
//Date: April 10th, 2023
#ifndef SDDS_NONPERISHABLE_H
#define SDDS_NONPERISHABLE_H

#include "Date.h"
#include "Item.h"

namespace sdds
{
	class NonPerishable : public Item
	{
		char itemType() const override;
		std::ostream& write(std::ostream&) const override;
	};
}

#endif