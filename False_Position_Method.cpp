#include <bits/stdc++.h>

using namespace std;

double E = 1e-4;
double coeff[5];

double f(double x)
{
    return coeff[4] * pow(x, 4) + coeff[3] * pow(x, 3) + coeff[2] * pow(x, 2) + coeff[1] * pow(x, 1) + coeff[0];
}

double FalsePositionMethod(double x1, double x2, int &itr)
{
    double x0 = x1-((f(x1) * (x2 - x1)) / (f(x2) - f(x1)));
    itr = 0;

    while (fabs((x2 - x1) / x1) >= E)
    {

        x0 = x1-((f(x1) * (x2 - x1)) / (f(x2) - f(x1)));

        if (f(x0) == 0.0)
        {
            break;
        }

        else if (f(x0) * f(x1) < 0)
        {
            x2 = x0;
        }

        else if (f(x0) * f(x2) < 0)
        {
            x1 = x0;
        }

        itr++;
    }

    return (x1 + x2) / 2.0;
}

int main()
{
    cout << "Enter the coefficients: ";
    double a4, a3, a2, a1, a0;

    for (int i = 4; i >= 0; i--)
    {
        cin >> coeff[i];
    }

    a4 = coeff[4];
    a3 = coeff[3];
    a2 = coeff[2];
    a1 = coeff[1];
    a0 = coeff[0];

    double x_max = sqrt(pow((a3 / a4), 2) - (2 * (a2 / a4)));

    double l = -fabs(x_max);
    double h = fabs(x_max);
    double stepsz = 0.5;
    int rootcount = 0;
    int itr = 0;
    double a = l;

    while (a < h)
    {
        double b = a + stepsz;

        if (f(a) * f(b) < 0)
        {
            rootcount++;
            double res = FalsePositionMethod(a, b, itr);
            cout << rootcount << "th: " << res << endl;
            cout << "Search interval: [" << a << ", " << b << "]" << endl;
            cout << "Iteration needed: " << itr << endl;
        }

        a = b;
    }

    if (rootcount == 0)
    {
        cout << "There is no real root!" << endl;
    }

    return 0;
}
