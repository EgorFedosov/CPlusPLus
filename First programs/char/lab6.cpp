#include <iostream>
#include <string>

using namespace std;

int main()
{
    int size, a = 0;
    cout << "Size string: ";
    cin >> size;
    cin.ignore();

    char *stroka = new char[size + 1];
    char *rez = new char[size + 1];
    cout << "Enter string: ";
    cin.getline(stroka, size + 1);

    int numWord = 0;
    bool inWord = false;

    for (int i = 0; stroka[i] != '\0'; i++)
    {
        if (stroka[i] != ' ' && !inWord)
        {
            inWord = true;
            numWord++;
        }

        if (inWord && (numWord == 1 || numWord == 3 || numWord == 5))
        {
            rez[a] = stroka[i];
            a++;
        }

        if (stroka[i] == ' ' && inWord)
        {
            inWord = false;
        }
    }

    if (inWord && (numWord == 1 || numWord == 3 || numWord == 5)) // aaa
    {
        rez[a] = ' ';
        a++;
    }

    rez[a - 1] = '\0';

    cout << "rez: " << rez << endl;

    delete[] stroka;
    delete[] rez;

    return 0;
}
