/*
ID: r4f4rfs1
PROG: beads
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

/*
 * A 'w' char can be painted, so it's always equal to any other char
 */
static inline bool
equal(char x, char y)
{
    return (x == y) || (x == 'w') || (y == 'w');
}

int
main(int argc, const char *argv[])
{
    int i, j, next;
    int len, maximum = 0;
    char nl[351]; // The necklace

    ifstream fin("beads.in");
    fin >> len;
    fin >> nl;
    fin.close();

    int rstart = 0;

    // Ignore initial 'w' characters
    while ((rstart < len) && nl[rstart] == 'w') rstart++;

    // Necklace made just of 'w's ?
    if (rstart == len)
        maximum = len;

    /*
     * When the characters are equal, they don't need to be tested again just
     * by changing which one of them is the initial character. So we keep track
     * of the last one different and proceed from it until we reach the end of
     * the necklace. But the algorithm still is O(n^2) because of the tests
     * made through the right and left of the initial one.
     */
    while (rstart < len) {
        // The first character is always equals to itself. =)
        char cbreak = nl[rstart];
        int equals = 1;

        // Test equality through the right
        for (i = rstart + 1; (i < len) && equal(nl[i], cbreak); i++)
            equals++;

        // Keep position of the first different char
        next = i;

        // Wrap through right
        j = 0;
        if ((i == len) && equal(nl[0], cbreak)) {
            for ( ; (j < rstart) && equal(nl[j], cbreak); j++)
                equals++;
        }

        // Avoid pass through the entire necklace twice
        int stop = (j > 0) ? j - 1 : i - 1;

        int lstart = rstart - 1;
        // Nothing to test to the left
        if (((lstart > 0) && stop == lstart) || (stop == len))
            goto finish_loop;

        cbreak = (lstart >= 0) ? nl[lstart] : nl[len - 1];
        // Stop point was wrapped
        if (stop < rstart)
            // Test equality through the left
            for (j = lstart; (j > stop) && equal(nl[j], cbreak); j--) {
                cbreak = (cbreak == 'w') ? nl[j] : cbreak;
                equals++;
            }
        else {
            for (j = lstart; (j >= 0) && equal(nl[j], cbreak); j--) {
                cbreak = (cbreak == 'w') ? nl[j] : cbreak;
                equals++;
            }
            // Wrap through the left
            if (j < 0)
                for (j = len - 1; (j > stop) && equal(nl[j], cbreak); j--) {
                    cbreak = (cbreak == 'w') ? nl[j] : cbreak;
                    equals++;
                }
        }
finish_loop:
        maximum = max(maximum, equals);
        // Go to the next different char
        rstart = next;
    }

    ofstream fout("beads.out");
    fout << maximum << endl;
    fout.close();

    return 0;
}
