#include <iostream>
#include <omp.h>
#include <math.h>

double func(double* y, double t, int i)
{
	double u = 0.0;
	switch (i)
	{
	case 0: u = 2.0 * (y[0] - y[0] * y[1]); break;
	case 1: u = - (y[1] - y[1]); break;
	}
	return u;
}

int main()
{
	const int n = 2;
	double t0 = 0.0, tmax = 5.0, tau = 0.01, t = t0, tn, tk, deltat;
	double y[n] = { 1.0, 3.0 };
	double yy[n] = { 0.0 };

	tn = omp_get_wtime();
	for (double t = t0; t <= tmax; t += tau)
	{
		for (int i = 0; i < n; i++)
		{
			yy[i] = y[i] + tau * func(y, t, i);
		}
		for (int i = 0; i < n; i++)
			y[i] = yy[i];
	}

	tk = omp_get_wtime();
	deltat = tk - tn;
	std::cout << "Delta t = "<< deltat << std::endl;
	for (int i = 0; i < n; i++)
	{
		std::cout << "Element[" << i << "]: " << y[i]<< std::endl;
	}
	return 0;
}