//Name: Adiel Roytgarts
//100068220
//aroytgarts1@myseneca.ca
//Date: March 26th, 2023

#ifndef SDDS_UTILS_H
#define SDDS_UTILS_H

namespace sdds
{
	void getSystemDate(int& year, int& mon, int& day, int& hour, int& min, bool dateOnly);
	int uniqueDateValue(int year, int mon, int day, int hour, int min);
	int daysOfMonth(int year, int month);

	int getValidInt(int min, int max, const char* message = " ");
}

#endif
