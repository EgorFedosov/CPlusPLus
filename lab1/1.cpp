#include <iostream>
using namespace std;

double recurs(int n)
{
    if (n == 0)
    {
        return 0.0;
    }

    return 1 / (1 + recurs(n - 1));
}

double unrecurs(int n)
{
    double result = 0.0;

    for (int i = 0; i < n; i++)
    {
        result = 1 / (1 + result);
    }

    return result;
}

int main()
{
    int n;
    cout << "Enter N: ";
    cin >> n;

    if (n < 0)
    {
        cout << "Error N!";
        return 1;
    }

    double res = recurs(n);
    cout << "Result of a regular function: " << res << endl;

    res = unrecurs(n);
    cout << "Result of a recursive function: " << res;

    return 0;
}