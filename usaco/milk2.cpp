/*
PROG: milk2
ID: r4f4rfs1
LANG: C++
IDEA: Sort the intervals array by starting time and walk through it combining
intervals with intersection and maintaining the longest milking and idle times
until the moment.
*/
#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;
int
main(int argc, const char *argv[])
{
    int n, idle, milking;
    vector<pair<int, int> > times;

    ifstream fin("milk2.in");
    fin >> n;
    times.reserve(n);

    for (int i = 0; i < n; i++) {
        int begin, end;
        fin >> begin >> end;
        times.push_back(make_pair(begin, end));
    }
    fin.close();

    sort(times.begin(), times.end());
    /* Last interval (with intersections) */
    pair<int, int> last = make_pair(times[0].first, times[0].second);
    /* Longest milking time */
    milking = last.second - last.first;
    /* Longest idle time */
    idle = 0;
    for (int i = 1; i < times.size(); i++) {
        /* There is an idle time */
        if (times[i].first > last.second) {
            idle = max(idle, times[i].first - last.second);
            milking = max(milking, last.second - last.first);
            last = times[i];
        }
        /* Calculate intersection between intervals */
        else
            last.second = max(last.second, times[i].second);
    }

    ofstream fout("milk2.out");
    fout << milking << " " << idle << endl;
    fout.close();

    return 0;
}
