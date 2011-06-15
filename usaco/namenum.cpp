/*
ID: r4f4rfs1
PROG: namenum
LANG: C++
IDEA: For each word in the dictionary of known names, generate the number that
represents it and check if it is equal to the input number.
COMP: O(n*m) where m is the number of words in the dictionary and n is the
number of digits of the input number.
*/

#include <iostream>
#include <fstream>
#include <map>
#include <cstring>
#include <cassert>

using namespace std;

/*
 * Get the number that generates that name
 */
static char *
hash(char name[], int len, map<char, int> keypad)
{
    char *r = new char[13];

    for (int i = 0; i < len; i++)
        r[i] = keypad[name[i]];
    r[len] = '\0';
    return r;
}

int
main(int argc, const char *argv[])
{
    char name[13] = {0};
    char number[13] = {0};
    map<char, int> keypad;
    bool found = false;

    keypad['A'] = keypad['B'] = keypad['C'] = '2';
    keypad['D'] = keypad['E'] = keypad['F'] = '3';
    keypad['G'] = keypad['H'] = keypad['I'] = '4';
    keypad['J'] = keypad['K'] = keypad['L'] = '5';
    keypad['M'] = keypad['N'] = keypad['O'] = '6';
    keypad['P'] = keypad['R'] = keypad['S'] = '7';
    keypad['T'] = keypad['U'] = keypad['V'] = '8';
    keypad['W'] = keypad['X'] = keypad['Y'] = '9';

    ifstream fin("namenum.in");
    assert(!fin.fail());
    fin >> number;
    fin.close();

    ifstream dict("dict.txt");
    assert(!dict.fail());

    ofstream fout("namenum.out");
    assert(!fout.fail());

    int snum = strlen(number);
    while (!dict.eof()) {
        dict >> name;
        int sname = strlen(name);
        /* They will never have the same representing number if their sizes are
         * different */
        if (sname == snum) {
            char *r = hash(name, sname, keypad);
            if (!strcmp(r, number)) {
                found = true;
                fout << name << endl;
            }
            delete[] r;
        }
    }
    dict.close();

    if (!found)
        fout << "NONE" << endl;
    fout.close();

    return 0;
}
