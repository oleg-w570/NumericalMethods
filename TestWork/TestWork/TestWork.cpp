#include "TestWork.h"

TestWork::TestWork(double a, double b, double u0, double h0)
{
	mult2 = 0;
	div2 = 0;
	this->b = b;
	grid.push_back(a);
	true_values.push_back(u0);
	num_values.push_back(u0);
	grid_step.push_back(h0);
	d_num_values.push_back(u0);
}

double TestWork::Func(double u)
{
	return 2 * u;
}

double TestWork::TrueFunc(double x)
{
	return true_values.front() * exp(2 * (x - grid.front()));
}

double TestWork::NumFunc(double v, double h)
{
	double k1 = Func(v);
	double k2 = Func(v + h / 2 * k1);
	double k3 = Func(v + h / 2 * k2);
	double k4 = Func(v + h * k3);

	return (v + h / 6 * (k1 + 2 * k2 + 2 * k3 + k4));
}

double TestWork::DNumFunc(double v, double h)
{
	double v_tmp = NumFunc(v, h / 2);
	return NumFunc(v_tmp, h / 2);
}

void TestWork::MethodStep()
{
	double h = grid_step.back();
	double x = grid.back() + h;
	double u = TrueFunc(x);
	double v = NumFunc(num_values.back(), h);
	double v2 = DNumFunc(num_values.back(), h);
	double s = abs(v2 - v) / 15;

	if (s < EPS / 32)
	{
		h *= 2;
		mult2++;
	}
	else while (s > EPS)
	{
		h = h / 2;
		div2++;
		x = grid.back() + h;
		u = TrueFunc(x);
		v = NumFunc(num_values.back(), h);
		v2 = DNumFunc(num_values.back(), h);
		s = (v2 - v) / 15;
	}
	grid_step.push_back(h);
	grid.push_back(x);
	true_values.push_back(u);
	num_values.push_back(v);
	d_num_values.push_back(v2);
}

void TestWork::Run()
{
	int n = 0;
	while (grid.back() < b && n < 1000)
	{
		MethodStep();
		n++;
	}
}

void TestWork::Print()
{
	unsigned long long N = grid.size();
	for ( unsigned int i = 0; i < N; i++)
	{
		std::cout << "Num: (" << grid[i] << ", " << num_values[i] << ")" << "\tTrue: (" << grid[i] << ", " << true_values[i] << ")"
		<< "\th = " << grid_step[i] << "\tvD = " << d_num_values[i]
		<< "\tDiff = " << true_values[i] - num_values[i]
		<< std::endl;
	}
	std::cout << "\nmult2 = " << mult2 << ", div2 = " << div2 << std::endl;
}
