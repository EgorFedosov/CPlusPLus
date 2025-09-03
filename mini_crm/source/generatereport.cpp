#include <iostream>
#include <fstream>

#include "client.h"
#include "generateReport.h"
#include "sortAlgorithm.h"
#include "charUtils.h"
#include "checker.h"

using namespace std;

void generateReport()
{
    if (checkFileOpen())
    {

        ifstream inFile("clients.bin", ios::binary);

        inFile.seekg(0, ios::end);
        int count = inFile.tellg() / sizeof(Client);
        if (count == 0)
        {
            cout << "Нет данных для отчета\n";
            return;
        }

        Client *clients = new Client[count];
        inFile.seekg(0);
        inFile.read(reinterpret_cast<char *>(clients), count * sizeof(Client));
        inFile.close();

        ofstream outFile("report.txt");
        if (!outFile)
        {
            cout << "Ошибка создания отчета\n";
            delete[] clients;
            return;
        }

        cout << "\n=== ОТЧЕТ ===\n";
        outFile << "=== ОТЧЕТ ===\n\n";

        // сортируем по названию
        sortQuickProduct(clients, 0, count - 1);

        // если один товар - сортируем по дате
        int startGroup = 0;
        for (int i = 1; i <= count; ++i)
        {
            if (i == count || my_strcmp(clients[i].product, clients[startGroup].product) != 0)
            {
                sortSelection(clients + startGroup, i - startGroup);
                startGroup = i;
            }
        }

        const char *currentProduct = clients[0].product;
        outFile << "Товар: " << currentProduct << "\n";
        cout << "Товар: " << currentProduct << "\n";

        for (int i = 0; i < count; ++i)
        {
            if (my_strcmp(clients[i].product, currentProduct) != 0)
            {
                currentProduct = clients[i].product;
                outFile << "\nТовар: " << currentProduct << "\n";
                cout << "\nТовар: " << currentProduct << "\n";
            }
            outFile << "  " << clients[i].day << "." << clients[i].month << "." << clients[i].year
                    << " - " << clients[i].name << " (" << clients[i].quantity << " шт.)\n";
            cout << "  " << clients[i].day << "." << clients[i].month << "." << clients[i].year
                 << " - " << clients[i].name << " (" << clients[i].quantity << " шт.)\n";
        }

        int maxQuantity = 0;
        const char *popularProduct = "";
        for (int i = 0; i < count;)
        {
            int total = 0; // общее количество покупок
            const char *product = clients[i].product;
            while (i < count && my_strcmp(clients[i].product, product) == 0)
            {
                total += clients[i].quantity;
                ++i;
            }
            if (total > maxQuantity)
            {
                maxQuantity = total;
                popularProduct = product;
            }
        }
        outFile << "\nСамый популярный товар: " << popularProduct << " (" << maxQuantity << " шт.)\n";
        cout << "\nСамый популярный товар: " << popularProduct << " (" << maxQuantity << " шт.)\n";

        struct ClientTotal
        {
            char name[100];
            double total;
        };

        ClientTotal *totals = new ClientTotal[count]; // Храним имя и сумму покупок
        int totalCount = 0;

        for (int i = 0; i < count; ++i)
        {
            bool found = false;
            for (int j = 0; j < totalCount; ++j)
            {
                if (my_strcmp(clients[i].name, totals[j].name) == 0)
                {
                    totals[j].total += clients[i].amount; // увеличиваем сумму для клиента
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                my_strcpy(totals[totalCount].name, clients[i].name); // копируем имя
                totals[totalCount].total = clients[i].amount;        // копируем сумму
                ++totalCount;
            }
        }

        double maxTotal = 0;
        const char *activeClient = "";
        for (int i = 0; i < totalCount; ++i)
        {
            if (totals[i].total > maxTotal)
            {
                maxTotal = totals[i].total;
                activeClient = totals[i].name;
            }
        }
        outFile << "Самый активный клиент: " << activeClient << " (Сумма: " << maxTotal << ")\n";
        cout << "Самый активный клиент: " << activeClient << " (Сумма: " << maxTotal << ")\n";

        delete[] clients;
        delete[] totals;
        outFile.close();
        cout << "\nОтчет сохранен в report.txt\n";
    }
    else
        return;
}