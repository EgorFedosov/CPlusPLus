#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Client
{
    string name;
    string contact_info;
    string product;
    string date_of_purchase;
    int count_product;
    int sum;

    Client(string n, string ci, string p, string d, int cnt, int s)
        : name(n), contact_info(ci), product(p),
          date_of_purchase(d), count_product(cnt), sum(s) {}

    void writeToFile(ofstream &outFile) const
    {
        writeString(outFile, name);
        writeString(outFile, contact_info);
        writeString(outFile, product);
        writeString(outFile, date_of_purchase);

        outFile.write(reinterpret_cast<const char *>(&count_product), sizeof(count_product));
        outFile.write(reinterpret_cast<const char *>(&sum), sizeof(sum));
    }

    void print() const
    {
        cout << "Name: " << name << "\n"
             << "Contact: " << contact_info << "\n"
             << "Product: " << product << "\n"
             << "Date: " << date_of_purchase << "\n"
             << "Count: " << count_product << "\n"
             << "Sum: " << sum << "\n\n";
    }

private:
    static void writeString(ofstream &outFile, const string &s)
    {
        unsigned short len = s.size();
        outFile.write(reinterpret_cast<const char *>(&len), sizeof(len));
        outFile.write(s.c_str(), len);
    }
};

int main()
{
    short num;
    do
    {
        cout << "\n--- Система учета клиентов и продаж ---\n";
        cout << "1. Добавить клиента\n"
             << "2. Поиск\n"
             << "3. Сортировка\n"
             << "4. Поиск покупок по товарам\n"
             << "5. Статистика\n"
             << "0. Выход\n"
             << "Выберите действие: ";
        cin >> num;

        switch (num)
        {
        case 1:
        {
            cin.ignore();
            string name, contact, product, date;
            int count, sum;

            cout << "ФИО клиента: ";
            getline(cin, name);

            cout << "Контактные данные: ";
            getline(cin, contact);

            cout << "Товар: ";
            getline(cin, product);

            cout << "Дата (ДД-ММ-ГГГГ): ";
            getline(cin, date);

            cout << "Количество: ";
            cin >> count;

            cout << "Сумма: ";
            cin >> sum;

            ofstream outFile("clients.bin", ios::binary | ios::app);
            if (!outFile)
            {
                cout << "Ошибка открытия файла!\n";
                break;
            }

            Client client(name, contact, product, date, count, sum);
            client.writeToFile(outFile);
            cout << "Данные сохранены!\n";
            outFile.close();
            break;
        }

        case 2:
        {
            cout << "Выберите тип поиска: \n1) Линейный поиск по ФИО клиента\n2) Бинарный поиск по наименованию товара\n";
            short t;
            cin >> t;

            if (t != 1 && t != 2)
            {
                cout << "Ошибка ввода\n";
                break;
            }

            // Здесь нужно добавить реализацию поиска
            cout << "Функционал поиска в разработке...\n";
            break;
        }

        case 3:
            cout << "Функционал сортировки в разработке...\n";
            break;

        case 4:
            cout << "Поиск покупок по товарам в разработке...\n";
            break;

        case 5:
            cout << "Статистика в разработке...\n";
            break;

        case 0:
            cout << "Выход...\n";
            break;

        default:
            cout << "Неверный выбор!\n";
        }
    } while (num != 0);

    return 0;
}