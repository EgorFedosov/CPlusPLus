#include <iostream>
using namespace std;

int main()
{
    int n;
    cout << "Введите размер квадратной матрицы: ";
    cin >> n;

    int **arr = new int *[n];
    for (int i = 0; i < n; ++i)
    {
        arr[i] = new int[n];
    }

    cout << "Введите элементы матрицы:" << endl;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> arr[i][j];
        }
    }

    cout << "Введенная матрица:" << endl;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

    int max = arr[0][0], min = arr[0][0];

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if ((i <= j && i + j < n) || (i >= j && i + j >= n)) // нижний + верхний треугольник
            {
                if (arr[i][j] > max)
                    max = arr[i][j];
                if (arr[i][j] < min)
                    min = arr[i][j];
            }
        }
    }
    // ubrat mojno
    if (n % 2 == 1) // если нечет
    {
        int center = arr[n / 2][n / 2];
        if (center > max)
            max = center;
        if (center < min)
            min = center;
    }

    cout << "Максимум: " << max << ", Минимум: " << min << endl;

    for (int i = 0; i < n; ++i)
    {
        delete[] arr[i];
    }
    delete[] arr;

    return 0;
}
