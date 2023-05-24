//Name: Adiel Roytgarts
//100068220
//aroytgarts1@myseneca.ca
//Date: April 16th, 2023

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>

#include "Utils.h"
#include "PosApp.h"

using namespace std;

namespace sdds
{
	PosApp::PosApp(const char* filename)
	{
		strcpy(m_fileName, filename);

		for (int i = 0; i < MAX_NO_ITEMS; i++)
		{
			Iptr[i] = nullptr;
		}
	}
	int PosApp::menu()
	{
		int userInput = -1;

		cout << "The Sene-Store\n";
		cout << "1- List items\n";
		cout << "2- Add item\n";
		cout << "3- Remove item\n";
		cout << "4- Stock item\n";
		cout << "5- POS\n";
		cout << "0- exit program\n";
		
		userInput = getValidInt(0, numChoices, "> ");

		return userInput;

	}

	void PosApp::run()
	{
		bool done = false;

		loadRecs();

		while (!done)
		{
			int userInput = menu();

			switch (userInput)
			{
			case sdds::listItems:
				listItems(true);
				break;
			case sdds::addItem:
				addItem();
				break;
			case sdds::removeItem:
				removeItem();
				break;
			case sdds::stockItem:
				stockItem();
				break;
			case sdds::pos:
				POS();
				break;
			case sdds::exit:
				saveRecs();

				done = true;
				break;
			}
		}

		cout << "Goodbye!\n";
	}

	std::ostream& PosApp::printTitle(std::ostream& ost, const char* title) const
	{
		ost << ">>>> ";
		ost.width(72);
		ost.fill('.');
		ost.setf(ios::left);
		ost << title;
		ost.unsetf(ios::left);
		ost.fill(' ');
		ost << "\n";

		return ost;
	}
	void PosApp::loadRecs()
	{
		m_numItems = 0;

		int index = 0;

		printTitle(cout, "Loading Items");
		ifstream ifst;

		ifst.open(m_fileName);
		if (ifst.fail())
		{
			ofstream ofst(m_fileName);
			ofst.close();

			ifst.open(m_fileName);
		}

		//delete class by emptying Iptr
		emptyClass();

		//Keeps reading input as long as file is in a good state
		//and the Iptr is not full
		while (ifst && Iptr[m_numItems] == nullptr)
		{
			char tempChar = ifst.get();
			if (tempChar == 'P')
			{
				//Keeps incrementing index until an available index is found
				while (Iptr[index] != nullptr && index < m_numItems)
					index++;
				Iptr[index] = new Perishable;
				m_numItems++;
				ifst >> *Iptr[index];
			}
			else if (tempChar == 'N')
			{
				//Keeps incrementing index until an available index is found
				while (Iptr[index] != nullptr && index < m_numItems)
					index++;
				Iptr[index] = new NonPerishable;
				ifst >> *Iptr[index];
				m_numItems++;
			}
		}
		ifst.close();

	}

