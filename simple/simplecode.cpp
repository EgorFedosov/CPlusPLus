#include <iostream>
#include <cstdlib>
#include <ctime>

int main()
{
    const int SIZE = 10;
    int array[SIZE];

    // Инициализация генератора случайных чисел с использованием текущего времени
    std::srand(std::time(NULL
    ));

    // Заполнение массива случайными числами
    for (int i = 0; i < SIZE; i++)
    {
        array[i] = std::rand();
        std::cout << "array[" << i << "] = " << array[i] << std::endl;
    }

    return 0;
}
