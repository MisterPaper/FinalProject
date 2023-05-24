//Name: Adiel Roytgarts
//100068220
//aroytgarts1@myseneca.ca
//Date: March 26th, 2023

#include <iostream>
#include "Utils.h"
#include "Date.h"
#include "POS.h"

using namespace std;

namespace sdds
{
	Date::Date()
	{
		m_dateOnly = false;

		getSystemDate(m_year, m_month, m_day, m_hour, m_minute, false);
	}

	Date::Date(int year, int month, int day)
	{
		m_year = year;
		m_month = month;
		m_day = day;

		m_hour = m_minute = 0;
		m_dateOnly = true;

		doValid();
	}

	Date::Date(int year, int month, int day, int hour)
	{
		m_year = year;
		m_month = month;
		m_day = day;

		m_hour = hour;
		m_minute = 0;
		m_dateOnly = false;

		doValid();
	}

	Date::Date(int year, int month, int day, int hour, int minute)
	{
		m_year = year;
		m_month = month;
		m_day = day;

		m_hour = hour;
		m_minute = minute;
		m_dateOnly = false;

		doValid();
	}

	void Date::doValid()
	{
		if (m_year < MIN_YEAR || m_year > MAX_YEAR)
			m_error = "Invalid Year";
		else if (m_month < 1 || m_month > 12)
			m_error = "Invalid Month";
		else if (m_day < 1 || m_day > daysOfMonth(m_year, m_month))
			m_error = "Invalid Day";
		//Only check for hour and minute validation if needed
		else if (!m_dateOnly)
		{
			if (m_hour < 0 || m_hour > 23)
				m_error = "Invalid Hour";
			else if (m_minute < 0 || m_minute > 59) //Typo?
				m_error = "Invlid Minute";
		}
	}

	bool Date::operator==(Date& date) const
	{
		bool isTrue;

		if (uniqueDateValue(m_year, m_month, m_day, m_hour, m_minute) == uniqueDateValue(date.m_year, date.m_month, date.m_day, date.m_hour, date.m_minute))
		{
			isTrue = true;
		}
		else
			isTrue = false;
		return isTrue;
	}

	bool Date::operator!=(Date& date) const
	{
		return !(*this == date);
	}

	bool Date::operator<(Date& date) const
	{
		bool isTrue;

		if (uniqueDateValue(m_year, m_month, m_day, m_hour, m_minute) < uniqueDateValue(date.m_year, date.m_month, date.m_day, date.m_hour, date.m_minute))
			isTrue = true;
		else
			isTrue = false;
		return isTrue;
	}

	bool Date::operator>(Date& date) const
	{
		return !(*this < date);
	}

	bool Date::operator>=(Date& date) const
	{
		return (*this == date || *this > date);
	}

	bool Date::operator<=(Date& date) const
	{
		return (*this == date || *this < date);
	}

	Date::operator bool() const
	{
		return !(m_error.isError());
	}

	Date& Date::dateOnly(bool dateOnly)
	{
		m_dateOnly = dateOnly;
		if (dateOnly)
		{
			m_hour = 0;
			m_minute = 0;
		}

		return *this;
	}

	const Error& Date::error() const
	{
		return (Error&)m_error;
	}

	std::ostream& Date::output(std::ostream& ost) const
	{
		ost.unsetf(ios::left);
		if (m_error.isError())
		{
			ost << (Error&)m_error;
			ost << "(" << m_year << "/";
			ost.width(2);
			ost.fill('0');
			ost << m_month << "/";
			ost.width(2);
			ost.fill('0');
			ost.setf(ios::fixed);
			ost.setf(ios::right);
			ost << m_day;
			ost.unsetf(ios::right);
			ost.unsetf(ios::fixed);

			if (!m_dateOnly)
			{

				ost << ", ";
				ost.width(2);
				ost.fill('0');
				ost << m_hour << ":";
				ost.width(2);
				ost.fill('0');
				ost << m_minute << ")";
			}
			else
			{
				ost << ")";
			}
		}
		else
		{
			ost << m_year << "/";
			ost.width(2);
			ost.fill('0');
			ost << m_month << "/";
			ost.width(2);
			ost.fill('0');
			ost.setf(ios::fixed);
			ost.setf(ios::right);
			ost << m_day;
			ost.unsetf(ios::fixed);
			ost.unsetf(ios::right);

			if (!m_dateOnly)
			{
				ost << ", ";
				ost.width(2);
				ost.fill('0');
				ost << m_hour << ":";
				ost.width(2);
				ost.fill('0');
				ost << m_minute;
			}

		}

		return ost;
	}

	std::istream& Date::input(std::istream& ist)
	{
		m_error.clear();
		m_year = 0;
		m_month = 0;
		m_day = 0;
		m_hour = 0;
		m_minute = 0;

		ist >> m_year;

		//Input for delimited date input in the format YYYY*MM*DD*TT:TT
		if (ist.fail())
			m_error = "Cannot read year entry";
		else
		{
			//READING MM
			ist.ignore(1);
			ist >> m_month;

			if (ist.fail())
				m_error = "Cannot read month entry";
			else
			{
				//READING DD
				ist.ignore(1);
				ist >> m_day;

				if (ist.fail())
				{
					m_error = "Cannot read day entry";
				}
				else
				{
					if (!m_dateOnly)
					{

						ist.ignore(1);
						ist >> m_hour;

						if (ist.fail())
							m_error = "Cannot read hour entry";
						else
						{
							ist.ignore(1);
							ist >> m_minute;

							doValid();

							if (ist.fail())
							{
								m_error = "Cannot read minute entry";
							}
						}
					}
					//User inputted date only
					else
					{
						m_hour = 0;
						m_minute = 0;
						doValid();
					}
				}
			}
		}
		return ist;
	}

	std::ostream& operator <<(std::ostream& ost, Date& date)
	{
		date.output(ost);

		return ost;
	}

	std::istream& operator >>(std::istream& ist, Date& date)
	{
		date.input(ist);

		return ist;
	}
}
