/*
ID: r4f4rfs1
PROG: palsquare
LANG: C++
IDEA: Very stupid: just to the conversion to the respective base and check
whether the square of the number is a palindrome.
COMP: 300 * (20 + 20)
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

using namespace std;

static bool
is_palindrome(string num)
{
    int n = num.size();
    for (int i = 0; i < n / 2; i++)
        if (num[i] != num[n - i - 1])
            return false;
    return true;
}

static string
convert(int num, int base)
{
    static const string digits("0123456789ABCDEFGHIJK");
    string result;

    for (; num; num /= base)
        result.insert(result.begin(), digits[num % base]);

    return result;
}

int
main(int argc, const char *argv[])
{
    int base;

    ifstream fin("palsquare.in");
    assert(!fin.fail());
    fin >> base;
    fin.close();

    ofstream fout("palsquare.out");
    assert(!fout.fail());

    for (int n = 1; n <= 300; n++) {
        string square = convert(n * n, base);
        if (is_palindrome(square))
            fout << convert(n, base) << " " << square << endl;
    }
    fout.close();

    return 0;
}
