#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

int main()
{
    int n1;
    vector<pair<int, int>> graph1;

    cout << "Введите количество пар в первом графике: ";
    cin >> n1;
    cout << "Введите пары для первого графика (два числа через пробел):" << endl;
    for (int i = 0; i < n1; ++i)
    {
        int u, v;
        cin >> u >> v;
        pair<int, int> p = {u, v};

        bool isUnique = true;
        for (int j = 0; j < graph1.size(); ++j)
        {
            if (graph1[j] == p) // Проверка на уникальность
            {
                isUnique = false;
                break;
            }
        }

        if (isUnique)
        {
            graph1.push_back(p);
        }
        else
        {
            cout << "Пара <" << u << ", " << v << "> уже существует. Введите другую пару.\n";
            --i;
        }
    }

    int n2;
    vector<pair<int, int>> graph2;

    cout << "Введите количество пар во втором графике: ";
    cin >> n2;
    cout << "Введите пары для второго графика (два числа через пробел):" << endl;
    for (int i = 0; i < n2; ++i)
    {
        int u, v;
        cin >> u >> v;
        pair<int, int> p = {u, v};

        bool isUnique = true;
        for (int j = 0; j < graph2.size(); ++j)
        {
            if (graph2[j] == p) // Проверка на уникальность
            {
                isUnique = false;
                break;
            }
        }

        if (isUnique)
        {
            graph2.push_back(p);
        }
        else
        {
            cout << "Пара <" << u << ", " << v << "> уже существует. Введите другую пару.\n";
            --i;
        }
    }
    cout << endl;

    cout << "Первый график: ";
    for (size_t i = 0; i < graph1.size(); ++i) // size_t лучше чем инт так как тут нету отрицательных значений
    {
        cout << "<" << graph1[i].first << ", " << graph1[i].second << ">  ";
    }
    cout << endl;

    cout << "Второй график: ";
    for (size_t i = 0; i < graph2.size(); ++i)
    {
        cout << "<" << graph2[i].first << ", " << graph2[i].second << ">  ";
    }
    cout << endl;

    // Векторы для инверсий
    vector<pair<int, int>> invertedGraph1, invertedGraph2;

    for (size_t i = 0; i < graph1.size(); ++i)
    {
        invertedGraph1.push_back({graph1[i].second, graph1[i].first});
    }

    for (size_t i = 0; i < graph2.size(); ++i)
    {
        invertedGraph2.push_back({graph2[i].second, graph2[i].first});
    }

    cout << endl;
    cout << "Инверсия первого графика: ";
    for (size_t i = 0; i < invertedGraph1.size(); ++i)
    {
        cout << "<" << invertedGraph1[i].first << ", " << invertedGraph1[i].second << ">  ";
    }
    cout << endl;

    cout << "Инверсия второго графика: ";
    for (size_t i = 0; i < invertedGraph2.size(); ++i)
    {
        cout << "<" << invertedGraph2[i].first << ", " << invertedGraph2[i].second << ">  ";
    }
    cout << endl;

    // Вектор для композиции графиков
    vector<pair<int, int>> composition;

    for (size_t i = 0; i < graph1.size(); ++i)
    {
        for (size_t j = 0; j < graph2.size(); ++j)
        {
            if (graph1[i].second == graph2[j].first)
            {
                composition.push_back({graph1[i].first, graph2[j].second});
            }
        }
    }

    cout << "Композиция графиков: ";
    for (size_t i = 0; i < composition.size(); ++i)
    {
        cout << "<" << composition[i].first << ", " << composition[i].second << ">  ";
    }
    cout << endl;

    vector<int> projectionX1, projectionX2;

    // Проекция на ось X для первого графика
    for (size_t i = 0; i < graph1.size(); i++)
    {
        int x = graph1[i].first;
        bool exists = false;

        // Проверка, если такой x уже есть в projectionX1
        for (int px : projectionX1)
        {
            if (px == x)
            {
                exists = true;
                break;
            }
        }

        if (!exists)
        {
            projectionX1.push_back(x);
        }
    }

    // Проекция на ось X для второго графика
    for (size_t i = 0; i < graph2.size(); i++)
    {
        int x = graph2[i].first;
        bool exists = false;

        // Проверка, если такой x уже есть в projectionX2
        for (int px : projectionX2)
        {
            if (px == x)
            {
                exists = true;
                break;
            }
        }

        if (!exists)
        {
            projectionX2.push_back(x);
        }
    }

    vector<int> projectionY1, projectionY2;

    // Проекция на ось Y для первого графика
    for (size_t i = 0; i < graph1.size(); i++)
    {
        int y = graph1[i].second;
        bool exists = false;

        // Проверка, если такой y уже есть в projectionY1
        for (int py : projectionY1)
        {
            if (py == y)
            {
                exists = true;
                break;
            }
        }

        if (!exists)
        {
            projectionY1.push_back(y);
        }
    }

    // Проекция на ось Y для второго графика
    for (size_t i = 0; i < graph2.size(); i++)
    {
        int y = graph2[i].second;
        bool exists = false;

        // Проверка, если такой y уже есть в projectionY2
        for (int py : projectionY2)
        {
            if (py == y)
            {
                exists = true;
                break;
            }
        }

        if (!exists)
        {
            projectionY2.push_back(y);
        }
    }

    cout << "Проекция первого графика на ось X: ";
    for (int x : projectionX1)
    {
        cout << x << " ";
    }
    cout << endl;

    cout << "Проекция первого графика на ось Y: ";
    for (int y : projectionY1)
    {
        cout << y << " ";
    }
    cout << endl;

    cout << "Проекция второго графика на ось X: ";
    for (int x : projectionX2)
    {
        cout << x << " ";
    }
    cout << endl;

    cout << "Проекция второго графика на ось Y: ";
    for (int y : projectionY2)
    {
        cout << y << " ";
    }
    cout << endl
         << endl;

    // декартово произведение

    vector<int> set1;
    int choice1;
    cout << "Как вы хотите заполнить первое множество?\n";
    cout << "1 - Вручную\n2 - Квадратами натуральных чисел в диапазоне [A, B]\n";
    cin >> choice1;

    if (choice1 == 1)
    {
        // Заполнение вручную
        int n1;
        cout << "Введите количество элементов первого множества: ";
        cin >> n1;
        cout << "Введите элементы первого множества:\n";
        for (int i = 0; i < n1; ++i)
        {
            int value;
            cin >> value;
            set1.push_back(value);
        }
    }
    else if (choice1 == 2)
    {
        // Заполнение квадратами натуральных чисел
        int a, b;
        cout << "Введите диапазон [A, B] для квадратов натуральных чисел:\n";
        cin >> a >> b;
        for (int i = 1; i * i <= b; ++i)
        {
            int square = i * i;
            if (square >= a)
            {
                set1.push_back(square);
            }
        }
    }
    else
    {
        cout << "Неверный выбор. Завершение программы.\n";
        return 1;
    }

    // Второе множество
    vector<int> set2;
    int choice2;
    cout << "Как вы хотите заполнить второе множество?\n";
    cout << "1 - Вручную\n2 - Квадратами натуральных чисел в диапазоне [A, B]\n";
    cin >> choice2;

    if (choice2 == 1)
    {
        // Заполнение вручную
        int n2;
        cout << "Введите количество элементов второго множества: ";
        cin >> n2;
        cout << "Введите элементы второго множества:\n";
        for (int i = 0; i < n2; ++i)
        {
            int value;
            cin >> value;
            set2.push_back(value);
        }
    }
    else if (choice2 == 2)
    {
        // Заполнение квадратами натуральных чисел
        int a, b;
        cout << "Введите диапазон [A, B] для квадратов натуральных чисел:\n";
        cin >> a >> b;
        for (int i = 1; i * i <= b; ++i)
        {
            int square = i * i;
            if (square >= a)
            {
                set2.push_back(square);
            }
        }
    }
    else
    {
        cout << "Неверный выбор. Завершение программы.\n";
        return 1;
    }

    cout << "Первое множество: ";
    for (int i = 0; i < set1.size(); ++i)
    {
        cout << set1[i] << " ";
    }
    cout << endl;

    cout << "Второе множество: ";
    for (int i = 0; i < set2.size(); ++i)
    {
        cout << set2[i] << " ";
    }
    cout << endl;

    // Вычисление декартова произведения
    cout << "Декартово произведение:\n";
    for (int i = 0; i < set1.size(); ++i)
    {
        for (int j = 0; j < set2.size(); ++j)
        {
            cout << "(" << set1[i] << ", " << set2[j] << ") ";
        }
    }
    cout << endl;
    return 0;
}