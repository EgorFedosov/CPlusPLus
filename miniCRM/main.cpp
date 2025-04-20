#include <iostream>
#include <fstream>
#include <windows.h>
// Русский, бинарная сортировка отсотировать перед началом, проверки на ввод(дату ввести по разными способами), высокосный год
using namespace std;

struct Client
{
    char name[100];
    char phone[20];
    char product[100];
    int day;
    int month;
    int year;
    int quantity;
    double amount;
};

int my_strcmp(const char *str1, const char *str2)
{

    while (*str1 != '\0' && (*str1 == *str2))
    {
        str1++;
        str2++;
    }

    return static_cast<int>(static_cast<unsigned char>(*str1) -
                            static_cast<unsigned char>(*str2));
}
char *my_strcpy(char *dest, const char *src)
{
    char *original_dest = dest;
    while ((*dest++ = *src++) != '\0')
        ;
    return original_dest;
}
char *my_strncpy(char *dest, const char *src, size_t n)
{
    char *original_dest = dest;
    size_t i;

    for (i = 0; i < n && src[i] != '\0'; ++i)
    {
        dest[i] = src[i];
    }

    for (; i < n; ++i)
    {
        dest[i] = '\0';
    }

    return original_dest;
}
void printClient(const Client &client)
{
    cout << "ФИО: " << client.name << "\n"
         << "Телефон: " << client.phone << "\n"
         << "Товар: " << client.product << "\n"
         << "Дата: " << client.day << "." << client.month << "." << client.year << "\n"
         << "Количество: " << client.quantity << "\n"
         << "Сумма: " << client.amount << "\n\n";
}

void saveToBinaryFile(const Client &client)
{
    ofstream file("clients.bin", ios::binary | ios::app); // app -открываем файл в режиме добавления, то есть не пересоздаем новый
    if (file)
    {
        file.write(reinterpret_cast<const char *>(&client), sizeof(Client)); // преобразуем указатель и записываем столько байтов, сколько занимает объект
        file.close();
    }
}

void displayBinaryFile()
{
    ifstream file("clients.bin", ios::binary); // создаем объект
    if (!file)
    {
        cout << "Ошибка открытия файла\n";
        return;
    }

    Client client;
    while (file.read(reinterpret_cast<char *>(&client), sizeof(Client))) // читаем файл
    {
        printClient(client);
    }

    file.close();
}

void editClient()
{
    fstream file("clients.bin", ios::in | ios::out | ios::binary);
    if (!file)
    {
        cout << "Ошибка открытия файла\n";
        return;
    }

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
        cin.getline(client.phone, 20);
        break;
    case 2:
        cout << "Новый товар: ";
        cin.getline(client.product, 100);
        break;
    case 3:
        cout << "Новая дата (дд мм гггг): ";
        cin >> client.day >> client.month >> client.year;
        cin.ignore();
        break;
    case 4:
        cout << "Новое количество: ";
        cin >> client.quantity;
        cin.ignore();
        break;
    case 5:
        cout << "Новая сумма: ";
        cin >> client.amount;
        cin.ignore();
        break;
    default:
        cout << "Неверный выбор\n";
        file.close();
        return;
    }

    file.seekp(pos);                                                     // перемещаемся в начало client
    file.write(reinterpret_cast<const char *>(&client), sizeof(Client)); // перещаписываем весь объект, с учетом изменённого поля
    file.close();
    cout << "Данные успешно обновлены!\n";
}

void deleteClient()
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

