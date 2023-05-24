//Name: Adiel Roytgarts
//100068220
//aroytgarts1@myseneca.ca
//Date: April 5th, 2023

#ifndef SDDS_ITEM_H
#define SDDS_ITEM_H

#include "Error.h"
#include "POS.h"
#include "PosIO.h"

namespace sdds
{
	class Item : public PosIO
	{
		char m_skuCode[MAX_SKU_LEN];
		//max: MAX_SKU_LEN
		char* m_name;
		double m_price;
		bool m_taxed;
		
		int m_quantity;
	protected:
		//Either equal to POS_LIST or POS_FORM
		int m_displayType;
		Error error = {};

		void setEmpty();

		virtual std::ostream& write(std::ostream&) const override;
		virtual std::ofstream& save(std::ofstream&) const override;
		virtual std::istream& read(std::istream&) override;
		virtual std::ifstream& load(std::ifstream&) override;
	public:
		Item();
		Item(Item&);
		Item& operator=(const Item&);
		~Item();

		//cstring: the cstring to attempt read into
		//varName: the name of the variable of the cstring
		//istream& charValidate(std::istream& ist, char* varName, char* cstring);

		std::ostream& bprint(std::ostream& ost) const;

		double cost() const;
		int quantity() const;

		double getTotal() const;

		bool operator==(const char*) const;
		bool operator!=(const char*) const;
		bool operator>(Item&) const;
		bool operator<(Item&) const;

		int operator+=(int);
		int operator-=(int);

		operator bool() const;

		virtual char itemType() const = 0;

		Item& displayType(int);

		Item& clear();

	};

	double& operator+=(double& num, const Item& item);

	//std::ostream& operator<<(std::ostream&, Item& item);
	//std::ofstream& operator<<(std::ofstream&, Item& item);

	//std::istream& operator>>(std::istream&, Item& item);
	//std::ifstream& operator>>(std::ifstream&, Item& item);
}
#endif