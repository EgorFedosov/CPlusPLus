#include <fstream>
#include <iostream>

#include "charUtils.h"
#include "clientService.h"
#include "client.h"
#include "sortAlgorithm.h"
#include "fileManager.h"
#include "checker.h"

using namespace std;

void printClient(const Client &client)
{
    cout << "ФИО: " << client.name << "\n"
         << "Телефон: " << client.phone << "\n"
         << "Товар: " << client.product << "\n"
         << "Дата: " << client.day << "." << client.month << "." << client.year << "\n"
         << "Количество: " << client.quantity << "\n"
         << "Сумма: " << client.amount << "\n\n";
}

void addClient()
{

    Client newClient;
    cout << "Введите ФИО: ";
    cin.getline(newClient.name, 100);

    cout << "Телефон: ";
    checkPhoneNum(newClient.phone, 20);

    cout << "Товар: ";
    cin.getline(newClient.product, 100);

    cout << "Дата (используйте . / -): ";
    setDate(newClient);

    cout << "Количество: ";
    newClient.quantity = checkPositiveNum<int>();

    cout << "Сумма: ";
    newClient.amount = checkPositiveNum<double>();

    saveToBinaryFile(newClient);
    cout << "Клиент добавлен!\n";
}

void setDate(Client &client)
{
    char inputData[256];
    bool valid = false;

    while (!valid)
    {
        cin.getline(inputData, 256);

        if (isValidDate(inputData))
        {
            if (parseDate(inputData, &client.day, &client.month, &client.year))
            {
                valid = true;
            }
            else
            {
                cout << "Ошибка парсинга даты, повторите ввод" << endl;
            }
        }
        else
        {
            cout << "Дата не корректна, повторите ввод.\n";
        }
    }
}

void editClient()
{
    if (checkFileEmpty() && checkFileOpen())
    {

        fstream file("clients.bin", ios::in | ios::out | ios::binary);
        char searchName[100];
        cout << "Введите ФИО клиента для редактирования: ";
        cin.getline(searchName, 100);

        Client client;
        streampos pos;
        bool found = false;

        while (file.read(reinterpret_cast<char *>(&client), sizeof(Client)))
        {
            if (my_strcmp(client.name, searchName) == 0)
            {
                pos = file.tellg() - static_cast<streampos>(sizeof(Client)); // получаем позицию (конец прочтения - размер объекта)
                found = true;
                break;
            }
        }

        if (!found)
        {
            cout << "Клиент не найден\n";
            file.close();
            return;
        }

        int editChoice;
        cout << "Выберите поле для редактирования:\n"
             << "1. Телефон\n"
             << "2. Товар\n"
             << "3. Дата\n"
             << "4. Количество\n"
             << "5. Сумма\n"
             << "Ваш выбор: ";
        cin >> editChoice;
        cin.ignore();

        switch (editChoice)
        {
        case 1:
            cout << "Новый телефон: ";
            checkPhoneNum(client.phone, 20);
            break;
        case 2:
            cout << "Новый товар: ";
            cin.getline(client.product, 100);
            break;
        case 3:
            cout << "Дата (используйте . / -): ";
            setDate(client);
            break;
        case 4:
            cout << "Количество: ";
            client.quantity = checkPositiveNum<int>();
            break;
        case 5:
            cout << "Сумма: ";
            client.amount = checkPositiveNum<double>();
            break;
        default:
            cout << "Неверный выбор\n";
            file.close();
            return;
        }

        file.seekp(pos);                                                     // перемещаемся в начало client
        file.write(reinterpret_cast<const char *>(&client), sizeof(Client)); // перещаписываем весь объект, с учетом изменённого поля
        file.close();
        cout << "Данные успешно обновлены10\n";
    }
    else
        return;
}

void deleteClient()
{
    if (checkFileEmpty() && checkFileOpen())
    {
        char deleteName[100];
        cout << "Введите ФИО клиента для удаления: ";
        cin.getline(deleteName, 100);

        ifstream inFile("clients.bin", ios::binary); // Исходный файл (для чтения)
        ofstream outFile("temp.bin", ios::binary);   // Временный файл (для записи)

        if (!inFile || !outFile)
        {
            cout << "Ошибка при удалении\n";
            return;
        }

        Client client;
        bool found = false;

        while (inFile.read(reinterpret_cast<char *>(&client), sizeof(Client)))
        {
            if (my_strcmp(client.name, deleteName) != 0)
            {
                outFile.write(reinterpret_cast<const char *>(&client), sizeof(Client));
            }
            else
            {
                found = true;
            }
        }

        inFile.close();
        outFile.close();

        if (found)
        {
            remove("clients.bin");             // Удаляем исходный файл
            rename("temp.bin", "clients.bin"); // Переименовываем временный файл
            cout << "Запись успешно удалена\n";
        }
        else
        {
            remove("temp.bin"); // Удаляем временный файл, если клиент не найден
            cout << "Клиент не найден\n";
        }
    }
    else
        return;
}

