#include <iostream>

using namespace std;

int main()
{

    int size = 0;
    cout << "Size str: ";
    cin >> size;
    cin.ignore();

    char *str = new char[size + 1];
    char *result = new char[2 * size + 1];
    cout << "Enter string: ";
    cin.getline(str, size + 1);

    int newchar = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == 'у' || str[i] == 'ё' || str[i] == 'Е' || str[i] == 'Ы' || str[i] == 'а' ||
            str[i] == 'У' || str[i] == 'Ё' || str[i] == 'е' || str[i] == 'ы' || str[i] == 'А' ||
            str[i] == 'о' || str[i] == 'Э' || str[i] == 'Я' || str[i] == 'и' || str[i] == 'ю' ||
            str[i] == 'О' || str[i] == 'э' || str[i] == 'я' || str[i] == 'И' || str[i] == 'Ю')
        {
            result[newchar] = '-';
        }
        result[newchar++] = str[i];
    }

    result[newchar] = '\0';

    cout << "Result: " << result << endl;

    delete[] str;
    delete[] result;

    return 0;
}
