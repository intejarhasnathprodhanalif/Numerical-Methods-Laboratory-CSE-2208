#include <bits/stdc++.h>

using namespace std;

double E = 1e-3;
vector<double> coeff;
double step = 0.45;
int degree;

// Horner's method to evaluate f(x)
double f(double x)
{
    double result = coeff[degree];
    for (int i = degree - 1; i >= 0; i--)
    {
        result = result * x + coeff[i];
    }
    return result;
}

// Horner's method to evaluate the derivative f'(x)
double df(double x)
{
    if (degree == 0)
        return 0.0; // Derivative of a constant is 0

    double result = coeff[degree] * degree;
    for (int i = degree - 1; i >= 1; i--)
    {
        result = result * x + (coeff[i] * i);
    }
    return result;
}

void printFunction()
{
    cout << "Function: ";
    for (int i = degree; i >= 0; i--)
    {
        if (i < degree && coeff[i] >= 0)
        {
            cout << "+ ";
        }
        else if (i < degree && coeff[i] < 0)
        {
            cout << "- ";
        }
        else if (i == degree && coeff[i] < 0)
        {
            cout << "-";
        }

        cout << fabs(coeff[i]);
        if (i > 0)
        {
            cout << "x^" << i << " ";
        }
    }
    cout << " = 0" << endl;
}

// Newton-Raphson Method
double NewtonRaphsonMethod(double x0, int &itr)
{
    double x1 = 0.0;
    itr = 0;
    int max_itr = 1000; // Safety safeguard

    while (itr < max_itr)
    {
        double df_val = df(x0);

        // Prevent division by zero if the tangent is perfectly horizontal
        if (fabs(df_val) < 1e-12)
        {
            return x0;
        }

        // Newton-Raphson formula: x_new = x_old - f(x_old) / f'(x_old)
        x1 = x0 - (f(x0) / df_val);
        itr++;

        // Check stopping criteria
        if (fabs(x1 - x0) < E && fabs(f(x1)) < E)
        {
            break;
        }

        x0 = x1;
    }

    return x1;
}

int main()
{
    cout << "Input degree of equation: ";
    cin >> degree;

    coeff.resize(degree + 1);

    cout << "Enter coefficients (from highest degree to constant): ";
    for (int i = degree; i >= 0; i--)
    {
        cin >> coeff[i];
    }

    double max_ratio = 0.0;
    for (int i = 0; i < degree; i++)
    {
        double ratio = fabs(coeff[i] / coeff[degree]);
        if (ratio > max_ratio)
        {
            max_ratio = ratio;
        }
    }

    double x_max = 1.0 + max_ratio;

    printFunction();

    double Y = -fabs(x_max);
    int rootcount = 1;

    while (Y < x_max)
    {
        double Z = Y + step;

        if (Z > x_max)
        {
            Z = x_max;
        }

        if (f(Y) * f(Z) < 0 || f(Y) == 0.0)
        {
            int itr = 0;
            // Use the midpoint of the bracket as the initial guess
            double guess = (Y + Z) / 2.0;

            double root = NewtonRaphsonMethod(guess, itr);

            cout << "\nRoot " << rootcount << ": " << root << endl;
            cout << "Search Interval: [" << Y << ", " << Z << "]" << endl;
            cout << "Iteration Needed: " << itr << endl;

            rootcount++;
        }

        Y = Z;
    }

    if (rootcount == 1)
    {
        cout << "\nNo real root in the domain!" << endl;
    }

    return 0;
}