#include <iostream>
using namespace std;

double defoltFun(int n)
{
    double result = 1.0;
    for (int i = 1; i < n; i++)
    {
        result = 1.0 / (1.0 + result);
    }
    return result;
}

double recurs(int n)
{
    if (n == 1)
    {
        return 1.0;
    }
    else
    {
        return 1.0 / (1.0 + recurs(n - 1));
    }
}

int main()
{
    int n;
    cout << "Введите количество ступеней (n): ";
    cin >> n;

    if (n <= 0)
    {
        cout << "Количество ступеней должно быть больше нуля!" << endl;
        return 1;
    }

    double result = defoltFun(n);
    cout << "Результат вычисления для n = " << n << " (обычная функция): " << result << endl;

    double recursiveResult = recurs(n);
    cout << "Результат вычисления для n = " << n << " (рекурсивная функция): " << recursiveResult << endl;

    return 0;
}
