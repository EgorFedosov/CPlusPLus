#include <iostream>

using namespace std;

// проверка на корректность
bool isValidInfix(char *infix)
{
    int len = 0;
    while (infix[len] != '\0')
        len++;

    bool lastWasLetterOrDigit = false;
    bool lastWasOperator = false;
    bool lastWasClosingBracket = false;
    int openBrackets = 0;

    for (int i = 0; i < len; i++)
    {
        char c = infix[i];
        if (c == ' ')
            continue;

        bool isLetter = (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
        bool isDigit = (c >= '0' && c <= '9');
        bool isOperator = c == '+' || c == '-' || c == '*' || c == '/';
        bool isBracket = c == '(' || c == ')';

        if (!(isLetter || isDigit || isOperator || isBracket))
            return false;

        if (isOperator)
        {
            if (i == 0) 
                return false;

            if (lastWasOperator) // a++b
                return false;

            if (infix[i + 1] == '\0') // a*
                return false;
        }

        if (isLetter || isDigit)
        {
            if (lastWasLetterOrDigit || lastWasClosingBracket) // )2
                return false;
            lastWasLetterOrDigit = true;
            lastWasOperator = false;
            lastWasClosingBracket = false;
        }
        else if (c == ')')
        {
            openBrackets--;
            if (openBrackets < 0) // check (())
                return false;
            lastWasLetterOrDigit = false;
            lastWasOperator = false;
            lastWasClosingBracket = true;
        }
        else
        {
            if (c == '(')
                openBrackets++;
            lastWasLetterOrDigit = false;
            lastWasOperator = isOperator;
            lastWasClosingBracket = false;
        }
    }

    if (openBrackets != 0)
        return false;

    return true;
}

// переводим в опз и запрашиваем значения переменных
void infixToPostfixAndGetValues(char *infix, char *postfix, char vars[], double values[], int &varCount)
{
    char opStack[100];
    int opTop = -1;
    int j = 0;
    varCount = 0;

    for (int i = 0; infix[i] != '\0'; i++)
    {
        char c = infix[i];
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        {
            bool found = false;
            for (int k = 0; k < varCount; k++)
            {
                if (vars[k] == c)
                {
                    found = true;
                    break;
                }
            }
            if (!found && varCount < 26)
            {
                vars[varCount] = c;
                bool validInput = false;
                do
                {
                    cout << "Введите значение для переменной " << c << ": ";
                    if (cin >> values[varCount])
                    {
                        validInput = true;
                    }
                    else
                    {
                        cout << "Ошибка: введите корректное числовое значение" << endl;
                        cin.clear();
                        cin.ignore();
                    }
                } while (!validInput);
                cin.ignore();
                varCount++;
            }
        }
    }

    for (int i = 0; infix[i] != '\0'; i++)
    {
        char c = infix[i];
        if (c == ' ')
            continue;
        if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        {
            postfix[j++] = c;
        }
        else if (c == '(')
        {
            opStack[++opTop] = c;
        }
        else if (c == ')')
        {
            while (opTop >= 0 && opStack[opTop] != '(')
            {
                postfix[j++] = ' ';
                postfix[j++] = opStack[opTop--];
            }
            if (opTop >= 0)
                opTop--;
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/')
        {
            postfix[j++] = ' ';

            int priority;
            if (c == '+' || c == '-')
                priority = 1;
            else
                priority = 2;

            while (opTop >= 0 && opStack[opTop] != '(')
            {
                int topPriority;
                if (opStack[opTop] == '*' || opStack[opTop] == '/')
                    topPriority = 2;
                else
                    topPriority = 1;

                if (topPriority >= priority)
                {
                    postfix[j++] = opStack[opTop--];
                    postfix[j++] = ' ';
                }
                else
                {
                    break;
                }
            }

            opStack[++opTop] = c;
        }
    }

    while (opTop >= 0)
    {
        postfix[j++] = ' ';
        postfix[j++] = opStack[opTop--];
    }
    postfix[j] = '\0';
}

// считаем
double evaluatePostfix(char *postfix, char vars[], double values[], int varCount)
{
    double numStack[100];
    int numTop = -1;

    for (int i = 0; postfix[i] != '\0'; i++)
    {
        char c = postfix[i];
        if (c == ' ')
            continue;
        if (c >= '0' && c <= '9')
        {
            numStack[++numTop] = c - '0';
        }
        else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        {
            for (int j = 0; j < varCount; j++)
            {
                if (vars[j] == c)
                {
                    numStack[++numTop] = values[j];
                    break;
                }
            }
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/')
        {
            if (numTop < 1)
            {
                cout << "Ошибка: некорректное выражение" << endl;
                return 0.0;
            }
            double b = numStack[numTop--];
            double a = numStack[numTop--];
            switch (c)
            {
            case '+':
                numStack[++numTop] = a + b;
                break;
            case '-':
                numStack[++numTop] = a - b;
                break;
            case '*':
                numStack[++numTop] = a * b;
                break;
            case '/':
                if (b == 0)
                {
                    cout << "Ошибка: деление на ноль!" << endl;
                    return 0.0;
                }
                numStack[++numTop] = a / b;
                break;
            }
        }
    }
    return numStack[numTop];
}

int main()
{
    char infix[100], postfix[100];
    char variables[26];
    double varValues[26];
    int varCount = 0;

    bool validInput = false;
    do
    {
        cout << "Введите инфиксное выражение (например, a+b*2 или 3+4*2): ";
        cin.getline(infix, 100);

        int len = 0;
        while (infix[len] != '\0')
            len++;

        if (len == 0)
        {
            cout << "Ошибка: пустое выражение" << endl;
        }
        else if (!isValidInfix(infix))
        {
            cout << "Ошибка: некорректное выражение" << endl;
        }
        else
        {
            validInput = true;
        }
    } while (!validInput);

    infixToPostfixAndGetValues(infix, postfix, variables, varValues, varCount);

    cout << "Постфиксная нотация: " << postfix << endl;

    if (varCount > 0)
    {
        cout << "Значения переменных:" << endl;
        for (int i = 0; i < varCount; i++)
        {
            cout << variables[i] << " = " << varValues[i] << endl;
        }
    }

    double result = evaluatePostfix(postfix, variables, varValues, varCount);
    cout << "Результат выражения: " << result << endl;

    return 0;
}