
#include "Client.h"

Client::Client(string n, string ci, string p, string d, int cnt, int s)
    : name(n), contact_info(ci), product(p),
      date_of_purchase(d), count_product(cnt), sum(s) {}

void Client::writeToFile(ofstream &outFile) const
{
    writeString(outFile, name);
    writeString(outFile, contact_info);
    writeString(outFile, product);
    writeString(outFile, date_of_purchase);

    outFile.write(reinterpret_cast<const char *>(&count_product), sizeof(count_product));
    outFile.write(reinterpret_cast<const char *>(&sum), sizeof(sum));
}

void Client::print() const
{
    cout << "Name: " << name << "\n"
         << "Contact: " << contact_info << "\n"
         << "Product: " << product << "\n"
         << "Date: " << date_of_purchase << "\n"
         << "Count: " << count_product << "\n"
         << "Sum: " << sum << "\n\n";
}

void Client::writeString(ofstream &outFile, const string &s)
{
    unsigned short len = s.size();
    outFile.write(reinterpret_cast<const char *>(&len), sizeof(len));
    outFile.write(s.c_str(), len);
}
