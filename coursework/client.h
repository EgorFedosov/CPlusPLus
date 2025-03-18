#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <fstream>
using namespace std;

class Client
{
private:
    string name;
    string contact_info;
    string product;
    string date_of_purchase;
    int count_product;
    int sum;

public:
    Client(string name, string contact_info, string product, string date_of_purchase,
           int count_product, int sum);

    void writeToFile(ofstream &outFile) const;
    void print() const;

    string getName() const;
    string getContactInfo() const;
    string getProduct() const;
    string getDateOfPurchase() const;
    int getCountProduct() const;
    int getSum() const;
};

#endif
