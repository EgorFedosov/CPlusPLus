#include <iostream>
using namespace std;
int main()
{
    int size;
    cout << "Enter size: ";
    cin >> size;
    cout << endl;
    int Arr[size];

    for (int i = 0; i < size; i++)
    {
        cout << "Enter(!=0)" << i << ": ";
        cin >> Arr[i];
        cout << endl;
    }

    int k = 0; // количество нечетных и отрицательных
    for (int i = 0; i < size; i++)
    {
        if (Arr[i] % 2 != 0)
        {
            k++;
        }
    }
    int newsize = k; // количество нечетных и отрицательных
    int *newArr = new int[newsize];

    int j = 0;
    for (int i = 0; i < size; i++)
    {
        if (Arr[i] % 2 != 0)
        {
            newArr[j] = Arr[i]; // добавляем нечет в новый массив
            j++;
        }
    }

    for (int i = 0; i < newsize; i++)
    {
        cout << newArr[i] << " ";
    }
    cout << endl;
    // нужна затирка в некст

    int save = 0;
    for (int i = 0; i < newsize; i++)
    {

        if (newArr[i] < 0)
        {
            newArr[i] = save; // перед отрицательными 10
            newArr[i] = 10;
            newArr[i + 1] = save;
        }
    }

    cout << endl;
    cout << endl;

    for (int i = 0; i < newsize; i++)
    {
        cout << newArr[i] << " ";
    }
    delete[] newArr;

    return 0;
}