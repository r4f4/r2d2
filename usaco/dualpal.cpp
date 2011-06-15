/*
ID: r4f4rfs1
PROG: dualpal
LANG: C++
IDEA: Walk all the numbers starting on S, convert them to bases from 2 to 10
and test in each base whether it is palindrome or not.
COMP: (8 * 20) * n, where n is the quantity of numbers tested.
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
    int n, start;
    bool is_pal;

    ifstream fin("dualpal.in");
    assert(!fin.fail());
    fin >> n >> start;
    fin.close();

    ofstream fout("dualpal.out");
    assert(!fout.fail());
    for (int i = start + 1; n > 0; i++) {
        is_pal = false;
        /* Test all the bases from 2 to 10 */
        for (int b = 2; b < 11; b++)
            if (is_palindrome(convert(i, b))) {
                /* Two bases found in which the number is palindrome */
                if (is_pal) {
                    fout << i << endl;
                    n--;
                    break;
                }
                /* Just found the first base */
                is_pal = true;
            }
    }
    fout.close();

    return 0;
}

