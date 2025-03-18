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

void SwapMinToHead(spis **p)
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

void SwapMinMax(spis **p)
{
    if (!p || !(*p) || !(*p)->next)
        return; // Если пусто или 1 элемент

    spis *t = *p;
    spis *min = *p;
    spis *max = *p;

    // Поиск min и max
    while (t)
    {
        if (t->info < min->info)
            min = t;
        if (t->info > max->info)
            max = t;
        t = t->next;
    }

    if (min == max)
        return;

    spis *MinNext = min->next;
    spis *MinPrev = min->prev;
    spis *MaxNext = max->next;
    spis *MaxPrev = max->prev;

    // если min и max соседи
    if (max->next == min)
    { // max перед min
        if (MaxPrev)
            MaxPrev->next = min;
        if (MinNext)
            MinNext->prev = max;

        min->prev = MaxPrev;
        min->next = max;
        max->prev = min;
        max->next = MinNext;
    }
    else if (min->next == max)
    { // min перед max
        if (MinPrev)
            MinPrev->next = max;
        if (MaxNext)
            MaxNext->prev = min;

        max->prev = MinPrev;
        max->next = min;
        min->prev = max;
        min->next = MaxNext;
    }
    else
    { // ОБЩИЙ СЛУЧАЙ
      // связываем соседей Мин и Макса
        if (MinPrev)
            MinPrev->next = max;
        if (MinNext)
            MinNext->prev = max;
        if (MaxPrev)
            MaxPrev->next = min;
        if (MaxNext)
            MaxNext->prev = min;

        min->next = MaxNext;
        min->prev = MaxPrev;
        max->next = MinNext;
        max->prev = MinPrev;
    }

    //  если min или max были head-e

    //===========OK
    if (*p == min)
        *p = max;
    else if (*p == max)
        *p = min;
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
        cout << "\n\tcreate - 1\n\tadd - 2\n\tview - 3\n\tdelete spis - 4\n\tSwapMinToHead - 5\n\tSwapMinMax - 6 \n\texit - 0 : ";
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
            SwapMinToHead(&head);
            cout << "done" << endl;
            break;

        case 6:
        {
            if (!head)
            {
                cout << "list pust!" << endl;
                break;
            }
            SwapMinMax(&head);
            cout << "done" << endl;
            break;
        }
        case 0:
            if (head != nullptr)
                Del_All(&head);
            return 0;
        }
    }
}
