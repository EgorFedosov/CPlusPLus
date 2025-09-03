#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

const short maxSize = 256;

struct Stack
{
    char info;
    Stack *next;
};

Stack *InStack(Stack *p, char in)
{
    Stack *t = new Stack;
    t->info = in;
    t->next = p;
    return t;
}

Stack *OutStack(Stack *p, char &out)
{
    if (p != nullptr)
    {
        Stack *t = p;
        out = t->info;
        p = p->next;
        delete t;
    }
    return p;
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

bool isNum(char ch)
{
    return ch >= '0' && ch <= '9';
}

bool isChar(char ch)
{
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

int Prior(char op)
{
    switch (op)
    {
    case '^':
        return 3;
    case '*':
    case '/':
        return 2;
    case '+':
    case '-':
        return 1;
    case '(':
        return 0;
    default:
        return -1;
    }
}

void ConvertToPolish(const char mathRecord[], char output[])
{
    Stack *stackTop = nullptr;
    int outIndex = 0;
    for (int i = 0; mathRecord[i] != '\0'; i++)
    {
        char ch = mathRecord[i];
        if (isChar(ch) || isNum(ch))
        {
            output[outIndex++] = ch;
        }
        else if (ch == '(')
        {
            stackTop = InStack(stackTop, ch);
        }
        else if (ch == ')')
        {
            char temp;
            while (stackTop && stackTop->info != '(')
            {
                stackTop = OutStack(stackTop, temp);
                output[outIndex++] = temp;
            }
            stackTop = OutStack(stackTop, temp);
        }
        else
        {
            while (stackTop && Prior(stackTop->info) >= Prior(ch))
            {
                char temp;
                stackTop = OutStack(stackTop, temp); // так сказать вытаскиваем вершину
                output[outIndex++] = temp;           // кидаем сразу в массив
            }
            stackTop = InStack(stackTop, ch);
        }
    }
    while (stackTop)
    {
        char temp;
        stackTop = OutStack(stackTop, temp);
        output[outIndex++] = temp;
    }
    output[outIndex] = '\0';
}

double pow(double base, int exp)
{
    double result = 1;
    for (int i = 0; i < exp; i++)
    {
        result *= base;
    }
    return result;
}

double calcRes(const char polRecord[], double values[26])
{
    Stack *stackTop = nullptr;

    char temp_var = 'z';

    for (int i = 0; polRecord[i] != '\0'; i++)
    {
        char ch = polRecord[i];
        if (isChar(ch))
        {
            stackTop = InStack(stackTop, ch);
        }
        else
        {
            char op1, op2; // операнды
            stackTop = OutStack(stackTop, op2);
            stackTop = OutStack(stackTop, op1);

            double a = values[op1 - 'a']; // тут мы каждой переменной присваиваем значение
            double b = values[op2 - 'a'];
            double res = 0;

            switch (ch)
            {
            case '+':
                res = a + b;
                break;
            case '-':
                res = a - b;
                break;
            case '*':
                res = a * b;
                break;
            case '/':
                if (b == 0)
                {
                    cerr << "Ошибка: деление на ноль!\n";
                    exit(1);
                }
                res = a / b;
                break;
            case '^':
                res = pow(a, b);
                break;
            }

            values[temp_var - 'a'] = res;
            stackTop = InStack(stackTop, temp_var);
        }
    }

    char final;
    stackTop = OutStack(stackTop, final);
    return values[final - 'a'];
}

int main()
{
    char mathRecord[maxSize];
    char polRecord[maxSize];
    cout << "Введите выражение: ";
    cin >> mathRecord;

    ConvertToPolish(mathRecord, polRecord);
    cout << "Обратная польская запись: " << polRecord << endl;
    double values[26] = {0};

    for (int i = 0; mathRecord[i] != '\0'; i++)
    {
        char ch = mathRecord[i];
        if (isChar(ch) && values[ch - 'a'] == 0)
        {
            cout << "Введите значение для " << ch << ": ";
            cin >> values[ch - 'a'];
        }
    }

    double result = calcRes(polRecord, values);
    cout << "Результат: " << result << endl;
    return 0;
}
