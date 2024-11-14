#include <iostream>
using namespace std;
int main()
{
    int n, m;
    cout << "Enter n and m: ";
    cin >> n >> m;

    int s[n][m];

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
        {
            cout << "Enter s[" << i << "]" << "[" << j << "]: ";
            cin >> s[i][j];
        }
    return 0;
}