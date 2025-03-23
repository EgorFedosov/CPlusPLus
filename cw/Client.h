
#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

struct Client
{
    string name;
    string contact_info;
    string product;
    string date_of_purchase;
    int count_product;
    int sum;

    Client(string n, string ci, string p, string d, int cnt, int s);

    void writeToFile(ofstream &outFile) const;
    void print() const;

private:
    static void writeString(ofstream &outFile, const string &s);
};

#endif
