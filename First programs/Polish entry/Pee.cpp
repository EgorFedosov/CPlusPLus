#include <iostream>

using namespace std;

bool isValidInfix(char *infix)
{
        int len = 0;
        while (infix[len] != '\0') len++;
        
    int openBrackets = 0;
        bool lastWasLetter = false;
        
    for (int i = 0; i < len; i++)
    {
                char c = infix[i];
                if (c == ' ') continue;
                
        bool isValidChar = (c >= '0' && c <= '9') ||
                          (c >= 'A' && c <= 'Z') ||
                          (c >= 'a' && c <= 'z') ||
                          c == '+' || c == '-' || c == '*' ||
                          c == '/' || c == '(' || c == ')';
                if (!isValidChar) return false;
                
        bool isLetter = (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
                if (isLetter)
        {
                        if (lastWasLetter)
            {
                                return false;
                           
            }
                        lastWasLetter = true;
                   
        }
        else
        {
                        lastWasLetter = false;
                   
        }
                
        if (c == '(') openBrackets++;
                if (c == ')')
        {
                        openBrackets--;
                        if (openBrackets < 0) return false;
                   
        }
           
    }
        return openBrackets == 0;
}

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
                                                cin.ignore(10000, '\n');
                                           
                    }
                                   
                }
                while (!validInput)
                    ;
                                cin.ignore();
                                varCount++;
                           
            }
                   
        }
           
    }

        for (int i = 0; infix[i] != '\0'; i++)
    {
                char c = infix[i];
                
        if (c == ' ') continue;
                
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
                        if (opTop >= 0) opTop--;
                   
        }
                else if (c == '+' || c == '-' || c == '*' || c == '/')
        {
                        postfix[j++] = ' ';
                        int priority = (c == '+' || c == '-') ? 1 : 2;
                        while (opTop >= 0 && opStack[opTop] != '(' &&
                   ((opStack[opTop] == '*' || opStack[opTop] == '/') ? 2 : 1) >= priority)
            {
                                postfix[j++] = opStack[opTop--];
                                postfix[j++] = ' ';
                           
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

double evaluatePostfix(char *postfix, char vars[], double values[], int varCount)
{
        double numStack[100];
        int numTop = -1;
        
    for (int i = 0; postfix[i] != '\0'; i++)
    {
                char c = postfix[i];
                
        if (c == ' ') continue;
                
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
                while (infix[len] != '\0') len++;
                
        if (len == 0)
        {
                        cout << "Ошибка: пустое выражение" << endl;
                   
        }
                else if (!isValidInfix(infix))
        {
                        cout << "Ошибка: некорректное выражение (две буквы не могут идти подряд)" << endl;
                   
        }
                else
        {
                        validInput = true;
                   
        }
           
    }
    while (!validInput)
        ;
        
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
