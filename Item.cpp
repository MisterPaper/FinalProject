//Name: Adiel Roytgarts
//100068220
//aroytgarts1@myseneca.ca
//Date: April 5th, 2023

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <string>

#include "Item.h"

using namespace std;

namespace sdds
{
	Item::Item()
	{
		setEmpty();
	}

	Item::~Item()
	{
		delete[] m_name;
	}

	Item::Item(Item& item)
	{
		m_name = nullptr;

		*this = item;
	}

	Item& Item::operator=(const Item& item)
	{
		if (this != &item)
		{
			strcpy(m_skuCode, item.m_skuCode);
			m_price = item.m_price;
			m_taxed = item.m_taxed;
			m_quantity = item.m_quantity;
			m_displayType = item.m_displayType;

			delete[] m_name;
			m_name = nullptr;
			if (item.m_name != nullptr)
			{
				this->m_name = new char[strlen(item.m_name) + 1];
				strcpy(m_name, item.m_name);
			}
		}
		else
			setEmpty();

		return *this;
	}

	void Item::setEmpty()
	{
		m_skuCode[0] = '\0';
		m_name = nullptr;
		m_price = -1;
		m_taxed = false;
		m_quantity = -1;

		m_displayType = -1;

		//error goes through default constructor

	}

	bool Item::operator==(const char* cstring) const
	{
		bool isTrue;

		if (strcmp(m_skuCode, cstring) == 0)
		{
			isTrue = true;
		}
		else
			isTrue = false;

		return isTrue;
	}

	bool Item::operator!=(const char* cstring) const
	{
		bool isTrue;

		if (strcmp(m_skuCode, cstring) == 0)
		{
			isTrue = false;
		}
		else
			isTrue = true;

		return isTrue;
	}

	bool Item::operator>(Item& item) const
	{

		if (this->m_name && item.m_name)
		{
			return (strcmp(m_name, item.m_name) > 0);
		}
		else
			return false;
	}
	bool Item::operator<(Item& item) const
	{

		if (this->m_name && item.m_name)
		{
			return (strcmp(m_name, item.m_name) < 0);
		}
		else
			return false;
	}

	int Item::operator+=(int amount)
	{
		m_quantity += amount;

		if (m_quantity > MAX_STOCK_NUMBER)
		{
			m_quantity = MAX_STOCK_NUMBER;
			error = ERROR_POS_QTY;
		}

		return m_quantity;
	}

	int Item::operator-=(int amount)
	{
		m_quantity -= amount;

		if (m_quantity < 0)
		{
			m_quantity = 0;
			error = ERROR_POS_STOCK;
		}
		
		return m_quantity;
	}

	Item::operator bool() const
	{
		return !((bool)error);
	}

	int Item::quantity() const
	{
		return m_quantity;
	}

	double& operator+=(double& num, const Item& item)
	{
		num += (item.cost() * item.quantity());

		return num;
	}

	Item& Item::displayType(int type)
	{
		switch (type)
		{
		case POS_LIST:
			m_displayType = POS_LIST;
			break;
		case POS_FORM:
			m_displayType = POS_FORM;
			break;
		}
		return *this;
	}

	Item& Item::clear()
	{
		error.clear();

		return *this;
	}

	double Item::getTotal() const
	{
		double num = 0;
		num = (cost() * quantity());

		return num;
	}

	ostream& Item::write(ostream& ost) const
	{
		ost.fill(' ');
		if (*this)
		{
			if (m_displayType == POS_LIST)
			{
				ost.setf(ios::left);
				ost.width(7);
				ost << m_skuCode << "|";
				ost.width(20);
				if (strlen(m_name) > 20)
				{
					char tempChar[21];
					strncpy(tempChar, m_name, 21);
					tempChar[20] = '\0';
					ost << tempChar << "|";
				}
				else
					ost << m_name << "|";
				ost.unsetf(ios::left);
				ost.setf(ios::fixed);
				ost.width(7);
				ost.precision(2);
				ost << m_price << "|";
				if (m_taxed)
					ost << " X |";
				else
					ost << "   |";
				ost.width(4);
				ost << m_quantity << "|";
				ost.width(9);
				ost.precision(2);
				ost << getTotal() << "|";
				ost.unsetf(ios::fixed);
			}
			else if (m_displayType == POS_FORM)
			{
				ost << "=============v\n";
				ost.width(13);
				ost.setf(ios::left);
				ost << "Name:" << m_name << endl;
				ost.width(13);
				ost << "Sku:" << m_skuCode << endl;
				ost.width(13);
				ost << "Price:";
				ost.setf(ios::fixed);
				ost.precision(2);
				ost.unsetf(ios::left);
				ost << m_price << endl;
				ost.setf(ios::left);
				ost.width(13);
				ost << "Price + tax:";
				ost.unsetf(ios::left);
				ost.precision(2);
				if (m_taxed)
					ost << (m_price * (1 + TAX)) << endl;
				else
					ost << "N/A" << endl;
				ost.setf(ios::left);
				ost.width(13);
				ost << "Stock Qty:" << m_quantity << endl;
				ost.unsetf(ios::fixed);

			}
		}
		else
		{
			cout << error;
		}
		return ost;
	}

