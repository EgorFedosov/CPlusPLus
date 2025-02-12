#include <iostream>
using namespace std;

int Bin1(int arr[], int n, int key)
{
    bool flag = false;
    int l = 0;
    int r = n - 1;
    int mid;

    while (l <= r && !flag)
    {
        mid = (l + r) / 2;

        if (arr[mid] == key)
        {
            flag = true;
            return mid + 1;
        }

        if (arr[mid] > key)
        {
            r = mid - 1;
        }
        else
        {
            l = mid + 1; // fignya
        }
    }

    return -1;
}

int Bin2Rec(int arr[], int l, int r, int key)
{
    if (l > r)
    {
        return -1;
    }

    int mid = (l + r) / 2;

    if (arr[mid] == key)
    {
        return mid + 1;
    }
    else if (arr[mid] > key)
    {
        return Bin2Rec(arr, l, mid - 1, key);
    }
    else
    {
        return Bin2Rec(arr, mid + 1, r, key);
    }
}

int main()
{
    int n;

    cout << "Введите размер массива: ";
    cin >> n;

    int arr[n];

    cout << "Введите " << n << " элементов массива (в порядке возрастания): ";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    int key;
    cout << "Введите ключ для поиска: ";
    cin >> key;

    int res1 = Bin1(arr, n, key);
    int res2rec = Bin2Rec(arr, 0, n - 1, key);

    cout << "Элемент найден по индексу" << endl;
    cout << "Рекурсивная: " << res2rec << endl;
    cout << "Обычная: " << res1;

    return 0;
}