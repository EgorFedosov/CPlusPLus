#include <iostream>
using namespace std;
int main()
{

    int size;
    cout << "Enter size arr: ";
    cin >> size;
    cout << endl
         << endl;

        int *Arr = new int[size];

    for (int i = 0; i < size; i++)
    {
        cout << "Enter " << i << ": ";
        cin >> Arr[i];
        cout << endl;
    }
    cout << endl;

    int remove;
    cout << "delete: ";
    cin >> remove;
    cout << endl;

    for (int i = 0; i < size; i++)
    {
        if (Arr[i] == remove)
        {
            for (int j = i; j < size - 1; j++)
            {
                Arr[j] = Arr[j + 1];
            }
            size--;
            i--;
        }
    }
    // cout << "Size: " << size << endl;
    for (int i = 0; i < size; i++)
    {
        cout << Arr[i] << " ";
    }

    delete[] Arr;
    return 0;
}