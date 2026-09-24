#include<bits/stdc++.h>

using namespace std;

int n;

vector<double> gaussJordan(vector<vector<double>> &augmat)
{
    for(int j=0; j<n; j++)
    {
        int max_row=j;

        for(int i=j+1; i<n; i++)//max row ber kora
        {
            if(abs(augmat[i][j]) > abs(augmat[max_row][j]))
            {
                max_row=i;
            }
        }

        if(abs(augmat[max_row][j]) < 1e-9)//no unique solution
        {
            cout << "No Unique Solution" << endl;
            exit(1);
        }

        swap(augmat[j], augmat[max_row]);//max row swap kora

        //next kaj pivot element gulo ke 1 banano
            double pivot = augmat[j][j];

            for(int k=0; k<=n; k++)
            {
                augmat[j][k]/=pivot;
            }
        

        //next kaj row reduced echelon form a neya
        for(int i=0; i<n; i++)
        {
            if(i==j)
            {
                continue; 
            }

            double ratio = augmat[i][j]/augmat[j][j];

            for(int k=0; k<=n; k++)
            {
                augmat[i][k]-=augmat[j][k]*ratio;
            }
        }

   
    }

    cout << endl;
    cout << "Row Reduced Echelon Form: " << endl;

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n+1; j++)
        {
            double val =augmat[i][j];

            if(abs(val) < 1e-9)
            {
                val = 0.0;
            }

            cout << fixed << setprecision(3) << setw(10) <<  val << " ";
        }

        cout << endl;
    }

    //solution vector return korte hobe
    vector<double> x(n, 0.0);
    for(int i=0; i<n; i++)
    {
        x[i]=augmat[i][n];
    }

    return x;

}

int main()
{
    cout << "Enter the number of systems: ";
    cin >> n;
    cout << endl;

    vector<vector<double>> augmat(n, vector<double>(n+1, 0.0));

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n+1; j++)
        {
            cin >> augmat[i][j];
        }
    }

    vector<vector<double>> original = augmat;

    vector<double> x = gaussJordan(augmat);

    cout << "Solution: " << endl;
    for(int i=0; i<n; i++)
    {
        cout << "x" << i+1 << " = " << fixed << setprecision(3) << x[i] << endl;
    }

    cout << endl;

    return 0;
}