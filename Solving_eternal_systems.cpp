#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector <double> Iteration(vector < vector <double> > Arr, vector <double> FreeM)
{
    int N = Arr.size();
    vector <double> x;
    x.resize(N);
    vector <double> x0;
    x0.resize(N);
    double eps = 0.001;

    for (int i = 0; i < N; i++)
    {
        x0[i] = FreeM[i] / Arr[i][i];
    } // division by diagonal element
    do
    {
        for (int i = 0; i < N; i++)
        {
            x[i] = FreeM[i] / Arr[i][i];
            for (int j = 0; j < N; j++)
            {
                if (i == j) { continue; }
                else
                {
                    x[i] -= Arr[i][j] / Arr[i][i] * x0[j];
                }

            }
        }
        bool flag = true;
        for (int i = 0; i < N - 1; i++) // Checking the proximity to our accuracy
        {
            if (abs(x[i] - x0[i]) > eps)
            {
                flag = false;
                break;
            }
        }
        for (int i = 0; i < N; i++) // saving last approximation
        {
            x0[i] = x[i];
        }

        if (flag) { break; } // condition of ending the recursion
    } while (1);
    return x;
}


double solve_c_ik(int i, int k)
{
    double c = 0;
    return c = 1.0 / ((2.0 * i + 1.0 - 2.0 * k) * (2.0 * i - 1.0 - 2.0 * k));
}

int main()
{
    vector < vector <double> > Arr;
    vector < vector <double> > Arr_new;
    vector <double> x_k;
    vector <double> x_k_new;
    vector <double> b_i = { -1, 0, 0, 0, 0 };
    int N = 5;
    double eps = 0.001;
    bool check = false;

    for (int i = 0; i < N; i++)
    {
        Arr.push_back(vector <double>());
        for (int k = 0; k < N; k++)
        {
            Arr[i].push_back(0);
            Arr[i][k] = solve_c_ik(i, k);
        }
    }
    x_k_new = Iteration(Arr, b_i);


    do
    {
        b_i.push_back(0);
        x_k = x_k_new;

        Arr.push_back(vector <double>());
        for (int k = 0; k < N; k++)
        {
            Arr[N].push_back(0);
            Arr[N][k] = solve_c_ik(N, k);
        }
        for (int i = 0; i < N + 1; i++)
        {
            Arr[i].push_back(0);
            Arr[i][N] = solve_c_ik(i, N);
        }
        N++;
        x_k_new = Iteration(Arr, b_i);

        for (int i = 0; i < x_k.size(); i++)
        {
            if (abs(x_k_new[i] - x_k[i]) < eps) { check = true; }
            else { check = false; }
        }
    } while (check == false);

    cout << fixed;
    cout.precision(4);
    for (int i = 0; i < x_k_new.size(); i++) // Output of solution
    {
        cout << "x[" << i + 1 << "]= " << x_k_new[i] << "\t|\t";
        if (i % 3 == 0)
        {
            cout << "\n";
        }
    }

}
