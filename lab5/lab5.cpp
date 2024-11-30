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
            if ((i <= j && i + j < n) || (i >= j && i + j >= n) || (i + j == n - 1))
            {
                if (arr[i][j] > max)
                    max = arr[i][j];
                if (arr[i][j] < min)
                    min = arr[i][j];
            }
        }
    }

    cout << "Максимум: " << max << ", Минимум: " << min << endl;

    for (int i = 0; i < n; ++i)
    {
        delete[] arr[i];
    }
    delete[] arr;

    return 0;
}
