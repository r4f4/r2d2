/*
ID: r4f4rfs1
PROG: milk
LANG: C++
IDEA: Just buy as much milk as we can from the farmers that sell their milk
with lower prices.
COMP: O(m*log(m)), where m is the number of farmers
*/

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

int
main(int argc, const char *argv[])
{
    int n, m, price;
    vector<pair<int, int> > farmers;

    ifstream fin("milk.in");
    assert(!fin.fail());
    fin >> n >> m;
    farmers.reserve(m);
    for (int i = 0; i < m; i++) {
        int pi, ai;
        fin >> pi >> ai;
        farmers.push_back(make_pair(pi, ai));
    }
    fin.close();

    /* Sort farmers by their prices */
    sort(farmers.begin(), farmers.end());

    price = 0;
    vector<pair<int, int> >::iterator it;
    for (it = farmers.begin(); it < farmers.end() && n; it++) {
        int quantity = min(n, it->second);
        price += quantity * it->first;
        n -= quantity;
    }

    ofstream fout("milk.out");
    assert(!fout.fail());
    fout << price << endl;
    fout.close();

    return 0;
}
