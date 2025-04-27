#include <iostream>
#include <fstream>

#include "charUtils.h"
#include "client.h"
#include "clientService.h"
#include "searchAlgorithm.h"
#include "checker.h"

using namespace std;

void searchLinearByName()
{
    if (checkFileEmpty() && checkFileOpen())
    {

        char searchName[100];
        cout << "Введите ФИО для поиска: ";
        cin.getline(searchName, 100);

        Client client;
        bool found = false;
        ifstream file("clients.bin", ios::binary);
        while (file.read(reinterpret_cast<char *>(&client), sizeof(Client)))
        {
            if (my_strcmp(client.name, searchName) == 0)
            {
                printClient(client);
                found = true;
            }
        }
        file.close();

        if (!found)
            cout << "Клиент не найден\n";
    }
    else
        return;
}

void searchLinearByProduct()
{
    if (checkFileEmpty() && checkFileOpen())
    {

        ifstream file("clients.bin", ios::binary);
        char searchProduct[100];
        cout << "Введите наименование товара: ";
        cin.getline(searchProduct, 100);

        Client client;
        bool found = false;
        while (file.read(reinterpret_cast<char *>(&client), sizeof(Client)))
        {
            if (my_strcmp(client.product, searchProduct) == 0)
            {
                printClient(client);
                found = true;
            }
        }
        file.close();

        if (!found)
            cout << "Продукт не найден\n";
    }
    else
        return;
}

void searchBinaryByName()
{
    if (checkFileEmpty() && checkFileOpen())
    {

        ifstream file("clients.bin", ios::binary);
        int count = file.tellg() / sizeof(Client);
        Client *clients = new Client[count];

        file.seekg(0);
        file.read(reinterpret_cast<char *>(clients), count * sizeof(Client));
        file.close();

        sortClientsByProduct(); // сортировка перед бинарной
        char searchProduct[100];
        cout << "Введите наименование товара: ";
        cin.getline(searchProduct, 100);

        int left = 0, right = count - 1;
        bool found = false;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            int cmp = my_strcmp(clients[mid].product, searchProduct);
            if (cmp == 0)
            {
                int i = mid;
                while (i >= 0 && my_strcmp(clients[i].product, searchProduct) == 0) // для того чтобы вывести все совпадения
                    --i;
                ++i;
                while (i < count && my_strcmp(clients[i].product, searchProduct) == 0)
                {
                    printClient(clients[i]);
                    ++i;
                    found = true;
                }
                break;
            }
            if (cmp < 0)
                left = mid + 1;
            else
                right = mid - 1;
        }

        delete[] clients;
        if (!found)
            cout << "Товар не найден\n";
    }
    else
        return;
}

void searchByProductAndDate()
{
    if (checkFileEmpty() && checkFileOpen())
    {

        ifstream file("clients.bin", ios::binary);

        char searchProduct[100];
        int day, month, year;

        cout << "Введите наименование товара: ";
        cin.getline(searchProduct, 100);

        bool valid = false;
        char data[256];

        while (!valid)
        {
            cout << "Введите дату(используйте . / -): ";
            cin.getline(data, 256);
            valid = isValidDate(data);
            if (!valid)
                cout << "Дата не корректна, повторите ввод. \n";
        }
        parseDate(data, &day, &month, &year);

        Client *temp = new Client[1000];
        int count = 0;

        Client client;
        while (file.read(reinterpret_cast<char *>(&client), sizeof(Client)))
        {
            if (my_strcmp(client.product, searchProduct) == 0 &&
                (client.year > year ||
                 (client.year == year && client.month > month) ||
                 (client.year == year && client.month == month && client.day > day)))
            {
                temp[count++] = client;
            }
        }
        file.close();

        if (count == 0)
        {
            cout << "Покупки не найдены\n";
            delete[] temp;
            return;
        }
        // сортируем по имени, методом вставок
        for (int i = 1; i < count; ++i)
        {
            Client key = temp[i];
            int j = i - 1;
            while (j >= 0 && my_strcmp(temp[j].name, key.name) > 0)
            {
                temp[j + 1] = temp[j];
                --j;
            }
            temp[j + 1] = key;
        }

        for (int i = 0; i < count; ++i)
        {
            printClient(temp[i]);
        }
        delete[] temp;
    }
    else
        return;
}
