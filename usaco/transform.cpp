/*
ID: r4f4rfs1
PROG: transform
LANG: C++
IDEA: Just check all seven transformations one by one but taking advantage of
the fact that the order of reflecting and rotating does not matter. So we just
test the rotation and try testing the inverted line to figure out whether there
was reflection
COMP: O(n^2)
*/

#include <fstream>
#include <algorithm>

#define MAXSIZE 11

using namespace std;

enum { DEG90 = 1, DEG180, DEG270,
       REFLECTION, COMB, NO_CHANGE, INVALID };

int
zero_deg(char pattern[][MAXSIZE], char result[][MAXSIZE], int n)
{
    int transf = NO_CHANGE;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (pattern[i][j] != result[i][j]) {
                transf = REFLECTION;
                if (pattern[i][n - j - 1] != result[i][j])
                    return INVALID;
            }
    return transf;
}

int
ninety_deg(char pattern[][MAXSIZE], char result[][MAXSIZE], int n)
{
    int transf = DEG90;
    for (int j = 0; j < n; j++)
        for (int i = 0; i < n; i++)
            if (pattern[n - i - 1][j] != result[j][i]) {
                transf = COMB;
                if (pattern[n - i - 1][n - j - 1] != result[j][i])
                    return INVALID;
            }
    return transf;
}

int
one_eighty_deg(char pattern[][MAXSIZE], char result[][MAXSIZE], int n)
{
    int transf = DEG180;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (pattern[n - i - 1][n - j - 1] != result[i][j]) {
                transf = COMB;
                if (pattern[n - i - 1][j] != result[i][j])
                    return INVALID;
            }
    return transf;
}

int
two_seventy_deg(char pattern[][MAXSIZE], char result[][MAXSIZE], int n)
{
    int transf = DEG270;
    for (int j = 0; j < n; j++)
        for (int i = 0; i < n; i++)
            if (pattern[i][n - j - 1] != result[j][i]) {
                transf = COMB;
                if (pattern[i][j] != result[j][i])
                    return INVALID;
            }
    return transf;
}

int
main(int argc, const char *argv[])
{
    int n, transform;
    char pattern[MAXSIZE][MAXSIZE];
    char result[MAXSIZE][MAXSIZE];
    int (*func[])(char[][MAXSIZE], char[][MAXSIZE], int) = {
        zero_deg, ninety_deg, one_eighty_deg, two_seventy_deg };

    ifstream fin("transform.in");
    fin >> n;

    for (int i = 0; i < n; i++)
        fin >> pattern[i];

    for (int i = 0; i < n; i++)
        fin >> result[i];
    fin.close();

    transform = INVALID + 1;
    for (int i = 0; i < 4; i++)
        transform = min(transform, func[i](pattern, result, n));

    ofstream fout("transform.out");
    fout << transform << endl;
    fout.close();

    return 0;
}
