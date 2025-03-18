#include "Client.h"
#include "iostream"

Client::Client(string name, string contact_info, string product, string date_of_purchase,
               int count_product, int sum)
{
    this->name = name;
    this->contact_info = contact_info;
    this->product = product;
    this->date_of_purchase = date_of_purchase;
    this->count_product = count_product;
    this->sum = sum;
}

void Client::writeToFile(ofstream &outFile) const
{
    unsigned short nameLength = name.size();
    unsigned short contactInfoLength = contact_info.size();
    unsigned short productLength = product.size();
    unsigned short dateOfPurchaseLength = date_of_purchase.size();

    outFile.write(reinterpret_cast<const char *>(&nameLength), sizeof(nameLength));
    outFile.write(name.c_str(), name.size());

    outFile.write(reinterpret_cast<const char *>(&contactInfoLength), sizeof(contactInfoLength));
    outFile.write(contact_info.c_str(), contact_info.size());

    outFile.write(reinterpret_cast<const char *>(&productLength), sizeof(productLength));
    outFile.write(product.c_str(), product.size());

    outFile.write(reinterpret_cast<const char *>(&dateOfPurchaseLength), sizeof(dateOfPurchaseLength));
    outFile.write(date_of_purchase.c_str(), date_of_purchase.size());

    outFile.write(reinterpret_cast<const char *>(&count_product), sizeof(count_product));
    outFile.write(reinterpret_cast<const char *>(&sum), sizeof(sum));
}

void Client::print() const
{
    cout << "Name: " << name << "\n"
         << "Contact: " << contact_info << "\n"
         << "Product: " << product << "\n"
         << "Date of Purchase: " << date_of_purchase << "\n"
         << "Count: " << count_product << "\n"
         << "Sum: " << sum << "\n";
}

string Client::getName() const { return name; }
string Client::getContactInfo() const { return contact_info; }
string Client::getProduct() const { return product; }
string Client::getDateOfPurchase() const { return date_of_purchase; }
int Client::getCountProduct() const { return count_product; }
int Client::getSum() const { return sum; }
