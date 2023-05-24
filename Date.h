//Name: Adiel Roytgarts
//100068220
//aroytgarts1@myseneca.ca
//Date: March 26th, 2023

#ifndef SDDS_DATE_H
#define SDDS_DATE_H

#include "Error.h"
#include <iostream>

namespace sdds
{
	class Date
	{
		int m_year;
		int m_month;
		int m_day;
		int m_hour;
		int m_minute;

		bool m_dateOnly;

		Error m_error;

		void doValid();
		//Retrieves date in cstring format
		//const char* getDate() const;
	public:
		Date();
		Date(int year, int month, int day);
		Date(int year, int month, int day, int hour);
		Date(int year, int month, int day, int hour, int minute);

		bool operator==(Date&) const;
		bool operator!=(Date&) const;

		bool operator>(Date&) const;
		bool operator<(Date&) const;

		bool operator>=(Date&) const;
		bool operator<=(Date&) const;

		operator bool() const;

		Date& dateOnly(bool);

		const Error& error() const;

		std::ostream& output(std::ostream& ost) const;

		std::istream& input(std::istream& ist);
	};

	std::ostream& operator <<(std::ostream& ost, Date& date);

	std::istream& operator >>(std::istream& ist, Date& date);

}
#endif