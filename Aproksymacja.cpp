#include <iostream>
#include <cmath>

using namespace std;
const double eps = 1e-12;

bool gauss(int n, double** AB, double* X)// za pomocą tej funkcji wykonuje się cały algorytm eliminacji gaussa
{
	double m, s;

	// przy pomocy poniższych forów eliminuje współczynniki 
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (fabs(AB[i][i]) < eps)
			{
				return false;
			}
			m = -AB[j][i] / AB[i][i];
			AB[j][i] = 0;
			for (int k = i + 1; k <= n; k++)
			{
				AB[j][k] += m * AB[i][k];
			}
		}
	}

	// przy pomocy poniższych forów wyliczam niewiadome

	for (int i = n - 1; i >= 0; i--)
	{
		s = AB[i][n];

		for (int j = n - 1; j >= i + 1; j--)
		{
			s -= AB[i][j] * X[j];
		}
		if (fabs(AB[i][i]) < eps)
		{
			return false;
		}

		X[i] = s / AB[i][i];
	}


	return true;
}

int main()
{
	const int m = 8; // liczba punktów
	int w = 2; // stopień wielomianu 
	double X[m] = { 1, 2, 3, 4, 5, 6, 7, 8 }; // węzeł
	double Y[m] = { 2, 4, 3, 5, 6, 9, 11, 11 }; // wartości
	double F[2];
	double Fw = 1;
	
	double** M = new double* [4];
	for (int i = 0; i < 4; i++)
	{
		M[i] = new double[4];
	}
	double g = 0.0;
	
	cout << "Liczba wezlow: " << m << endl << endl;

	cout << "Punkty: " << endl;

	for (int i = 0; i < m; i++)
	{
		cout << "(" << X[i] << ", " << Y[i] << ")";
	}
	cout << endl << endl;

	cout << "Macierz:" << endl; // Poniżej liczę współczynniki wielomianu aproksymującego

	for (int k = 0; k < w; k++)
	{
		for (int j = 0; j < w; j++)
		{
			for (int i = 0; i < m; i++)
			{
				g += pow(X[i], k) * pow(X[i], j) * Fw;
			}
			M[k][j] = g;
			g = 0;
			cout << M[k][j] << "	";
		}
		cout << endl;
	}

	cout << endl << "--------------------------------------------------------------------------------" << endl << endl; //Poniżej liczę wartości funkcji

	for (int k = 0; k < w; k++)
	{
		for (int i = 0; i < m; i++)
		{
			g += pow(X[i], k) * Y[i] * Fw;
		}
		F[k] = g;
		g = 0;
		cout << "F" << k << " = " << F[k] << endl;
	}

	cout << endl << "--------------------------------------------------------------------------------" << endl << endl; //Poniżej rozwiązuje układ rówanń metodą gaussa

	int n = 2;

	double** AB = new double* [n + 1];
	for (int i = 0; i < n + 1; i++)
	{
		AB[i] = new double[n + 1];
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			AB[i][j] = M[i][j];
		}
		AB[i][2] = F[i];
	}


	if (gauss(n, AB, X)) // uruchamiamy naszą funkcję liczącą (eliminację gaussa)
	{
		for (int i = 0; i < n; i++)
		{
			cout << "a" << i + 1 << " = " << X[i] << endl; // wypisanie wyników
		}
	}
	else
	{
		cout << "DZIELNIK ZERO" << endl; // jeśli będziemy dzielić przez 0 kompilator to wypisze
	}

	for (int i = 0; i < n; i++)
	{
		delete[] AB[i];
	}
	delete[] AB;

	cout << endl;

	double y[8] = {NULL};
	double X12[2] = { 1, 2 };

	for (int k = 0; k < 2; k++)
	{
		for (int i = 0; i < m; i++)
		{
			if (k == 1)
			{
				if (i < 2)
					y[i] += X12[i] * X[k];
				else
					y[i] += X[i] * X[k];
			}
			else
			{
				y[i] = X[k];
			}
		}
	}

	for (int i = 0; i < m; i++)
	{
		cout << "y" << i + 1 << " = " << y[i] << endl;
	}

	return 0;
}