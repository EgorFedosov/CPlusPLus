#include <iostream>
using namespace std;

int main()
{
    int size;
    cout << "Enter size: ";
    cin >> size;

    int *Arr = new int[size];
    for (int i = 0; i < size; i++)
    {
        cout << "Enter element " << i + 1 << ": ";
        cin >> Arr[i];
    }

    int MaxNewSize = size * 2;
    int *NewArr = new int[MaxNewSize];

    int NewSize;
    for (int i = 0; i < size; i++)
    {
        if (Arr[i] % 2 != 0){
            NewSize++;
            if(Arr[i] % 2 !=0 && Arr[i]<0){
                NewSize++;
            }
        }
    }

    for (int i = 0; i < size; i++){
        if (Arr[i] % 2 = 0){
            Arr[i] = NewArr[i];
        }
    }

        cout << "New array: ";
    for (int i = 0; i < NewSize; i++)
    {
        cout << NewArr[i] << " ";
    }
    cout << endl;

    delete[] Arr;
    delete[] NewArr;

    return 0;
}
