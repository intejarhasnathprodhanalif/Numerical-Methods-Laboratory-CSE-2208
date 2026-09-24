#include<bits/stdc++.h>

using namespace std;

const double E = 1e-4;
int n;
vector<vector<double>> A; //co-efficient matrix
vector<double> b; //constant matrix
vector<vector<double>> L, U; //lower and upper triangular matrix
vector<double> y, x; //y for forward substitution, x for backward sunstitution

void printMatrix(vector<vector<double>> &M);

//Crout's Method
void Crout()
{
    L.assign(n, vector<double>(n, 0.0));
    U.assign(n, vector<double>(n, 0.0));

    for(int i=0; i<n; i++)
    {
        U[i][i]=1.0;
    }

    for(int j=0; j<n; j++)
    {
        for(int i=j; i<n; i++)
        {
            double sum=0.0;

            for(int k=0; k<j; k++)
            {
                sum+=L[i][k]*U[k][j];
            }

            L[i][j]=A[i][j]-sum;
        }

        for(int i=j+1; i<n; i++)
        {
            double sum=0.0;

            for(int k=0; k<j; k++)
            {
                sum+=L[j][k]*U[k][i];
            }

            if((L[j][j]) < E)
            {
                U[j][i]=0.0;
            }

            else
            {
                U[j][i]=(A[j][i]-sum)/L[j][j];
            }

        }
    }
}

//DoLittle's Method
void DoLittle()
{
    L.assign(n, vector<double>(n, 0.0));
    U.assign(n, vector<double>(n, 0.0));

    for(int i=0; i<n; i++)
    {
        L[i][i]=1.0;
    }

    for(int j=0; j<n; j++)
    {
        for(int i=j; i<n; i++)
        {
            double sum=0.0;

            for(int k=0; k<j; k++)
            {
                sum+=L[i][k]*U[k][j];
            }

            U[i][j]=A[i][j]-sum;
        }

        for(int i=j+1; i<n; i++)
        {
            double sum=0.0;

            for(int k=0; k<j; k++)
            {
                sum+=L[i][k]*U[k][j];
            }

            if(U[j][j]<E)
            {
                L[i][j]=0.0;
            }

            else
            {
                L[i][j]=(A[i][j]-sum)/U[j][j];
            }
        }
    }
}

//LU Decompose

void LUDecompose()
{
    //Decompose A into L & U
    Crout();
    //for doing it with DoLittle's Method
    //DoLittle();

    cout << "L: " << endl;
    printMatrix(L);
    cout << "U: " << endl;
    printMatrix(U);

    //forward substitution => L*y=b
    y.assign(n, 0.0);
    bool noSolution=false, infiniteSolution=false;

    for(int i=0; i<n; i++)
    {
        double sum=b[i];

        for(int k=0; k<i; k++)
        {
            sum-=L[i][k]*y[k];
        }

        if (fabs(L[i][i]) < E)
        {
            if (fabs(sum) < E)
            {
                infiniteSolution = true;
            }

            else
            {
                noSolution = true;
            }

            y[i] = 0.0;
        }

        else
        {
            y[i] = sum / L[i][i];
        }
    }

    //backward substitution => U*x=y
    x.assign(n, 0.0);
    for(int i=n-1; i>=0; i--)
    {
        double sum=y[i];

        for(int k=i+1; k<n; k++)
        {
            sum-=U[i][k]*x[k];
        }

        if (fabs(L[i][i]) < E)
        {
            if (fabs(sum) < E)
            {
                infiniteSolution = true;
            }

            else
            {
                noSolution = true;
            }

            x[i] = 0.0;
        }

        else
        {
            x[i] = sum / U[i][i];
        }

    }

    //report the result

    if(noSolution)
    {
        cout << "The system has no solution" << endl;
    }

    else if(infiniteSolution)
    {
        cout << "The system has infinite solutions" << endl;
    }

    else
    {
        cout << "This system has a unique solution"<< endl;
        cout << fixed << setprecision(3);

        cout << "y (from L*y = b):\n";
        for (int i = 0; i < n; i++)
        {
            cout << "  y" << i + 1 << " = " << y[i] << endl;
        }
            

        cout << endl << "x (final solution, from U*x = y):";
        for (int i = 0; i < n; i++)
        {
            cout << "  x" << i + 1 << " = " << x[i] << "\n";
        }
            
        cout << endl;
    }
    

}

void printMatrix(vector<vector<double>> &M)
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            cout << M[i][j] << " ";
        }

        cout << endl;
    }
}


int main()
{
    char a='y';

    while(a=='y' || a=='Y')
    {
        cout << "Enter nmuber of equations: ";
        cin >> n;

        A.assign(n, vector<double>(n, 0.0));
        b.assign(n, 0.0);

        cout << "Enter the augmented matrix: " << endl;
        for(int i=0; i<n; i++) //augmented matrix input[[A]|[b]]
        {
            for(int j=0; j<n; j++)
            {
                cin>>A[i][j];
            }

            cin >> b[i];
        }

        LUDecompose();

        cout << endl;
        cout << "Solve another system? (y/n): ";
        cin >> a;
        cout << endl;

    }
    
    return 0;
}