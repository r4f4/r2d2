/*
PROG: friday
ID: r4f4rfs1
LANG: C++
*/
#include <iostream>
#include <fstream>

using namespace std;

enum { sat, sun, mon, tue, wed, thu, fri };

// For debugging
char weekdays[][12] = {
    "Saturday",
    "Sunday",
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday"
};

int days[][12] = {
    {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int main(int argc, const char *argv[])
{
    int n;
    int first = mon;
    unsigned int times[7] = {0} ; // #13th on sat, sun, mon, ..., fri

    ifstream fin("friday.in");
    fin >> n;
    fin.close();

    for (int year=1900; year < 1900 + n; year++) {
        bool is_leap_year = !(year % 400) || ((year % 100) && !(year % 4));
        for (int month=0; month < 12; month++) {
            //cout << weekdays[first] << " is first day of " << month << "/" << year << endl;
            int weekday = (first + 12) % 7;
            //cout << "13th land on a " << weekdays[weekday] << endl;
            times[weekday]++;
            first = (first + days[is_leap_year][month]) % 7;
        }
    }

    ofstream fout("friday.out");
    for (int i = 0; i < 7; i++) {
        if (i < 6)
            fout << times[i] << " ";
        else
            fout << times[i];
    }
    fout << endl;
    fout.close();

    return 0;
}
