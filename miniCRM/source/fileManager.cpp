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
    ifstream file("clients.bin", ios::binary);  
    checkFileOpen();
    checkFileEmpty();

    Client client;
    while (file.read(reinterpret_cast<char *>(&client), sizeof(Client))) 
    {
        printClient(client);
    }

    file.close();
}

void removeBinaryFile(){

    checkFileOpen();
    checkFileEmpty();

    if (remove("clients.bin") == 0)
        cout << "Файл clients.bin успешно удален\n";
}