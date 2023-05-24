//Name: Adiel Roytgarts
//100068220
//aroytgarts1@myseneca.ca
//Date: April 16th, 2023
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Utils.h"
#include <ctime>

using namespace std;

namespace sdds
{
    void getSystemDate(int& year, int& mon, int& day, int& hour, int& min, bool dateOnly)
    {
        time_t t = time(NULL);
        tm lt = *localtime(&t);
        day = lt.tm_mday;
        mon = lt.tm_mon + 1;
        year = lt.tm_year + 1900;
        if (dateOnly) {
            hour = min = 0;
        }
        else {
            hour = lt.tm_hour;
            min = lt.tm_min;
        }
    }

    int uniqueDateValue(int year, int mon, int day, int hour, int min)
    {
        return year * 535680 + mon * 44640 + day * 1440 + hour * 60 + min;
    }

    int daysOfMonth(int year, int month) {
        int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
        int mon = month >= 1 && month <= 12 ? month : 13;
        mon--;
        return days[mon] + int((mon == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
    }

    int getValidInt(int min, int max, const char* message)
    {
        bool valid = false;
        int num;

        cout << message;

        while (!valid)
        {

            cin >> num;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid Integer, try again: ";
            }
            else if (num < min || num > max)
            {
                cout << "[1<=value<=" << max << "], retry: " << message;
            }
            else
            {
                valid = true;
            }
        }


        return num;
    }
}