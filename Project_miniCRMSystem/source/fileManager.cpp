#include <iostream>
#include <fstream>

#include "fileManager.h"
#include "clientService.h"
#include "checker.h"

using namespace std;

void saveToBinaryFile(const Client &client)
{
    ofstream file("clients.bin", ios::binary | ios::app); // app -открываем файл в режиме добавления, если нет файлы - создаем
    if (file)
    {
        file.write(reinterpret_cast<const char *>(&client), sizeof(Client)); // преобразуем указатель и записываем столько байтов, сколько занимает объект
        file.close();
    }
}

void displayBinaryFile()
{
    if (checkFileEmpty() && checkFileOpen())
    {
        ifstream file("clients.bin", ios::binary);

        Client client;
        while (file.read(reinterpret_cast<char *>(&client), sizeof(Client)))
        {
            printClient(client);
        }

        file.close();
    }
    else
        return;
}

void removeClients()
{
    if (checkFileOpen() && checkFileEmpty())
    {
        ofstream file("clients.bin", ios::binary | ios::trunc); // очищаем содержимое файла
        if (file)
        {
            cout << "Все записи клиентов были удалены.\n";
            file.close();
        }
    }
}