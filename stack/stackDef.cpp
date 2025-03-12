#include <iostream>
using namespace std;

struct Stack
{
    int info;
    Stack *next;
};

Stack *InStack(Stack *p, int in)
{
    Stack *t = new Stack;
    t->info = in;
    t->next = p;
    return t;
}

void View(Stack *p)
{
    Stack *t = p;
    while (t != nullptr)
    {
        cout << " " << t->info << endl;
        t = t->next;
    }
}

void Del_All(Stack **p)
{
    while (*p != nullptr)
    {
        Stack *t = *p;
        *p = (*p)->next;
        delete t;
    }
}

void TransferToMax(Stack **p)
{
    if (*p == nullptr)
    {
        cout << "Stack pust!" << endl;
        return;
    }

    int max = (*p)->info;
    Stack *t = *p;

    while (t != nullptr)
    {
        if (t->info > max)
        {
            max = t->info;
        }
        t = t->next;
    }

    Stack *newStack = nullptr;

    t = *p;
    int value;
    while (t != nullptr)
    {
        value = t->info;
        newStack = InStack(newStack, value);
        if (value == max)
            break;
        t = t->next;
    }

    // разворот стека
    Stack *reversedStack = nullptr;
    while (newStack != nullptr)
    {
        value = newStack->info;
        reversedStack = InStack(reversedStack, value);
        newStack = newStack->next;
    }

    Del_All(p);
    *p = reversedStack;
}

int main()
{
    int i, in, n, kod;
    Stack *stackTop = nullptr;
    while (true)
    {
        cout << "\n\tCreate - 1.\n\tAdd - 2.\n\tView - 3.\n\tDel - 4.\n\tTransferToMax - 5.\n\tEXIT - 0. : ";
        cin >> kod;
        switch (kod)
        {
        case 1:
        {
            if (stackTop != nullptr)
            {
                Del_All(&stackTop);
                cout << "Memory cleared!" << endl;
            }
            cout << "Input number of elements: ";
            cin >> n;
            for (i = 1; i <= n; i++)
            {
                in = rand() % 20;
                stackTop = InStack(stackTop, in);
            }
            cout << "Created " << n << " elements." << endl;
            break;
        }
        case 2:
        {
            cout << "Input number of elements to add: ";
            cin >> n;
            for (i = 1; i <= n; i++)
            {
                in = rand() % 20;
                stackTop = InStack(stackTop, in);
            }
            cout << "Added " << n << " elements." << endl;
            break;
        }
        case 3:
        {
            if (!stackTop)
            {
                cout << "Stack is empty!" << endl;
                break;
            }
            cout << "--- Stack ---" << endl;
            View(stackTop);
            break;
        }
        case 4:
        {
            Del_All(&stackTop);
            cout << "Memory freed!" << endl;
            break;
        }
        case 5:
        {
            if (!stackTop)
            {
                cout << "Stack is empty!" << endl;
                break;
            }
            TransferToMax(&stackTop);
            cout << "Elements up to new stack." << endl;
            break;
        }
        case 0:
        {
            if (stackTop != nullptr)
                Del_All(&stackTop);
            return 0;
        }
        }
    }
}