	void PosApp::addItem()
	{
		int index = 0;
		cin.clear();
		cin.ignore(1000, '\n');

		printTitle(cout, "Adding Item to the store");

		if (m_numItems <= MAX_NO_ITEMS)
		{
			Item* pointer = nullptr;
			char input;

			cout << "Is the Item perishable? (Y)es/(N)o: ";
			cin.get(input);
			if (input == 'y')
				pointer = new Perishable;
			else if (input == 'n')
				pointer = new NonPerishable;

			do
			{
				cin >> *pointer;
				if (!*pointer)
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << ", try again...\n";
				}
			} while (!*pointer);

			//Get index of next available pointer
			while (Iptr[index] != nullptr)
				index++;

			//Set this to the pointer 
			Iptr[index] = pointer;
			m_numItems++;

			printTitle(cout, "DONE!");

		}
		else
			cout << "Inventory Full!\n";
	}
	void PosApp::removeItem(ostream& ost)
	{
		printTitle(ost, "Remove Item");
		int rowNum = selectItem();
		ost << "Removing....\n";

		Iptr[rowNum]->displayType(POS_FORM);
		ost << *Iptr[rowNum];

		delete Iptr[rowNum];
		Iptr[rowNum] = nullptr;

		//Sorts the Iptr array so that the nullptr entry is moved to the end
		selectSort(rowNum);

		//Update num items
		m_numItems--;

		printTitle(ost, "DONE!");

	}

	void PosApp::stockItem(ostream& ost)
	{
		printTitle(ost, "Select an item to stock");

		int rowNum = selectItem(ost);

		ost << "Selected Item:\n";
		Iptr[rowNum]->displayType(POS_FORM);
		ost << *Iptr[rowNum];

		int quantity = getValidInt(1, MAX_STOCK_NUMBER - Iptr[rowNum]->quantity(), "Enter quantity to add: ");

		*Iptr[rowNum] += quantity;

		printTitle(ost, "DONE!");

	}
	ostream& PosApp::POS(ostream& ost)
	{
		printTitle(ost, "Starting Point of Sale");
		cin.ignore(1000, '\n');

		bool done = false;

		while (!done)
		{
			char sku[MAX_SKU_LEN];

			bool valid = false;
			while (!valid)
			{
				ost << "Enter SKU or <ENTER> only to end sale...\n";
				ost << "> ";

				int i = 0;
				if (cin.peek() != '\n')
				{
					while (cin.peek() != '\n' && i < MAX_SKU_LEN - 1)
					{
						sku[i] = cin.get();
						i++;
					}
					sku[i] = '\0';
				}
				else
					sku[0] = '\0';


				if (sku[0] != '\0' && cin.peek() == '\n')
				{
					cin.ignore(1000, '\n');
					valid = true;
				}
				else if (sku[0] == '\0')
				{
					cin.ignore(1000, '\n');
					//Break out of both loops
					valid = true;
					done = true;
				}
				else
				{
					cin.ignore(1000, '\n');
					ost << "SKU too long\n";
				}

			}

			if (!done)
			{
				Item* item = search(sku);

				if (item != nullptr)
				{
					*item -= 1;
					if (!*item)
					{
						item->clear();
						ost << "Item out of stock\n";
					}
					else
					{
						item->displayType(POS_FORM);
						ost << *item;

						m_bill.add(item);
						ost << "\n>>>>> Added to bill\n";
						ost.precision(2);
						ost.setf(ios::fixed);
						ost << ">>>>> Total: " << m_bill.total() << "\n";
						ost.unsetf(ios::fixed);
					}
				}
				else
					ost << "!!!!! Item Not Found !!!!!\n";
			}
			else
			{
				m_bill.print(ost);
				ost.unsetf(ios::right);
				ost.unsetf(ios::fixed);
			}
		}

		return ost;
	}

	void PosApp::saveRecs() const
	{

		printTitle(cout, "Saving Data");
		ofstream output(m_fileName);

		//Keep printing into the ostream instance until nullptr is encountered
		for(int i = 0; i < m_numItems; i++)
		{
			output << *Iptr[i] << '\n';
		}
		output.close();
	}

	std::ostream& PosApp::listItems(bool showTotal, std::ostream& ost)
	{
		double totalAssets = 0;

		selectSort();
		printTitle(ost, "Listing Items");

		ost << " Row | SKU    | Item Name          | Price |TX |Qty |   Total | Expiry Date |\n";
		ost << "-----|--------|--------------------|-------|---|----|---------|-------------|\n";

		//Keep printing into the ostream instance until num items
		for(int i = 0; i < m_numItems; i++)
		{
			totalAssets += Iptr[i]->getTotal();
			ost.width(4);
			ost.fill(' ');
			ost.setf(ios::left);
			ost.unsetf(ios::left);
			ost << i+1 << " | ";
			Iptr[i]->displayType(POS_LIST);
			ost << *Iptr[i];
		}
		ost << "-----^--------^--------------------^-------^---^----^---------^-------------^\n";
		if (showTotal)
		{
			ost << "                               Total Asset: $  |       ";
			ost.precision(2);
			ost.setf(ios::fixed);
			ost.setf(ios::right);
			ost << totalAssets << "| \n";
			ost.unsetf(ios::fixed);
			ost.unsetf(ios::right);
			ost << "-----------------------------------------------^--------------^\n\n";
		}
		return ost;
	}

	int PosApp::selectItem(ostream& ost) 
	{
		printTitle(cout, "Item Selection by row number");
		cin.ignore(1000, '\n');
		ost << "Press <ENTER> to start....";
		while (cin.get() != '\n');

		listItems(false, ost);

		//Subtract by one as the array starts from 0
		int num = getValidInt(1, m_numItems, "Enter the row number: ") - 1;

		return num;
	}

	void PosApp::emptyClass()
	{
		for (int i = 0; i < MAX_NO_ITEMS; i++)
		{
			delete Iptr[i];
			Iptr[i] = nullptr;
		}
	}

	PosApp::~PosApp()
	{
		emptyClass();
	}

	//If found, returns the index of the matching Item
	//If not found, returns -1
	Item* PosApp::search(const char* skuNum)
	{
		int index = 0;
		Item* item;
		bool found = false;

		//Keeps looping until a matching skuNum is found
		while (!found && index < (m_numItems))
		{
			if (*Iptr[index] == skuNum)
				found = true;
			else
				index++;
		}

		if (index > m_numItems)
			item = nullptr;
		else
			item = Iptr[index];

		return item;
	}

	//Sorts in ascending order. startIndex has default value of 0.
	void PosApp::selectSort(int startIndex)
	{
		int i, j, minIdx;
		Item* tempPointer;

		for (i = startIndex; i < m_numItems; i++)
		{
			minIdx = i;

			for (j = i + 1; j < m_numItems; j++)
			{
				if (Iptr[j] != nullptr && Iptr[minIdx] != nullptr)
				{
					if (*Iptr[j] < *Iptr[minIdx])
					{
						minIdx = j;
					}
				}
				//For the purposes of sorting, a nullptr entry will have
				//the highest value
				else if (Iptr[j] != nullptr && Iptr[minIdx] == nullptr)
				{
					minIdx = j;
				}
			}

			if (minIdx != i)
			{
				//tempPointer is now storing the address that Iptr[i] is pointing to, which will be referred to as Address X
				tempPointer = Iptr[i];

				//Iptr[i] is now storing the address that Iptr[minIdx] is pointing to, which will now be referred to as Address Y
				Iptr[i] = Iptr[minIdx];

				//Iptr[minIdx] is now pointing to Address X, while Iptr[i] is pointing to Address Y.
				//No modification of any of the non-pointer types is neccessary
				Iptr[minIdx] = tempPointer;
			}
		}
	}
}
