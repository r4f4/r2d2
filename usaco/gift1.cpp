/*
PROG: gift1
ID: r4f4rfs1
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

struct Person {
    int cash, balance;
    string name;
    vector<string> friends;

    Person(string name) {
        cash = balance = 0;
        this->name = name;
    }
};

int main(int argc, const char *argv[])
{
    int np;
    string name;
    vector<Person *> person;
    map<string, Person *> group; // Get person by name

    ifstream fin("gift1.in");
    fin >> np;

    for (int i = 0; i < np; i++) {
        fin >> name;
        person.push_back(new Person(name));
        group[name] = person[i];
    }

    for (int i = 0; i < np; i++) {
        int amount, nfriends;

        fin >> name;
        fin >> amount >> nfriends;
        group[name]->cash = group[name]->balance = amount;

        for (int j = 0; j < nfriends; j++) {
            string fname;

            fin >> fname;
            group[name]->friends.push_back(fname);
        }
    }
    fin.close();

    vector<Person *>::iterator it;
    for (it = person.begin(); it != person.end(); it++) {
        int ngiven = ((*it)->friends).size();
        if (!ngiven) continue;
        int given = (*it)->cash / ngiven;
        // Subtract an integer amount given to other people
        (*it)->balance -= given * ngiven;
        vector<string>::iterator to;
        for (to = ((*it)->friends).begin(); to != ((*it)->friends).end(); to++)
            group[*to]->balance += given;
    }

    ofstream fout("gift1.out");
    for (it = person.begin(); it != person.end(); it++)
        fout << (*it)->name << " " << (*it)->balance - (*it)->cash << endl;
    fout.close();

    return 0;
}
