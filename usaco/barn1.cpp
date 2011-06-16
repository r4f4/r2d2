/*
ID: r4f4rfs1
PROG: barn1
LANG: C++
IDEA: The original idea was to merge consecutive boards of occupied stalls and
find those boards that could be merged and block the minimum number of
unoccupied stalls so as to lower the number of boards used until the maximum
bords m we could purchase. Unfortunately, I could not find without much
thinking an efficient way to find those boards besides doing a linear search =/
COMP: O(c * log(c) + (c - m) * c)
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef vector<pair<int, int> > VPair;

static VPair::iterator
find_min(VPair& stalls)
{
    int blocked;
    VPair::iterator min, it;

    min = stalls.begin();
    blocked = 201; // Max number of stalls blocked
    for (it = min + 1; it < stalls.end(); it++) {
        int num = it->first - (it - 1)->second - 1;
        if (num < blocked) {
            blocked = num;
            min = (it - 1);
        }
    }
    return min;
}

int
main(int argc, const char *argv[])
{
    int m, s, c, blocked;
    VPair stalls;
    vector<int> occupied;

    ifstream fin("barn1.in");
    assert(!fin.fail());
    fin >> m >> s >> c;

    for (int i = 0; i < c; i++) {
        int num;
        fin >> num;
        occupied.push_back(num);
    }
    fin.close();

    /* Sort occupied stalls so it is easier to work with them */
    sort(occupied.begin(), occupied.end());

    /* Merge boards of consecutive stalls */
    vector<int>::const_iterator it;
    for (it = occupied.begin(); it < occupied.end(); it++) {
        if (stalls.size() && (stalls.back().second == *it - 1))
            stalls.back().second = *it;
        else
            stalls.push_back(make_pair(*it, *it));
    }

    blocked = c;
    VPair::iterator min;
    while ((int)stalls.size() > m) {
        /* Find two consecutive stalls whose boards can be merged so as to
         * minimize the number of stalls blocked */
        min = find_min(stalls);

        /* Merge boards */
        blocked += (min + 1)->first - min->second - 1;
        min->second = (min + 1)->second;
        stalls.erase(min + 1);
    }

    ofstream fout("barn1.out");
    assert(!fout.fail());
    fout << blocked << endl;
    fout.close();

    return 0;
}
