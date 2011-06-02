/*
ID: r4f4rfs1
LANG: C++
TASK: ride
*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, const char *argv[])
{
    string comet, group;
    bool go = false;

    ifstream input("ride.in");

    getline(input, comet);
    getline(input, group);
    input.close();

    int cnum = 1;
    string::iterator it;
    for (it = comet.begin(); it < comet.end(); it++)
        cnum *= *it - 64;
    int gnum = 1;
    for (it = group.begin(); it < group.end(); it++)
        gnum *= *it - 64;
    go = cnum % 47 == gnum % 47;

    ofstream output("ride.out");
    if (go)
        output << "GO" << endl;
    else
        output << "STAY" << endl;
    output.close();

    return 0;
}
