#include <iostream>
using namespace std;

struct spis
{
    int info;
    spis *next, *prev;
} *head, *tail;

spis *Create_spis(spis *h, int in)
{
    spis *t = new spis;
    t->info = in;
    t->next = h;
    t->prev = nullptr;
    if (h != nullptr)
        h->prev = t;
    return t;
}

spis *addEnd(spis *t, int in)
{
    spis *newspis = new spis;
    newspis->info = in;
    newspis->next = nullptr;
    newspis->prev = t;
    if (t != nullptr)
        t->next = newspis;
    return newspis;
}

void View(spis *p, bool reverse = false)
{
    spis *t = p;
    if (reverse)
    {
        while (t->next != nullptr)
            t = t->next;
        while (t != nullptr)
        {
            cout << " " << t->info << endl;
            t = t->prev;
        }
    }
    else
    {
        while (t != nullptr)
        {
            cout << " " << t->info << endl;
            t = t->next;
        }
    }
}

void Del_All(spis **p)
{
    while (*p != nullptr)
    {
        spis *t = *p;
        *p = (*p)->next;
        delete t;
    }
    tail = nullptr;
}

void change(spis **p)
{

    spis *min = *p;
    spis *t = *p;

    while (t != nullptr)
    {

        if (t->info < min->info)
        {

            min = t;
        }
        t = t->next;
    }
    if (*p != min)
    {

        spis *prev = nullptr;
        t = *p;

        while (t != min)
        {
            prev = t;
            t = t->next;
        }

        if (min->next != nullptr)
        {
            prev->next = min->next;
            min->next->prev = prev;
        }

        min->next = *p;
        *p = min;
    }
}

void removed(spis **p)
{
    spis *current = *p;
    while (current != nullptr)
    {
        if (current->info % 2 != 0)
        {
            // тут мы просто связываем следующий элемент с позапрошлым
            if (current->prev != nullptr)
                current->prev->next = current->next;

            if (current->next != nullptr)
                current->next->prev = current->prev;

            // Обновляем голову
            if (current == *p)
                *p = current->next;

            // переносим указатель и удаляем элемент
            spis *t = current;
            current = current->next;
            delete t;
        }
        else
        {
            current = current->next;
        }
    }
}

int main()
{
    int i, in, n, num, num1;
    while (true)
    {
        cout << "\n\tcreate - 1\n\tadd - 2\n\tview - 3\n\tdelete spis - 4\n\tchange - 5\n\texit - 0 : ";
        cin >> num;
        switch (num)
        {
        case 1:
            if (head != nullptr)
            {
                Del_All(&head);
                cout << "memory cleared!" << endl;
            }
            cout << "kol: ";
            cin >> n;
            for (i = 0; i < n; ++i)
            {
                in = rand() % 100;
                if (i == 0)
                {
                    head = tail = Create_spis(head, in);
                }
                else
                {
                    tail = addEnd(tail, in);
                }
            }
            cout << "list created" << endl;
            break;
        case 2:
            cout << "value = ";
            cin >> in;
            cout << "head - 0, tail - 1 : ";
            cin >> num1;
            if (num1 == 0)
            {
                head = Create_spis(head, in);
                if (tail == nullptr)
                    tail = head;
            }
            else
            {
                tail = addEnd(tail, in);
                if (head == nullptr)
                    head = tail;
            }
            cout << "element added" << endl;
            break;
        case 3:
            if (!head)
            {
                cout << "list pust!" << endl;
                break;
            }
            cout << "check head - 0, check tail - 1: ";
            cin >> num1;
            if (num1 == 0)
            {
                cout << "-- Head --" << endl;
                View(head);
            }
            else
            {
                cout << "--- Tail ---" << endl;
                View(head, true);
            }
            break;
        case 4:
            Del_All(&head);
            cout << "memory cleared!" << endl;
            break;
        case 5:
            if (!head)
            {
                cout << "list pust!" << endl;
                break;
            }
            change(&head);
            cout << "done" << endl;
            break;
        case 0:
            if (head != nullptr)
                Del_All(&head);
            return 0;
        }
    }
}
