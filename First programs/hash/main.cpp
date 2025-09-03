#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>
using namespace std;

struct Car
{
    char brand[16];
    unsigned short maxSpeed;
    short year;
};

struct HashNode
{
    Car data;
    bool status = false;
};

int hashFirst(int key, int size)
{
    return key % size;
}

int hashSecondary(int key, int size)
{
    return 1 + (key % (size - 2));
}

void insert(Car item, HashNode table[], int size)
{
    int key = item.maxSpeed;
    int index = hashFirst(key, size);
    int step = hashSecondary(key, size);

    for (int i = 0; i < size; ++i)
    {
        if (!table[index].status)
        {
            table[index].data = item;   
            table[index].status = true;
            return;
        }
        cout<<  "Key: " << key << "Index: " << index  << "step" << step << endl;
        index = (index - step + size) % size;

    }

    cout << "Хеш-таблица переполнена!" << endl;
}

const Car *search(int key, const HashNode table[], int size)
{
    int index = hashFirst(key, size);
    int step = hashSecondary(key, size);

    for (int i = 0; i < size; ++i)
    {
        if (!table[index].status)
            return nullptr;

        if (table[index].data.maxSpeed == key)
            return &table[index].data;

        index = (index - step + size) % size;
    }

    return nullptr;
}

void randomCars(Car cars[], int size)
{
    const char *brands[] = {"Toyota", "Honda", "Ford", "BMW", "Mercedes",
                            "Audi", "Volkswagen", "Hyundai", "Tesla", "Porsche"};
    int brandCount = sizeof(brands) / sizeof(brands[0]);

    for (int i = 0; i < size; ++i)
    {
        strcpy(cars[i].brand, brands[rand() % brandCount]);
        cars[i].maxSpeed = 100 + rand() % 201;
        cars[i].year = 1990 + rand() % 36;
    }
}

int main()
{
    srand(time(0));

    const int ARRAY_SIZE = 10;
    const int HASH_TABLE_SIZE = 15;

    Car cars[ARRAY_SIZE];
    HashNode hashTable[HASH_TABLE_SIZE] = {};

    int choice;
    bool dataLoaded = false;

    while (true)
    {
        cout << "\n--- МЕНЮ ---\n";
        cout << "1. Добавить данные вручную\n";
        cout << "2. Сгенерировать случайные данные\n";
        cout << "3. Просмотреть исходный массив\n";
        cout << "4. Просмотреть хеш-таблицу\n";
        cout << "5. Поиск по максимальной скорости\n";
        cout << "0. Выход\n";
        cout << "Выберите пункт: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            dataLoaded = true;
            for (int i = 0; i < ARRAY_SIZE; ++i)
            {
                cout << "\nАвтомобиль #" << i + 1 << ":\n";
                cin.ignore();
                cout << "Марка: ";
                cin.getline(cars[i].brand, 16);
                cout << "Максимальная скорость: ";
                cin >> cars[i].maxSpeed;
                cout << "Год выпуска: ";
                cin >> cars[i].year;
            }
            break;
        }

        case 2:
        {
            dataLoaded = true;
            randomCars(cars, ARRAY_SIZE);
            cout << "\nСлучайные данные сгенерированы!\n";
            break;
        }

        case 3:
        {
            if (dataLoaded)
            {
                cout << "\nИсходный массив автомобилей:" << endl;
                for (int i = 0; i < ARRAY_SIZE; ++i)
                {
                    cout << cars[i].brand << ", "
                         << cars[i].maxSpeed << " км/ч, "
                         << cars[i].year << endl;
                }
            }
            else
            {
                cout << "Сначала введите или сгенерируйте данные.\n";
            }
            break;
        }

        case 4:
        {
            if (dataLoaded)
            {
                for (int i = 0; i < ARRAY_SIZE; i++)
                {
                    insert(cars[i], hashTable, HASH_TABLE_SIZE);
                }
                cout << "\n--- ХЕШ-ТАБЛИЦА ---" << endl;
                for (int i = 0; i < HASH_TABLE_SIZE; ++i)
                {
                    if (hashTable[i].status)
                    {
                        cout << i << ": "
                             << hashTable[i].data.brand << ", "
                             << hashTable[i].data.maxSpeed << " км/ч, "
                             << hashTable[i].data.year << endl;
                    }
                    else
                    {
                        cout << i << ": [пусто]" << endl;
                    }
                }
            }
            else
            {
                cout << "Сначала введите или сгенерируйте данные.\n";
            }
            break;
        }

        case 5:
        {
            if (dataLoaded)
            {
                int speedToFind;
                cout << "Введите скорость для поиска: ";
                cin >> speedToFind;

                const Car *foundCar = search(speedToFind, hashTable, HASH_TABLE_SIZE);
                if (foundCar)
                {
                    cout << "Автомобиль найден:\n"
                         << foundCar->brand << ", "
                         << foundCar->maxSpeed << " км/ч, "
                         << foundCar->year << endl;
                }
                else
                {
                    cout << "Автомобиль не найден.\n";
                }
            }
            else
            {
                cout << "Сначала введите или сгенерируйте данные.\n";
            }
            break;
        }

        case 0:
        {
            cout << "Выход из программы." << endl;
            return 0;
        }

        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
        }
    }

    return 0;
}