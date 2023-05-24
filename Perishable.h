//Name: Adiel Roytgarts
//100068220
//aroytgarts1@myseneca.ca
//Date: April 10th, 2023
#ifndef SDDS_PERISHABLE_H
#define SDDS_PERISHABLE_H

#include "Item.h"
#include "Date.h"

namespace sdds
{
	class Perishable : public Item
	{
		Date m_date;

		char itemType() const override;

		std::istream& read(std::istream&) override;

		std::ostream& write(std::ostream&) const override;

		std::ofstream& save(std::ofstream&) const override;
		
		std::ifstream& load(std::ifstream&) override;


	};
}

#endif