	std::ofstream& Item::save(std::ofstream& ost) const
	{
		ost << itemType() << ",";
		ost << m_skuCode << ",";
		ost << m_name << ",";
		ost.precision(2);
		ost.setf(ios::fixed);
		ost << m_price << ",";
		ost.unsetf(ios::fixed);
		ost << m_taxed << ",";
		ost << m_quantity;

		if (!*this)
			cerr << error << endl;
		return ost;
	}

	std::istream& Item::read(std::istream& ist)
	{
		char toRead[200];
		char taxChar;

		bool fail = true;

		//Validation and prompt for skuCode
		cout << "Sku\n";
		while (fail)
		{
			cout << "> ";
			ist >> toRead;
			if (strlen(toRead) > 4)
			{
				error = ERROR_POS_SKU;
				cerr << error << endl;
			}
			else
			{
				fail = false;
				strcpy(m_skuCode, toRead);
			}
		}

		//Validation and prompt for Name
		cout << "Name\n";
		ist.ignore(1000, '\n');
		fail = true;
		while (fail)
		{
			cout << "> ";
			ist.getline(toRead, 200, '\n');
			if (strlen(toRead) > 40)
			{
				error = ERROR_POS_NAME;
				cerr << error << endl;
			}
			else
			{
				fail = false;
				delete[] m_name;
				m_name = new char[strlen(toRead) + 1];
				strcpy(m_name, toRead);
			}
		}
		//Validation and prompt for Price
		fail = true;
		//ist.ignore(1000, '\n');
		cout << "Price\n";
		while (fail)
		{
			cout << "> ";
			ist >> m_price;
			if (ist.fail())
			{
				ist.clear();
				ist.ignore(1000, '\n');
				error = ERROR_POS_PRICE;
				cerr << error << endl;
			}
			else if (m_price < 0)
			{
				error = ERROR_POS_PRICE;
				cerr << error << endl;
			}
			else
				fail = false;
		}

		//Validation and prompt for Taxed
		fail = true;
		cout << "Taxed?\n";
		cout << "(Y)es/(N)o: ";
		while (fail)
		{
			ist >> taxChar;
			if (ist.get() == '\n' && (taxChar == 'y' || taxChar == 'n'))
			{
				m_taxed = (taxChar == 'y');
				fail = false;
			}
			else
			{
				ist.ignore(1);
				error = ERROR_POS_TAX;
				cerr << "Only 'y' and 'n' are acceptable: ";
			}
		}

		//Validation and prompt for Quantity
		fail = true;
		cout << "Quantity\n";
		while (fail)
		{
			cout << "> ";
			ist >> m_quantity;
			if (ist.fail())
			{
				ist.clear();
				ist.ignore(1000, '\n');
				error = ERROR_POS_QTY;
				cerr << error << endl;
			}
			else if (m_quantity <= 0 || m_quantity > MAX_STOCK_NUMBER)
			{
				error = ERROR_POS_QTY;
				cerr << error << endl;
			}
			else
			{
				fail = false;
			}
		}

		//error.clear();

		return ist;
	}


	std::ifstream& Item::load(std::ifstream& ifst)
	{
		error.clear();
		char skuCode[25];
		char name[200];

		double price;
		int taxed;
		int quantity;

		ifst.ignore(1);

		ifst.getline(skuCode, 25, ','); 
		ifst.getline(name, 200, ',');
		ifst >> price;
		ifst.ignore(1);
		ifst >> taxed;
		ifst.ignore(1);
		ifst >> quantity;

		if (!ifst.fail())
		{
			if (strlen(skuCode) > MAX_SKU_LEN)
				error = ERROR_POS_SKU;
			else if (strlen(name) > MAX_NAME_LEN)
				error = ERROR_POS_NAME;
			else if (price < 0)
				error = ERROR_POS_PRICE;
			else if (taxed != 0 && taxed != 1)
				error = ERROR_POS_TAX;
			else if (quantity < 0 || quantity > MAX_STOCK_NUMBER)
				error = ERROR_POS_QTY;


			if (!error)
			{
				strcpy(m_skuCode, skuCode);

				delete[] m_name;
				m_name = new char[strlen(name) + 1];
				strcpy(m_name, name);

				m_price = price;
				m_taxed = taxed;
				m_quantity = quantity;

			}
		}

		return ifst;
	}

	std::ostream& Item::bprint(std::ostream& ost) const
	{
		ost.fill(' ');

		if (m_name != nullptr)
		{
			ost << "| ";
			ost.width(20);
			ost.setf(ios::left);
			if (strlen(m_name) > 20)
			{
				char tempChar[21];
				strncpy(tempChar, m_name, 21);
				tempChar[20] = '\0';
				ost << tempChar << "|";
			}
			else
				ost << m_name << "|";

			ost.unsetf(ios::left);
			ost.width(10);
			ost.precision(2);
			ost.setf(ios::fixed);
			ost.setf(ios::right);
			if (m_taxed)
			{
				ost << (m_price * (1 + TAX));
				ost << " |  T  |\n";
			}
			else
			{
				ost << m_price;
				ost << " |     |\n";
			}
			ost.unsetf(ios::right);
			ost.unsetf(ios::fixed);

		}
		return ost;
	}

	double Item::cost()const {
		return m_price * (1 + m_taxed * TAX);
	}
}


//Redundant Functions

//double Item::cost() const
//{
//	double cost = m_price;
//	if (m_taxed)
//		cost += (TAX * m_price);
//	return cost;
//}