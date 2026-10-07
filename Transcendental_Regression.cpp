#include<bits/stdc++.h>

using namespace std;

void Linear(vector<double> &X, vector<double> &Y, double &a, double &b)
{
    int n = X.size();
    double sx=0, sy=0, sxx=0, sxy=0;

    for(int i=0; i<n; i++)
    {
        sx+=X[i];
        sy+=Y[i];
        sxx+=X[i]*X[i];
        sxy+=X[i]*Y[i];
    }

    b=(n*sxy - sx*sy)/(n*sxx - sx*sx);
    a=(sy-b*sx)/n;
}

int main()
{
    int n;
    cout << "Enter number of data: ";
    cin >> n;

    vector<double> z(n, 0);
    vector<double> y(n, 0);
    vector<double> x(n, 0);

    cout << "Enter values of z: ";

    for(int i=0; i<n; i++)
    {
        cin >> z[i];
    }

    cout << "Enter values for y: "; 

    for(int i=0; i<n; i++)
    {
        cin >> y[i];
    }

    for(int i=0; i<z.size(); i++)
    {
        x[i]=exp(z[i]/4);
    }

    double p, q;
    Linear(x, y, p, q);

    cout << "Equation: " << p << " + " << q << "*e^(z/4)" << endl;

    cout << "For z=6, " << endl;
    cout << "y = " << p+q*exp(6.0/4) << endl;

    return 0;
}