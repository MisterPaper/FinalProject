//Name: Adiel Roytgarts
//100068220
//aroytgarts1@myseneca.ca
//Date: March 26th, 2023

#ifndef SDDS_ERROR_H
#define SDDS_ERROR_H

#include <iostream>

namespace sdds
{
	class Error
	{
		char* m_message;
		void init(const char* cstring);

	public:
		Error();
		Error(const char*);
		Error(Error&);

		~Error();

		Error& operator=(const Error&);

		Error& operator=(const char*);

		operator bool() const;

		bool isError() const;

		Error& clear();

		std::ostream& output(std::ostream& ost) const;

	};

	std::ostream& operator <<(std::ostream&, const Error&);
}

#endif

