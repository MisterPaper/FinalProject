//Name: Adiel Roytgarts
//100068220
//aroytgarts1@myseneca.ca
//Date: March 26th, 2023

#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include "Error.h"

namespace sdds
{
	Error::Error()
	{
		m_message = nullptr;
	}

	Error::Error(const char* cstring)
	{
		init(cstring);
	}

	Error::Error(Error& obj)
	{
		m_message = nullptr;
		*this = obj;
	}

	Error& Error::operator=(const Error& obj)
	{
		delete[] m_message;

		init(obj.m_message);

		return *this;
	}

	Error& Error::operator=(const char* cstring)
	{
		init(cstring);

		return *this;
	}

	Error::operator bool() const
	{
		return isError();
	}

	Error& Error::clear()
	{
		delete[] m_message;
		m_message = nullptr;

		return *this;
	}

	void Error::init(const char* cstring)
	{
		delete[] m_message;

		if (cstring != nullptr)
		{
			if (cstring[0] != '\0')
			{
				m_message = new char[strlen(cstring) + 1];
				strcpy(m_message, cstring);
			}
		}
		else
		{
			m_message = nullptr;
		}
	}

	Error::~Error()
	{
		delete[] m_message;
	}

	bool Error::isError() const
	{
		return m_message == nullptr ? false : true;
	}

	std::ostream& operator<<(std::ostream& ost, const Error& obj)
	{
		obj.output(ost);

		return ost;
	}

	std::ostream& Error::output(std::ostream& ost) const
	{
		if (isError())
		{
			ost << m_message;
		}

		return ost;
	}
}
