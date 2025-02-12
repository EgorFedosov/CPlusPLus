#include <iostream>
#include <cmath>

using namespace std;
int main()
{
    int f;
    double x, y, z, d, a, fx;

    cout << "Enter f(x):  1) 2x   2) x^2   3) x/3 " << endl;
    cin >> f;
    cout << endl;

    cout << "Enter z: ";
    cin >> z;
    cout << endl;

    cout << "Enter a: ";
    cin >> a;
    cout << endl;

    cout << "Enter d: ";
    cin >> d;
    cout << endl;

    switch (f)
    {
    case 1:
        if (z > 0)
        {
            x = -3 * z;
            fx = 2 * x;
            y = 2 * fx * (a * sin(x) + d * exp(-(x + 3)));
            cout << "x = -3z: " << x << "   "
                 << "f(x) = 2x: " << fx << endl
                 << "y: " << y;
        }

        if (z <= 0)
        {
            x = z * z;
            fx = 2 * x;
            y = 2 * fx * (a * sin(x) + d * exp(-(x + 3)));
            cout << "x = z^2: " << x << "   "
                 << "f(x) = 2x: " << fx << endl
                 << "y: " << y;
        }

        break;

    case 2:
        if (z > 0)
        {
            x = -3 * z;
            fx = x * x;
            y = 2 * fx * (a * sin(x) + d * exp(-(x + 3)));
            cout << "x = -3z: " << x << "   "
                 << "f(x) = x^2: " << fx << endl
                 << "y: " << y;
        }

        if (z <= 0)
        {
            x = z * z;
            fx = x * x;
            y = 2 * fx * (a * sin(x) + d * exp(-(x + 3)));
            cout << "x = z^2: " << x << "   "
                 << "f(x) = x^2: " << fx << endl
                 << "y: " << y;
        }

        break;

    case 3:
        if (z > 0)
        {
            x = -3 * z;
            fx = x / 3;
            y = 2 * fx * (a * sin(x) + d * exp(-(x + 3)));
            cout << "x = -3z: " << x << "   "
                 << "f(x) = x / 3: " << fx << endl
                 << "y: " << y;
        }

        if (z <= 0)
        {
            x = z * z;
            fx = x / 3;
            y = 2 * fx * (a * sin(x) + d * exp(-(x + 3)));
            cout << "x = z^2: " << x << "   "
                 << "f(x) = x / 3: " << fx << endl
                 << "y: " << y;
        }

        break;
    default:
        break;
    }
    return 0;
}