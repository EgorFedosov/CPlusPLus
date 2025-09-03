#include <iostream>
#include <vector>
#include <utility>

using namespace std;
bool qwerty(vector<pair<int, int>> vec, int x, int y)
{
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i].first == x && vec[i].second == y)
        {
            return true;
        }
    }
    return false;
}

int main()
{
    setlocale(LC_ALL, "RU");
    vector<pair<int, int>> set1;
    vector<pair<int, int>> set2;
    vector<pair<int, int>> set3;
    int n, choose, q = 0;
    cout << "Выберите способ заполнения множеств(графиков): " << endl
         << "1 - самостоятельно" << endl
         << "2 - высказыванием" << endl;
    cin >> choose;
    switch (choose)
    {
    case 1:
    {

        cout << "Универсум : {1, 2, 3, ... 100}" << endl;
        cout << "Выберите операцию: " << endl
             << "1 - инверсия" << endl
             << "2 - композиция" << endl
             << "3 - декартово произведение" << endl
             << "4 - проекцию" << endl;

        cin >> choose;

        switch (choose)
        {
        // инверсия
        case 1:
        {
            cout << "Введите количество кортежей в множестве: ";
            cin >> n;
            for (int i = 0; i < n; i++)
            {
                int a, b;
                cout << "Введите первый элемент" << " " << i + 1 << "-ого" << " кортежа: ";
                cin >> a;
                if (a < 0 or a > 100)
                {
                    cout << "Выходит за универсум, попробуйте снова: " << endl;
                    i--;
                    continue;
                }
                cout << "Введите второй элемент" << " " << i + 1 << "-ого" << " кортежа: ";
                cin >> b;
                if (b < 0 or b > 100)
                {
                    cout << "Выходит за универсум, попробуйте снова: " << endl;
                    i--;
                    continue;
                }
                if (qwerty(set1, a, b))
                {
                    cout << "Уже существует такая пара, попробуйте снова: " << endl;
                    i--;
                    continue;
                }
                set1.push_back(make_pair(a, b));
            }

            cout << "Инверсия графика: " << endl;

            for (auto &p : set1)
            {
                swap(p.first, p.second);
            }

            for (auto &p : set1)
            {
                cout << "<" << p.first << ", " << p.second << ">" << endl;
            }
            break;
        }
        // композиция
        case 2:
        {
            cout << "Введите количество кортежей в 1 множестве: ";
            cin >> n;
            for (int i = 0; i < n; i++)
            {
                int a, b;
                cout << "Введите первый элемент" << " " << i + 1 << "-ого" << " кортежа: ";
                cin >> a;
                if (a < 0 or a > 100)
                {
                    cout << "Выходит за универсум, попробуйте снова: " << endl;
                    i--;
                    continue;
                }
                cout << "Введите второй элемент" << " " << i + 1 << "-ого" << " кортежа: ";
                cin >> b;
                if (b < 0 or b > 100)
                {
                    cout << "Выходит за универсум, попробуйте снова: " << endl;
                    i--;
                    continue;
                } // проверка на уникальность
                if (!qwerty(set1, a, b))
                {
                    set1.push_back(make_pair(a, b));
                }
                else
                {
                    cout << "Уже существует такой кортеж, попробуйте снова: " << endl;
                    i--;
                    continue;
                }
            }

            cout << "Введите количество кортежей во 2 множестве: ";
            cin >> n;
            for (int i = 0; i < n; i++)
            {
                int a, b;
                cout << "Введите первый элемент" << " " << i + 1 << "-ого" << " кортежа: ";
                cin >> a;
                if (a < 0 or a > 100)
                {
                    cout << "Выходит за универсум, попробуйте снова: " << endl;
                    i--;
                    continue;
                }
                cout << "Введите второй элемент" << " " << i + 1 << "-ого" << " кортежа: ";
                cin >> b;
                if (b < 0 or b > 100)
                {
                    cout << "Выходит за универсум, попробуйте снова: " << endl;
                    i--;
                    continue;
                }
                // проверка на уникальность
                if (!qwerty(set2, a, b))
                {
                    set2.push_back(make_pair(a, b));
                }
                else
                {
                    cout << "Уже существует такой кортеж, попробуйте снова: " << endl;
                    i--;
                    continue;
                }
            }

            for (auto &p : set1)
            {
                for (auto &k : set2)
                {
                    if (p.second == k.first)
                    {
                        set3.push_back(make_pair(p.first, k.second));
                    }
                }
            }

            cout << "Композиция 2 графиков: " << endl;
            for (auto &p : set3)
            {
                cout << "<" << p.first << ", " << p.second << ">" << endl;
            }

            break;
        }
        // декартово произведение
        case 3:
        {
            int n1, n2;

            cout << "Введите количество элементов 1 множества: " << endl;
            cin >> n1;
            cout << "Введите количество элементов 2 множества: " << endl;
            cin >> n2;

            int *a = new int[n1];
            int *b = new int[n2];
            vector<pair<int, int>> set4;

            cout << "Введите элементы 1 множества: ";
            for (int i = 0; i < n1; i++)
            {
                cin >> a[i];
            }

            cout << "Введите элементы 2 множества: ";
            for (int i = 0; i < n2; i++)
            {
                cin >> b[i];
            }

            cout << "Декартово произведение: " << endl;
            for (int i = 0; i < n1; i++)
            {
                for (int j = 0; j < n2; j++)
                {
                    set4.push_back(make_pair(a[i], b[j]));
                }
            }
            for (auto &p : set4)
            {
                cout << "<" << p.first << ", " << p.second << ">" << endl;
            }
            break;
        }
        // проекция
        case 4:
        {
            cout << "Введите количество кортежей в множестве: ";
            cin >> n;
            for (int i = 0; i < n; i++)
            {
                int a, b;
                cout << "Введите первый элемент" << " " << i + 1 << "-ого" << " кортежа: ";
                cin >> a;
                if (a < 0 or a > 100)
                {
                    cout << "Выходит за универсум, попробуйте снова: " << endl;
                    i--;
                    continue;
                }
                cout << "Введите второй элемент" << " " << i + 1 << "-ого" << " кортежа: ";
                cin >> b;
                if (b < 0 or b > 100)
                {
                    cout << "Выходит за универсум, попробуйте снова: " << endl;
                    i--;
                    continue;
                }
                // проверка на уникальность
                if (!qwerty(set1, a, b))
                {
                    set1.push_back(make_pair(a, b));
                }
                else
                {
                    cout << "Уже существует такой кортеж, попробуйте снова: " << endl;
                    i--;
                    continue;
                }
            }
            cout << "Выберите проекцию на ось: " << endl
                 << "1 - проекция на ось Ох" << endl
                 << "2 - проекция на ось Оу" << endl;
            cin >> choose;
            switch (choose)
            {
            case 1:
            {
                cout << "Проекция на ось Ох: " << endl;
                for (auto &p : set1)
                {
                    cout << p.first << " ";
                }
                break;
            }
            case 2:
            {
                cout << "Проекция на ось Оy: " << endl;
                for (auto &p : set1)
                {
                    cout << p.second << " ";
                }
                break;
            }
            }
            break;
        }
        }
        break;
    }
    case 2:
    {
        cout << "Выберите высказывание: " << endl
             << "1 - квадрат натуральных чисел" << endl
             << "2 - четными числами" << endl
             << "3 - нечетными числами" << endl;

        cin >> q;

        cout << "Выберите операцию: " << endl
             << "1 - инверсия" << endl
             << "2 - композиция" << endl
             << "3 - декартово произведение" << endl
             << "4 - проекцию" << endl;

        cin >> choose;
        switch (choose)
        {
            // инверсия
        case 1:
        {
            cout << "Введите количество кортежей в множестве: ";
            cin >> n;
            // высказывания
            if (q == 1)
            {
                for (int i = 0; i < n; i++)
                {
                    int a, b;
                    a = (i + 1) * (i + 1);
                    b = (i + 2) * (i + 2);
                    if (a > 100 or b > 100)
                    {
                        cout << "Выходит за универсум" << endl;
                        break;
                    }
                    set1.push_back(make_pair(a, b));
                }
            }
            else if (q == 2)
            {
                for (int i = 0; i < n * 2; i += 2)
                {
                    int a, b;
                    a = i + 2;
                    b = i + 4;
                    if (a > 100 or b > 100)
                    {
                        cout << "Выходит за универсум" << endl;
                        break;
                    }
                    set1.push_back(make_pair(a, b));
                }
            }
            else if (q == 3)
            {
                for (int i = -1; i < n * 2 - 1; i += 2)
                {
                    int a, b;
                    a = i + 2;
                    b = i + 4;
                    if (a > 100 or b > 100)
                    {
                        cout << "Выходит за универсум" << endl;
                        break;
                    }
                    set1.push_back(make_pair(a, b));
                }
            }

            cout << "Инверсия графика: " << endl;

            for (auto &p : set1)
            {
                swap(p.first, p.second);
            }

            for (auto &p : set1)
            {
                cout << "<" << p.first << ", " << p.second << ">" << endl;
            }
            break;
        }
            // композиция
        case 2:
        {
            // высказывания
            cout << "Введите количество кортежей 1 множества: " << endl;
            cin >> n;
            if (q == 1)
            {

                for (int i = 0; i < n; i++)
                {
                    int a, b;
                    a = (i + 1) * (i + 1);
                    b = (i + 2) * (i + 2);
                    if (a > 100 or b > 100)
                    {
                        cout << "Выходит за универсум" << endl;
                        break;
                    }
                    set1.push_back(make_pair(a, b));
                }
            }
            else if (q == 2)
            {
                for (int i = 0; i < n * 2; i += 2)
                {
                    int a, b;
                    a = i + 2;
                    b = i + 4;
                    if (a > 100 or b > 100)
                    {
                        cout << "Выходит за универсум" << endl;
                        break;
                    }
                    set1.push_back(make_pair(a, b));
                }
            }
            else if (q == 3)
            {
                for (int i = -1; i < n * 2 - 1; i += 2)
                {
                    int a, b;
                    a = i + 2;
                    b = i + 4;
                    if (a > 100 or b > 100)
                    {
                        cout << "Выходит за универсум" << endl;
                        break;
                    }
                    set1.push_back(make_pair(a, b));
                }
            }
            cout << "1 график:" << endl;
            for (auto &p : set1)
            {
                cout << "<" << p.first << ", " << p.second << ">" << " ";
            }
            cout << endl;
            for (auto &p : set3)
            {
                cout << "<" << p.first << ", " << p.second << ">" << endl;
            }
            break;
        }
            // проекция
        case 4:
        {
            // высказывания
            if (q == 1)
            {
                for (int i = 0; i < n; i++)
                {
                    int a, b;
                    a = (i + 1) * (i + 1);
                    b = (i + 2) * (i + 2);
                    if (a > 100 or b > 100)
                    {
                        cout << "Выходит за универсум" << endl;
                        break;
                    }
                    set1.push_back(make_pair(a, b));
                }
            }
            else if (q == 2)
            {
                for (int i = 0; i < n * 2; i += 2)
                {
                    int a, b;
                    a = i + 2;
                    b = i + 4;
                    if (a > 100 or b > 100)
                    {
                        cout << "Выходит за универсум" << endl;
                        break;
                    }
                    set1.push_back(make_pair(a, b));
                }
            }
            else if (q == 3)
            {
                for (int i = -1; i < n * 2 - 1; i += 2)
                {
                    int a, b;
                    a = i + 2;
                    b = i + 4;
                    if (a > 100 or b > 100)
                    {
                        cout << "Выходит за универсум" << endl;
                        break;
                    }
                    set1.push_back(make_pair(a, b));
                }
            }

            cout << "Выберите проекцию на ось: " << endl
                 << "1 - проекция на ось Ох" << endl
                 << "2 - проекция на ось Оу" << endl;
            cin >> choose;
            switch (choose)
            {
            case 1:
            {
                cout << "Проекция на ось Ох: " << endl;
                for (auto &p : set1)
                {
                    cout << p.first << " ";
                }
                break;
            }
            case 2:
            {
                cout << "Проекция на ось Оy: " << endl;
                for (auto &p : set1)
                {
                    cout << p.second << " ";
                }
                break;
            }
            }
            break;
        }
        }
        break;
    }
    }
    return 0;
}