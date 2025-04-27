#include <type_traits>
#include <iostream>
#include <fstream>
#include "charUtils.h"
#include "client.h"

using namespace std;

bool checkFileOpen()
{
    ifstream file("clients.bin", ios::binary);
    if (!file)
    {
        cout << "Ошибка доступа к файлу, возможно, он не существует\n";
        return false;
    }else
        return true;
}

bool checkFileEmpty()
{
    ifstream file("clients.bin", ios::binary);
    file.seekg(0, ios::end);
    int count = file.tellg() / sizeof(Client);
    if (count == 0)
    {
        cout << "Файл пуст\n";
        return false;
    } else
        return true;
}

short checkChoice()
{
    char *end;
    long choice;
    bool valid;

    do
    {
        char input[256];
        cin.getline(input, 256);

        valid = true;
        if (my_strlen(input) == 0)
        {
            cout << "Ошибка: введите число от 0 до 15." << endl;
            valid = false;
            continue;
        }

        choice = strtol(input, &end, 10);

        if (end == input || *end != '\0')
        {
            cout << "Ошибка: введите  число от 0 до 15." << endl;
            valid = false;
        }
        else if (choice < 0 || choice > 14)
        {
            cout << "Ошибка: введите  число от 0 до 15." << endl;
            valid = false;
        }

    } while (!valid);

    return static_cast<short>(choice);
}

template <typename T>
T checkPositiveNum()
{
    char input[256];
    char *end;
    T value;
    bool valid;

    do
    {
        valid = true;
        cin.getline(input, 256);

        if constexpr (is_same_v<T, double>)
        {
            for (char *c = input; *c; ++c)
            {
                if (*c == ',')
                    *c = '.';
            }
        }

        if (my_strlen(input) == 0)
        {
            cout << "Ошибка: поле не может быть пустым." << endl;
            valid = false;
            continue;
        }

        if constexpr (is_same_v<T, int>)
        {
            value = strtol(input, &end, 10);
        }
        else
        {
            value = strtod(input, &end);
        }

        if (end == input || *end != '\0')
        {
            cout << "Ошибка: введите корректное число." << endl;
            valid = false;
        }
        else if (value <= 0)
        {
            cout << "Ошибка: число должно быть больше нуля." << endl;
            valid = false;
        }

    } while (!valid);

    return value;
}
template int checkPositiveNum<int>();
template double checkPositiveNum<double>();

bool checkPhoneNum(char *output, int maxLength)
{
    const size_t MAX_LENGTH = maxLength - 1;
    char input[256];
    bool valid;

    do
    {
        valid = true;
        cin.getline(input, 256);

        if (my_strlen(input) == 0)
        {
            cout << "Ошибка: введите номер телефона." << endl;
            valid = false;
            continue;
        }

        if (my_strlen(input) > MAX_LENGTH)
        {
            cout << "Ошибка: номер не должен превышать " << MAX_LENGTH << " символов." << endl;
            valid = false;
            continue;
        }

        if (input[0] == '+')
        {
            for (int i = 1; input[i]; i++)
            {
                if (!isdigit(input[i]))
                {
                    cout << "Ошибка: после '+' допускаются только цифры." << endl;
                    valid = false;
                    break;
                }
            }
        }
        else
        {
            for (int i = 0; input[i]; i++)
            {
                if (!isdigit(input[i]))
                {
                    cout << "Ошибка: введите только цифры или '+' в начале." << endl;
                    valid = false;
                    break;
                }
            }
        }

        if (!valid)
            continue;

        my_strncpy(output, input, maxLength);
        output[MAX_LENGTH] = '\0';

    } while (!valid);

    return true;
}

bool isValidDate(char *dateStr)
{
    char temp[11];
    int day = 0, month = 0, year = 0;
    int index = 0, numCount = 0;

    // заменяем разделители на пробел
    for (int i = 0; dateStr[i] && i < 10; i++)
    {
        if (my_isdigit(dateStr[i]))
        {
            temp[index++] = dateStr[i];
        }
        else if (dateStr[i] == '.' || dateStr[i] == '-' || dateStr[i] == ' ' || dateStr[i] == '/')
        {
            temp[index++] = ' ';
        }
    }
    temp[index] = '\0';

    for (int i = 0; temp[i]; i++)
    {
        if (my_isdigit(temp[i]))
        {
            int num = 0;
            while (temp[i] && my_isdigit(temp[i]))
            {
                num = num * 10 + (temp[i++] - '0'); // преобразуем символы в число
            }
            if (numCount == 0) // Первое число — день
                day = num;
            else if (numCount == 1)
                month = num;
            else if (numCount == 2)
                year = num;
            numCount++;
        }
    }

    if (numCount != 3)
        return false;
    if (year < 1 || month < 1 || month > 12 || day < 1 || year > 2025)
        return false;

    bool leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0); // проверка на високосный год
    if (month == 2)
    {
        if ((leap && day > 29) || (!leap && day > 28))
            return false;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        if (day > 30)
            return false;
    }
    else
    {
        if (day > 31)
            return false;
    }

    return true;
}

