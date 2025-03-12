//v15
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;
struct Student
{
    string surname = "";
    int group = 0;
    int math = 0;
    int physics = 0;
    int informatics = 0;
    double average = 0;
};

void bubbleSortBySurname(vector<Student> &students)
{
    int n = students.size();
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (students[j].surname > students[j + 1].surname)
            {
                swap(students[j], students[j + 1]);

            }
        }
    }
}

int main()
{
    setlocale(LC_ALL, "ru");
    int n;

    vector<Student> students;

    cout << "Выберите действие:" << endl
         << "1 - Создание" << endl
         << "2 - Просмотр" << endl
         << "3 - Добавление" << endl
         << "4 - Решение индивидуального задания" << endl
         << "5 - Редактирование" << endl
         << "6 - Сортировка" << endl
         << "7 - Удаление" << endl
         << "8 - Выход" << endl;
    cin >> n;

    while (n != 8)
    {
        switch (n)
        {

        case 1:
        {
            // Создание
            ofstream file("file.txt", ios_base::out);
            if (file.is_open())
            {
                file.close();
            }
            break;
        }

        case 2:
        {
            // Просмотр
            ifstream file("file.txt");
            if (!file)
            {
                cerr << "Ошибка открытия файла!" << endl;
                return 1;
            }
            string line;
            while (getline(file, line))
            {
                cout << line << endl;
            }
            cout << endl;
            file.close();
            break;
        }

        case 3:
        {
            // Добавление
            ofstream file("file.txt", ios::app);
            if (!file)
            {
                cerr << "Ошибка открытия файла!" << endl;
                return 1;
            }
            Student data;
            cout << "Введите фамилию студента: ";
            cin >> data.surname;
            file << "Фамилия: " << data.surname << endl;

            cout << "Введите номер группы: ";
            cin >> data.group;
            file << "Группа: " << data.group << endl;

            cout << "Введите оценку за семестр по математике: ";
            cin >> data.math;
            file << "Математика: " << data.math;

            cout << "Введите оценку за семестр по физике: ";
            cin >> data.physics;
            file << "\nФизика: " << data.physics;

            cout << "Введите оценку за семестр по информатике: ";
            cin >> data.informatics;
            file << "\nИнформатика: " << data.informatics;

            data.average = (data.math + data.physics + data.informatics) / 3.0;
            file << "\nСредний балл: " << data.average << "\n\n";

            students.push_back(data);
            file.close();
            break;
        }

        case 4:
        {
            // Индивидуальное задание
            cout << "Введите искомую группу: ";
            int find_group;
            cin >> find_group;
            cout << "Введите средний балл: ";
            float find_average;
            cin >> find_average;

            for (const auto &student : students)
            {
                if (student.group == find_group && student.average > find_average)
                {
                    cout << "Фамилия: " << student.surname << "\n";
                    cout << "Группа: " << student.group << "\n";
                    cout << "Оценка по математике: " << student.math << "\n";
                    cout << "Оценка по физике: " << student.physics << "\n";
                    cout << "Оценка по информатике: " << student.informatics << "\n";
                    cout << "Средний балл: " << student.average << "\n"
                         << endl;
                }
            }
            break;
        }

        case 5:
        {
            // Редактирование
            cout << "Введите номер студента в списке, которого хотите отредактировать: ";
            int redact;
            cin >> redact;

            if (redact > 0 && redact <= students.size())
            {
                Student &student = students[redact - 1]; // Получаем ссылку на студента

                cout << "Введите новую фамилию студента (текущая: " << student.surname << "): ";
                cin >> student.surname;

                cout << "Введите новый номер группы (текущий: " << student.group << "): ";
                cin >> student.group;

                cout << "Введите новую оценку за семестр по математике (текущая: " << student.math << "): ";
                cin >> student.math;

                cout << "Введите новую оценку за семестр по физике (текущая: " << student.physics << "): ";
                cin >> student.physics;

                cout << "Введите новую оценку за семестр по информатике (текущая: " << student.informatics << "): ";
                cin >> student.informatics;

                student.average = (student.math + student.physics + student.informatics) / 3.0;

                // Перезаписываем файл с обновленными данными
                ofstream file("file.txt", ios::out);
                if (!file)
                {
                    cerr << "Ошибка открытия файла!" << endl;
                    return 1;
                }

                for (const auto &student : students)
                {
                    file << "Фамилия: " << student.surname << "\n"
                         << "Группа: " << student.group << "\n"
                         << "Оценка по математике: " << student.math << "\n"
                         << "Оценка по физике: " << student.physics << "\n"
                         << "Оценка по информатике: " << student.informatics << "\n"
                         << "Средний балл: " << student.average << "\n"
                         << endl;
                }
                file.close();
            }
            else
            {
                cout << "Неверный номер студента." << endl;
            }
            break;
        }

        case 6:
        {

            cout << "Выберите способ сортировки: \n 1 - по фамилиям\n 2 - по среднему баллу\n 3 - по оценкам по математике\n 4 - по оценкам по физике\n 5 - по оценкам по информатике";

            cout << endl;
            int a;
            cin >> a;
            switch (a)
            {
            case 1:
            {
                // Сортировка по фамилиям
                bubbleSortBySurname(students);
                break;
            }
            case 2:
            {
                int n = students.size();
                for (int i = 0; i < n - 1; i++)
                {
                    for (int j = 0; j < n - 1 - i; j++)
                    {
                        if (students[j].average < students[j + 1].average)
                        {
                            swap(students[j], students[j + 1]);
                        }
                    }
                }
                break;
            }
            case 3:
            {
                int n = students.size();
                for (int i = 0; i < n - 1; i++)
                {
                    for (int j = 0; j < n - 1 - i; j++)
                    {
                        if (students[j].math < students[j + 1].math)
                        {
                            swap(students[j], students[j + 1]);
                        }
                    }
                }
                break;
            }
            case 4:
            {
                int n = students.size();
                for (int i = 0; i < n - 1; i++)
                {
                    for (int j = 0; j < n - 1 - i; j++)
                    {
                        if (students[j].physics < students[j + 1].physics)
                        {
                            swap(students[j], students[j + 1]);
                        }
                    }
                }
                break;
            }
            case 5:
            {
                int n = students.size();
                for (int i = 0; i < n - 1; i++)
                {
                    for (int j = 0; j < n - 1 - i; j++)
                    {
                        if (students[j].informatics < students[j + 1].informatics)
                        {
                            swap(students[j], students[j + 1]);
                        }
                    }
                }
                break;
            }
            default:
            {
                cout << "Неверный выбор.";
                break;
            }
            }

            // Перезаписываем файл с обновленными данными
            ofstream file("file.txt", ios::out);
            if (!file)
            {
                cerr << "Ошибка открытия файла!" << endl;
                return 1;
            }

            for (const auto &student : students)
            {
                file << "Фамилия: " << student.surname << "\n"
                     << "Группа: " << student.group << "\n"
                     << "Оценка по математике: " << student.math << "\n"
                     << "Оценка по физике: " << student.physics << "\n"
                     << "Оценка по информатике: " << student.informatics << "\n"
                     << "Средний балл: " << student.average << "\n"
                     << endl;
            }
            file.close();
            break;
        }

        case 7:
        {
            // Удаление
            cout << "Введите номер студента в списке, которого хотите удалить: ";
            int del;
            cin >> del;

            if (del > 0 && del <= students.size())
            {
                students.erase(students.begin() + (del - 1));
            }
            else
            {
                cout << "Неверный номер студента." << endl;
            }

            // Перезаписываем файл после удаления
            ofstream file("file.txt", ios::out);
            if (!file)
            {
                cerr << "Ошибка открытия файла!" << endl;
                return 1;
            }

            for (const auto &student : students)
            {
                file << "Фамилия: " << student.surname << "\n"
                     << "Группа: " << student.group << "\n"
                     << "Оценка по математике: " << student.math << "\n"
                     << "Оценка по физике: " << student.physics << "\n"
                     << "Оценка по информатике: " << student.informatics << "\n"
                     << "Средний балл: " << student.average << "\n"
                     << endl;
            }
            file.close();
            break;
        }

        default:
        {
            cout << "Неверный выбор. Попробуйте снова." << endl;
            break;
        }
        }

        cout << "Выберите действие:" << endl
             << "1 - Создание" << endl
             << "2 - Просмотр" << endl
             << "3 - Добавление" << endl
             << "4 - Решение индивидуального задания" << endl
             << "5 - Редактирование" << endl
             << "6 - Сортировка" << endl
             << "7 - Удаление" << endl
             << "8 - Выход" << endl;
        cin >> n;
    }

    return 0;
}