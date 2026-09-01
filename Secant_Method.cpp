#include<bits/stdc++.h>

using namespace std;

double E=1e-3;
vector<double> coeff;
double step=0.45;
int degree;

double f(double x)
{
    double result=coeff[degree];

    for(int i=degree-1; i>=0; i--)
    {
        result=result*x + coeff[i];
    }

    return result;
}

void printFunction()
{
    cout << "Function: ";
    
    for(int i=degree; i>=0; i--)
    {
        if(i<degree && coeff[i]>0 && coeff[i]!=0)
        {
            cout << "+ ";
        }

        else if(i>degree && coeff[i]<0 && coeff[i]!=0)
        {
            cout << "- ";
        }

        else if(coeff[i]<0 && coeff[i]!=0)
        {
            cout << "- ";
        }

        if(coeff[i]!=0 && coeff[i]!=1)
        {
            cout << fabs(coeff[i]);
        }

        if(coeff[i]!=0)
        {
            if (i > 0)
            {
                cout << "x^" << i << " ";
            }
        }
    }

    cout << " = 0" << endl;
}

double SecantMethod(double x0, double x1, int &itr)
{
    double x2=0.0;
    itr=0;

    while(true)
    {
        if(fabs(f(x1)-f(x0)) < 1e-12)
        {
            return x1;
        }

        x2=x1-(f(x1)*((x1-x0)/(f(x1)-f(x0))));
        itr++;

        if(fabs(x2-x1)<E && fabs(f(x2))<E)
        {
            break;
        }

        x0=x1;
        x1=x2;
    }
    
    return x2;
}

int main()
{
    cout << "Input degree of equation: ";
    cin >> degree;

    coeff.resize(degree+1);

    cout << "Enter coefficients: ";
    for(int i = degree; i>=0; i--)
    {
        cin >> coeff[i];
    }

    double max_ratio=0.0;
    for(int i=0; i<=degree; i++)
    {
        double ratio=abs(coeff[i]/coeff[degree]);

        if(ratio>max_ratio)
        {
            max_ratio=ratio;
        }
    }

    double x_max=1.0+max_ratio;

    printFunction();

    double Y=-fabs(x_max);
    int rootcount=1;

    while(Y<x_max)
    {
        double Z=Y+step;

        if(Z>x_max)
        {
            Z=x_max;
        }

        if(f(Y)*f(Z) < 0 || f(Y)==0.0)
        {
            int itr=0;

            double root=SecantMethod(Y, Z, itr);

            cout << "Root " << rootcount << ": " << root << endl;

            cout << "Search Interval: [" << Y << ", " << Z << "]" << endl;
            
            cout << "Iteration Needed: " << itr << endl;

            rootcount++;
        }

        Y=Z;

    }

    if(rootcount==1)
    {
        cout << "No real root in the domain!" << endl;
    }

    else if(rootcount<degree)
    {
        cout << "rest " << degree-rootcount+1 << " roots are not real" << endl;
    }

    return 0;
}
