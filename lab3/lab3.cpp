#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
int main()
{
    double a, b, h, rec, s, y, x;
    int k = 1;

    cout << "Enter a: ";
    cin >> a;
    cout << "Enter b: ";
    cin >> b;
    cout << "Enter h: ";
    cin >> h;
    cout << setw(10) << "x" << setw(15) << "Yx"
         << setw(15) << "Sx" << setw(15) << "|Sx - Yx|"
         << setw(10) << "steps" << endl;

    for (x = a; x <= b + h / 2; x += h)
    {
        y = (((x * x) / 4 + x / 2) + 1) * exp(x / 2);
        s = 1.0;
        k = 1;
        rec = 1.0;
        double l = 1;
        do
        {
            l *= x / 2; // pow.
            rec *= 1.0 / k;
            s += rec * (k * k + 1) * l;
            k++;
        } while (fabs(s - y) >= 0.001);

        cout << setw(10) << x << setw(15) << y << setw(15)
             << s << setw(15) << fabs(s - y) << setw(10) << k << endl;
    }
    return 0;
}