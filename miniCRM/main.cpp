#include <iostream>
#include <ctime>

#include "sortAlgorithm.h"
#include "searchAlgorithm.h"
#include "clientService.h"
#include "fileManager.h"
#include "searchAlgorithm.h"
#include "generateReport.h"
#include "checker.h"

using namespace std;

int main()
{
    srand(time(0));
    short choice = 0;
    do
    {

        cout << "\nМеню:\n";
        cout << "1. Добавить клиента\n";
        cout << "2. Просмотреть записи\n"; 
        cout << "3. Редактировать клиента\n";
        cout << "4. Удалить клиента\n";
        cout << "5. Сортировать клиентов по наименованию товара(быстрая)\n";
        cout << "6. Сортировать клиентов по дате покупки(выбором)\n";
        cout << "7. Сортировать клиентов по ФИО(вставками)\n";
        cout << "8. Поиск по ФИО(линейный)\n";
        cout << "9. Поиск по товару (линейный)\n";
        cout << "10.Поиск по товару (бинарный)\n";
        cout << "11.Поиск по товару и дате(покупка товара после введенной даты)\n"; 

        cout << "12.Создать отчет\n";
        cout << "13. Сгенерировать случайных клиентов\n";
        cout << "14. Удалить всех клиентов\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";

        choice = checkChoice();

        switch (choice)
        {
        case 1:
            addClient();
            break;
        case 2:
            displayBinaryFile();
            break;
        case 3:
            editClient();
            break;
        case 4:
            deleteClient();
            break;
        case 5:
            sortClientsByProduct(); 
            break;
        case 6:
            sortClientsByData(); 
            break;
        case 7:
            sortClientsByName(); 
            break;
        case 8:
            searchLinearByName();
            break;
        case 9:
        {
            searchLinearByProduct();
            break;
        }
        case 10:
            searchBinaryByName();
            break;
        case 11:
            searchByProductAndDate();
            break;
        case 12:
            generateReport();
            break;

        case 13:
            generateRandomClient();
            break;
        case 14:
            removeBinaryFile();
            break;
        case 0:
            exit(0);
        default:
            cout << "Неверный выбор\n";
        }
    } while (choice != 0);
}