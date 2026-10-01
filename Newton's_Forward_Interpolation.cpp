#include<bits/stdc++.h>

using namespace std;

double factorial(int k)
{
    double f=1.0;

    for(int i=2; i<=k; i++)
    {
        f*=i;
    }

    return f;
}

int main()
{
    int n;
    cout << "Enter number of data points: ";
    cin >> n;

    vector<double> x(n), y(n);

    cout << "Enter the x values: ";
    for(int i=0; i<n; i++)
    {
        cin >> x[i];
    }

    cout << "Enter corresponding y values: ";
    for(int i=0; i<n; i++)
    {
        cin >> y[i];
    }

    double h=x[1]-x[0];


    //forward table value calculation
    vector<vector<double>> diff(n, vector<double>(n, 0.0));
    for(int i=0; i<n; i++)
    {
        diff[i][0]=y[i];
    }

    for(int j=1; j<n; j++)
    {
        for(int i=0; i<n-j; i++)
        {
            diff[i][j]-diff[i+1][j-1]-diff[i][j-1];
        }
    }

    //forward table print
    for(int i=0; i<n; i++)
    {
        cout << setw(10) << x[i] << setw(12) << diff[i][0];
        for(int j=1; j<n-i; j++)
        {
            cout << setw(12) << diff[i][j];
        }

        cout << endl;
    }

    //result calculation and print
    double result=diff[0][0];
    double term=1.0;
    double xval;
    cout << "Enter the point to interpolate at: ";
    cin >> xval;
    double u=(xval-x[0])/h;

    for(int k=1; k<n; k++)
    {
        term*=(u-(k-1));
        result+=(term/factorial(k)) * diff[0][k];
    }

    cout << "u=(x-x[0])/h = " << u << endl;
    cout << "The interpolated value at x = " << xval << " is y = " << result << endl; 

    return 0;
}