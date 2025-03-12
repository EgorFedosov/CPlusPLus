#include <iostream>
using namespace std;

double recurs(int n, int k)
{
    if (k == 0 || k == n)
        return 1;
    return recurs(n - 1, k - 1) + recurs(n - 1, k);
}

double neRec(int n, int k)
{
    double result = 1;
    for (int i = 0; i < k; i++)
    {
        result *= (n - i);
        result /= (i + 1);
    }
    return result;
}

int main()
{
    int n, k;
    do
    {
        cout << "Enter n and k: ";
        cin >> n >> k;
    } while (k < 0 || k > n);

    cout << "Result: " << recurs(n, k) << endl;
    cout << "results: " << neRec(n, k);
    return 0;
}