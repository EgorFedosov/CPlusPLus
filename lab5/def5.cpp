#include <iostream>
using namespace std;

int main()
{
    int n, m;
    cout << "Введите количество строк и столбцов матрицы: ";
    cin >> n >> m;

    float arr[n][m];

    cout << "Введите элементы матрицы:" << endl;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            cin >> arr[i][j];
        }
    }
    cout << endl;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            float max1 = arr[i][0], max2 = arr[j][0];
            for (int t = 1; t < m; ++t)
            {
                if (arr[i][t] > max1)
                    max1 = arr[i][t];
                if (arr[j][t] > max2)
                    max2 = arr[j][t];
            }

            if (max1 > max2)
            {
                float save[m];
                for (int t = 0; t < m; ++t)
                {
                    save[t] = arr[i][t];
                    arr[i][t] = arr[j][t];
                    arr[j][t] = save[t];
                }
            }
        }
    }

    cout << "Матрица после сортировки:" << endl;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