void quickSortProduct(Client arr[], int left, int right)
{
    if (left >= right)
        return;
    int i = left, j = right;
    Client pivot = arr[left + (right - left) / 2];

    while (i <= j)
    {
        while (my_strcmp(arr[i].product, pivot.product) < 0)
            i++;
        while (my_strcmp(arr[j].product, pivot.product) > 0)
            j--;
        if (i <= j)
        {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    quickSortProduct(arr, left, j);
    quickSortProduct(arr, i, right);
}

int compareDates(Client a, Client b)
{

    if (a.year != b.year)
        return a.year - b.year;
    if (a.month != b.month)
        return a.month - b.month;
    return a.day - b.day;
}
void selectionSortDate(Client arr[], int size)
{
    for (int i = 0; i < size - 1; ++i)
    {
        int minDateIndex = i;
        for (int j = i + 1; j < size; ++j)
        {
            if (compareDates(arr[j], arr[minDateIndex]) < 0)
            {
                minDateIndex = j;
            }
        }
        if (minDateIndex != i)
        {
            swap(arr[i], arr[minDateIndex]);
        }
    }
}

void insertionSortName(Client arr[], int size)
{
    for (int i = 1; i < size; ++i)
    {
        Client key = arr[i];
        int j = i - 1;
        while (j >= 0 && my_strcmp(arr[j].name, key.name) > 0)
        {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

void sortClients(int sortType)
{
    fstream file("clients.bin", ios::in | ios::out | ios::binary);
    if (!file)
    {
        cout << "Ошибка доступа к файлу\n";
        return;
    }

    file.seekg(0, ios::end); // указатель в конец
    int count = file.tellg() / sizeof(Client);
    if (count == 0)
    {
        cout << "Файл пуст\n";
        return;
    }

    Client *clients = new Client[count];
    file.seekg(0);                                                        // указатель в начало
    file.read(reinterpret_cast<char *>(clients), count * sizeof(Client)); // считываем
    file.close();

    switch (sortType)
    {
    case 1:
        quickSortProduct(clients, 0, count - 1);
        break;
    case 2:
        selectionSortDate(clients, count);
        break;
    case 3:
        insertionSortName(clients, count);
        break;
    default:
        return;
    }

    file.open("clients.bin", ios::out | ios::binary | ios::trunc); // открываем для записи, если что-то есть - то удаляем
    file.write(reinterpret_cast<const char *>(clients), count * sizeof(Client));
    file.close();

    delete[] clients;
    cout << "Сортировка выполнена успешно\n";
}

void linearSearchByName()
{
    char searchName[100];
    cout << "Введите ФИО для поиска: ";
    cin.getline(searchName, 100);

    ifstream file("clients.bin", ios::binary);
    if (!file)
    {
        cout << "Ошибка доступа к файлу\n";
        return;
    }

    Client client;
    bool found = false;
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

void binarySearchByProduct()
{
    ifstream file("clients.bin", ios::binary);
    if (!file)
    {
        cout << "Ошибка доступа к файлу\n";
        return;
    }

    file.seekg(0, ios::end);
    int count = file.tellg() / sizeof(Client);
    if (count == 0)
    {
        cout << "Файл пуст\n";
        return;
    }

    Client *clients = new Client[count];
    file.seekg(0);
    file.read(reinterpret_cast<char *>(clients), count * sizeof(Client));
    file.close();

    bool sorted = true;
    for (int i = 1; i < count; ++i)
    {
        if (my_strcmp(clients[i].product, clients[i - 1].product) < 0)
        {
            sorted = false;
            break;
        }
    }
    if (!sorted)
    {
        cout << "Данные не отсортированы по товару\n";
        delete[] clients;
        return;
    }

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

void searchByProductAndDate()
{
    char searchProduct[100];
    int day, month, year;

    cout << "Введите наименование товара: ";
    cin.getline(searchProduct, 100);
    cout << "Введите дату (дд мм гггг): ";
    cin >> day >> month >> year;
    cin.ignore();

    ifstream file("clients.bin", ios::binary);
    if (!file)
    {
        cout << "Ошибка доступа к файлу\n";
        return;
    }

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

void generateReport()
{
    ifstream inFile("clients.bin", ios::binary);
    if (!inFile)
    {
        cout << "Ошибка доступа к файлу\n";
        return;
    }

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
    quickSortProduct(clients, 0, count - 1);

    // если один товар - сортируем по дате
    int startGroup = 0;
    for (int i = 1; i <= count; ++i)
    {
        if (i == count || my_strcmp(clients[i].product, clients[startGroup].product) != 0)
        {
            selectionSortDate(clients + startGroup, i - startGroup);
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

void generateRandomClients()
{
    srand(time(0));
    const string names[] = {"Anrey", "Sasha", "Tanus", "Simple", "Dima", "Vova"};
    const string surnames[] = {"Good", "Peep", "Jak", "Nau", "Volkov"};
    const string patronymics[] = {"Cas", "das", "Veel", "Sam"};
    const string products[] = {"iphone", "ipad", "bmw m3", "audi rs 5", "benz"};
    const string operators[] = {"25", "29", "33", "44"};

    int count;
    cout << "Введите количество клиентов для генерации (max 100): ";
    cin >> count;
    cin.ignore();
    if (count < 1 || count > 100)
    {
        cout << "Неверное количество\n";
        return;
    }

    ofstream file("clients.bin", ios::binary | ios::app);
    if (!file)
    {
        cout << "Ошибка записи файла\n";
        return;
    }

    for (int i = 0; i < count; ++i)
    {
        Client client;
        string fullName = surnames[rand() % 5] + " " +
                          names[rand() % 6] + " " +
                          patronymics[rand() % 4];
        my_strncpy(client.name, fullName.c_str(), 99);
        client.name[99] = '\0';

        string phone = "+375" + operators[rand() % 4];
        for (int j = 0; j < 7; ++j)
        {
            phone += to_string(rand() % 10);
        }
        my_strncpy(client.phone, phone.c_str(), 19);
        client.phone[19] = '\0';

        string product = products[rand() % 5];
        my_strncpy(client.product, product.c_str(), 99);
        client.product[99] = '\0';

        client.day = 1 + rand() % 28;
        client.month = 1 + rand() % 12;
        client.year = 2020 + rand() % 5;

        client.quantity = 1 + rand() % 5;
        client.amount = 100.0 + rand() % 10000;

        file.write(reinterpret_cast<const char *>(&client), sizeof(Client));
    }

    file.close();
    cout << "Сгенерировано " << count << " клиентов\n";
}

size_t my_strlen(const char *str)
{
    size_t length = 0;
    while (str[length] != '\0')
    {
        ++length;
    }
    return length;
}

bool my_isalpha(char ch)
{
    if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') ||
        (ch >= 'А' && ch <= 'Я') || (ch >= 'а' && ch <= 'я'))
    {
        return true;
    }
    return false;
}

int my_strncmp(const char *str1, const char *str2, size_t n)
{
    for (size_t i = 0; i < n; ++i)
    {
        if (str1[i] == '\0' || str2[i] == '\0' || str1[i] != str2[i])
        {
            return static_cast<int>(static_cast<unsigned char>(str1[i]) -
                                    static_cast<unsigned char>(str2[i]));
        }
    }
    return 0;
}

bool my_isdigit(char ch)
{
    return (ch >= '0' && ch <= '9');
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int choice;
    do
    {
        cout << endl
             << endl
             << "=== ГЛАВНОЕ МЕНЮ ===\n"
             << "1. Добавить клиента\n"
             << "2. Просмотреть записи\n"
             << "3. Редактировать клиента\n"
             << "4. Удалить клиента\n"
             << "5. Сортировка\n"
             << "6. Поиск\n"
             << "7. Создать отчет\n"
             << "8. Добавить рандомных клиентов\n"
             << "0. Выход\n"
             << "Выберите действие: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
        {
            Client newClient;

            while (true)
            {
                cout << "Введите ФИО (не более 99 символов, только буквы и пробелы): ";
                cin.getline(newClient.name, 100);

                if (my_strlen(newClient.name) == 0)
                {
                    cout << "Ошибка: ФИО не может быть пустым.\n";
                    continue;
                }

                bool isValid = true;
                for (int i = 0; i < my_strlen(newClient.name); ++i)
                {
                    if (!my_isalpha(newClient.name[i]) && newClient.name[i] != ' ')
                    {
                        isValid = false;
                        break;
                    }
                }

                if (!isValid)
                {
                    cout << "Ошибка: ФИО должно содержать только буквы и пробелы.\n";
                    continue;
                }

                break;
            }

            while (true)
            {
                cout << "Введите телефон: ";
                cin.getline(newClient.phone, 20);

                if (my_strlen(newClient.phone) == 0)
                {
                    cout << "Ошибка: Телефон не может быть пустым.\n";
                    continue;
                }
                bool isCorrect = true;
                for (int i = 0; newClient.phone[i] != '\0'; i++)
                {
                    if (!my_isdigit(newClient.phone[i]) && newClient.phone[i] != '+')
                    {
                        isCorrect = false;
                        cout << "Ошибка: Некорректные данные номера телефона.\n";
                        break;
                    }
                }
                if (isCorrect)
                    break;
            }

            while (true)
            {
                cout << "Введите наименование товара: ";
                cin.getline(newClient.product, 100);

                if (my_strlen(newClient.product) == 0)
                {
                    cout << "Ошибка: Наименование товара не может быть пустым.\n";
                    continue;
                }

                bool isValid = true;
                for (int i = 0; i < my_strlen(newClient.product); ++i)
                {
                    if (!my_isalpha(newClient.product[i]) && newClient.product[i] != ' ' && !my_isdigit(newClient.product[i]))
                    {
                        isValid = false;
                        break;
                    }
                }

                if (!isValid)
                {
                    cout << "Ошибка: Наименование товара должно содержать только буквы, пробелы и числа .\n";
                    continue;
                }

                break;
            }

            while (true)
            {
                cout << "Введите дату (дд мм гггг): ";
                cin >> newClient.day >> newClient.month >> newClient.year;
                cin.ignore();

                if (newClient.day < 1 || newClient.day > 31 ||
                    newClient.month < 1 || newClient.month > 12)
                {
                    cout << "Ошибка: Некорректная дата. День: 1-31, Месяц: 1-12.\n";
                    continue;
                }

                // if (!my_isdigit(newClient.day) || !my_isdigit(newClient.month) || !my_isdigit(newClient.year))
                // {
                //     cout << "Ошибка: Некорректная дата.\n";
                //     continue;
                // }
                break;
            }

            while (true)
            {
                cout << "Введите количество: ";
                cin >> newClient.quantity;
                cin.ignore();

                if (newClient.quantity <= 0)
                {
                    cout << "Ошибка: Количество должно быть больше нуля.\n";
                    continue;
                }

                break;
            }

            while (true)
            {
                cout << "Введите сумму: ";
                cin >> newClient.amount;
                cin.ignore();

                if (newClient.amount <= 0)
                {
                    cout << "Ошибка: Сумма должна быть больше нуля.\n";
                    continue;
                }

                break;
            }

            saveToBinaryFile(newClient);

            break;
        }
        case 2:
        {
            displayBinaryFile();
            break;
        }
        case 3:
        {
            editClient();
            break;
        }
        case 4:
        {
            deleteClient();
            break;
        }
        case 5:
        {
            int sortType;
            cout << "Выберите тип сортировки:\n"
                 << "1. По наименованию товара\n"
                 << "2. По дате покупки\n"
                 << "3. По ФИО клиента\n"
                 << "Ваш выбор: ";
            cin >> sortType;
            sortClients(sortType);
            break;
        }
        case 6:
        {
            int searchType;
            cout << "=== МЕНЮ ПОИСКА ===\n"
                 << "1. Линейный поиск по ФИО\n"
                 << "2. Бинарный поиск по товару\n"
                 << "3. Поиск покупок по товару и дате\n"
                 << "Ваш выбор: ";
            cin >> searchType;
            cin.ignore();

            switch (searchType)
            {
            case 1:
                linearSearchByName();
                break;
            case 2:
                binarySearchByProduct();
                break;
            case 3:
                searchByProductAndDate();
                break;
            default:
                cout << "Неверный выбор\n";
            }
            break;
        }
        case 7:
        {
            generateReport();
            break;
        }
        case 8:
        {
            generateRandomClients();
            break;
        }
        case 0:
            cout << "Выход из программы.\n";
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);

    return 0;
}