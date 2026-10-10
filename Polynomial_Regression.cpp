#include<bits/stdc++.h>

using namespace std;

vector<double> Polynomial(vector<double> &x, vector<double> &y, int m)
{
    int n = x.size();

    vector<vector<double>> M(m+1, vector<double>(m+2, 0));

    //augmented matrix

    for(int i=0; i<=m; i++)
    {
        for(int j=0; j<=m; j++)
        {
            for(int k=0; k<n; k++)
            {
                M[i][j] += pow(x[k], i+j);
            }
        }

        for(int k=0; k<n; k++)
        {
            M[i][m+1] += pow(x[k], i)*y[k];
        }
    }

    //Gauss Jordan Elimination

    for(int i=0; i<=m; i++)
    {
        double p = M[i][i];

        for(int c=0; c<=m+1; c++)
        {
            M[i][c]/=p;
        }

        for(int r=0; r<=m; r++)
        {
            if(r!=i)
            {
                double f=M[r][i];

                for(int c=0; c<=m+1; c++)
                {
                    M[r][c]-=f*M[i][c];
                }
            }
        }
    }

    //answer

    vector<double> a(m+1);
    for(int i=0; i<=m; i++)
    {
        a[i]=M[i][m+1];
    }

    return a;

}

int main()
{
    int n;
    cout << "Enter number of data: ";
    cin >> n;

    vector<double> x(n, 0);
    vector<double> y(n, 0);

    cout << "Enter values for x: ";
    for(int i=0; i<n; i++)
    {
        cin >> x[i];
    }

    cout << "Enter values for y: ";
    for(int i=0; i<n; i++)
    {
        cin >> y[i];
    }

    int m;
    cout << "Enter order of equation: ";
    cin >> m;

    int x0;
    cout << "Enter value to estimate for: ";
    cin >> x0;

    vector<double> a=Polynomial(x, y, m);

    cout << "Equation, y = ";
    for (int i = 0; i <= m; i++)
    {
        cout << a[i] << "*x^" << i;
        if (i < m)
        {
            cout << " + ";
        }
    }
    cout << endl;

    double y0 = 0;
    for (int i = 0; i <= m; i++)
    {
        y0 += a[i] * pow(x0, i);
    }

    cout << "y at x = " << x0 << " is " << y0 << endl;

    return 0;
}