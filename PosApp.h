//Name: Adiel Roytgarts
//100068220
//aroytgarts1@myseneca.ca
//Date: April 16th, 2023

#ifndef SDDS_POSAPP_H
#define SDDS_POSAPP_H

#include <iostream>
#include <fstream>
#include <cstring>

#include "Perishable.h"
#include "NonPerishable.h"
#include "Item.h"
#include "Bill.h"

namespace sdds
{
	//Represents number of choices in menu
	const int numChoices = 5;

	//Represents the various functions as numbers
	const int listItems = 1;
	const int addItem = 2;
	const int removeItem = 3;
	const int stockItem = 4;
	const int pos = 5;
	const int exit = 0;

	const int MAX_FILE_LEN = 128;

	class PosApp
	{
		Bill m_bill;
		char m_fileName[MAX_FILE_LEN];
		Item* Iptr[MAX_NO_ITEMS];
		int m_numItems = 0;

		void emptyClass();

		int menu();
		void addItem();
		void removeItem(std::ostream& ost = std::cout);
		void stockItem(std::ostream& ost = std::cout);
		std::ostream& POS(std::ostream& ost = std::cout);

		int selectItem(std::ostream& ost = std::cout);

		std::ostream& printTitle(std::ostream& ost, const char* title) const;

		void loadRecs();

		void saveRecs() const;

		std::ostream& listItems(bool showTotal, std::ostream& ost = std::cout);

		void selectSort(int startIndex = 0);

		Item* search(const char* skuNum);

	public:
		void run();

		PosApp(const char* filename);

		PosApp(const PosApp&) = delete;

		PosApp& operator =(const PosApp&) = delete;

		~PosApp();

	};
}

#endif
