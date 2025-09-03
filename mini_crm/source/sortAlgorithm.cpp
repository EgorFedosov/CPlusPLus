#include "sortAlgorithm.h"
#include "charUtils.h"

void sortQuickProduct(Client arr[], int left, int right)
{
    if (left >= right)
        return;
    int i = left, j = right;
    Client pivot = arr[left + (right - left) / 2];

    while (i <= j)
    {
        while (my_strcmp(arr[i].product, pivot.product) < 0)
            i++;
        while (my_strcmp(arr[j].product, pivot.product) > 0)
            j--;
        if (i <= j)
        {
            my_swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    sortQuickProduct(arr, left, j);
    sortQuickProduct(arr, i, right);
}

int compareDates(Client a, Client b)
{
    if (a.year != b.year)
        return a.year - b.year;
    if (a.month != b.month)
        return a.month - b.month;
    return a.day - b.day;
}
void sortSelection(Client arr[], int size)
{
    for (int i = 0; i < size - 1; ++i)
    {
        int minDateIndex = i;
        for (int j = i + 1; j < size; ++j)
        {
            if (compareDates(arr[j], arr[minDateIndex]) < 0)
            {
                minDateIndex = j;
            }
        }
        if (minDateIndex != i)
        {
            my_swap(arr[i], arr[minDateIndex]);
        }
    }
}

void sortInsertion(Client arr[], int size)
{
    for (int i = 1; i < size; ++i)
    {
        Client key = arr[i];
        int j = i - 1;
        while (j >= 0 && my_strcmp(arr[j].name, key.name) > 0)
        {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

template <typename T>
void my_swap(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}