void sortClientsByProduct()
{
    if (checkFileEmpty() && checkFileOpen())
    {

        fstream file("clients.bin", ios::in | ios::out | ios::binary);
        file.seekg(0, ios::end);
        int count = file.tellg() / sizeof(Client);

        Client *clients = new Client[count];
        file.seekg(0);
        file.read(reinterpret_cast<char *>(clients), count * sizeof(Client));
        file.close();

        sortQuickProduct(clients, 0, count - 1);

        file.open("clients.bin", ios::out | ios::binary | ios::trunc); // открываем для записи, если что-то есть - то удаляем
        file.write(reinterpret_cast<const char *>(clients), count * sizeof(Client));
        file.close();

        delete[] clients;
        cout << "Сортировка выполнена успешно\n";
    }
    else
        return;
}

void sortClientsByData()
{
    if (checkFileEmpty() && checkFileOpen())
    {

        fstream file("clients.bin", ios::in | ios::out | ios::binary);
        file.seekg(0, ios::end);
        int count = file.tellg() / sizeof(Client);

        Client *clients = new Client[count];
        file.seekg(0);
        file.read(reinterpret_cast<char *>(clients), count * sizeof(Client));
        file.close();

        sortSelection(clients, count);

        file.open("clients.bin", ios::out | ios::binary | ios::trunc); // открываем для записи, если что-то есть - то удаляем
        file.write(reinterpret_cast<const char *>(clients), count * sizeof(Client));
        file.close();

        delete[] clients;
        cout << "Сортировка выполнена успешно\n";
    }
    else
        return;
}

void sortClientsByName()
{
    if (checkFileEmpty() && checkFileOpen())
    {
        fstream file("clients.bin", ios::in | ios::out | ios::binary);
        file.seekg(0, ios::end);
        int count = file.tellg() / sizeof(Client);

        Client *clients = new Client[count];
        file.seekg(0);
        file.read(reinterpret_cast<char *>(clients), count * sizeof(Client));
        file.close();

        sortInsertion(clients, count);

        file.open("clients.bin", ios::out | ios::binary | ios::trunc); // открываем для записи, если что-то есть - то удаляем
        file.write(reinterpret_cast<const char *>(clients), count * sizeof(Client));
        file.close();

        delete[] clients;
        cout << "Сортировка выполнена успешно\n";
    }
    else
        return;
}

void getCountClient(){
    if (checkFileOpen())
    {
        fstream file("clients.bin", ios::in | ios::out | ios::binary);
        file.seekg(0, ios::end);
        int count = file.tellg() / sizeof(Client);

        cout << "Всего клиентов: " << count << endl;
    } else
        return;
}

void generateRandomClient()
{
    int count;
    cout << "Введите количество клиентов для генерации: ";
    cin >> count;
    cin.ignore();

    const char *maleFirstNames[] = {"Иван", "Петр", "Дмитрий"};
    const char *femaleFirstNames[] = {"Мария", "Анна"};
    const char *maleLastNames[] = {"Иванов", "Петров", "Смирнов", "Кузнецов", "Васильев"};
    const char *femaleLastNames[] = {"Иванова", "Петрова", "Смирнова", "Кузнецова", "Васильева"};
    const char *malePatronymics[] = {"Иванович", "Петрович", "Сергеевич"};
    const char *femalePatronymics[] = {"Алексеевна", "Дмитриевна", "Ивановна"};
    const char *products[] = {"Ноутбук", "Смартфон", "Телевизор", "Холодильник", "Пылесос"};
    for (int i = 0; i < count; i++)
    {
        Client newClient;

        bool isMale = rand() % 2;

        const char *firstName;
        const char *lastName;
        const char *patronymic;

        if (isMale)
        {
            firstName = maleFirstNames[rand() % 3];
            lastName = maleLastNames[rand() % 5];
            patronymic = malePatronymics[rand() % 3];
        }
        else
        {
            firstName = femaleFirstNames[rand() % 2];
            lastName = femaleLastNames[rand() % 5];
            patronymic = femalePatronymics[rand() % 3];
        }

        char fullName[100] = "";
        my_strncat(fullName, lastName, 99);
        my_strncat(fullName, " ", 99 - my_strlen(fullName));
        my_strncat(fullName, firstName, 99 - my_strlen(fullName));
        my_strncat(fullName, " ", 99 - my_strlen(fullName));
        my_strncat(fullName, patronymic, 99 - my_strlen(fullName));

        my_strncpy(newClient.name, fullName, 99);
        newClient.name[99] = '\0';

        char phone[20] = "9";
        for (int i = 0; i < 9; i++)
        {
            char digit[2] = {static_cast<char>('0' + rand() % 10), '\0'};
            my_strncat(phone, digit, 19 - my_strlen(phone));
        }
        my_strncpy(newClient.phone, phone, 19);
        newClient.phone[19] = '\0';

        my_strncpy(newClient.product, products[rand() % 5], 99);
        newClient.product[99] = '\0';

        newClient.day = 1 + rand() % 31;
        newClient.month = 1 + rand() % 12;
        newClient.year = 2000 + rand() % 24;

        newClient.quantity = 1 + rand() % 100;
        newClient.amount = 100.0 + (rand() % 990000) / 100.0;

        saveToBinaryFile(newClient);
    }
    cout << "Сгенерировано " << count << " клиентов!\n";
}
