#include "TestWork.h"

TestWork::TestWork(double right_border, double initial_value, double initial_step, int max_steps, bool ctrl_local_err)
{
	mult2 = 0;
	div2 = 0;
	this->ctrl_local_err = ctrl_local_err;
	this->max_steps = max_steps;
	this->right_border = right_border;
    grid.push_back(0);
	grid_step.push_back(initial_step);
	true_values.push_back(initial_value);
	num_values.push_back(initial_value);
	d_num_values.push_back(initial_value);
	final_num_values.push_back(initial_value);
}

double TestWork::Func(double u)
{
    return -3/2 * u;
}

double TestWork::TrueFunc(double x)
{
    return true_values.front() * exp(-3/2 * x);
}

double TestWork::NumFunc(double v, double h)
{
	const double k1 = Func(v);
	const double k2 = Func(v + h / 2 * k1);
	const double k3 = Func(v + h / 2 * k2);
	const double k4 = Func(v + h * k3);

	return (v + h / 6 * (k1 + 2 * k2 + 2 * k3 + k4));
}

double TestWork::DNumFunc(double v, double h)
{
	const double v_tmp = NumFunc(v, h / 2);
	return NumFunc(v_tmp, h / 2);
}

void TestWork::MethodStep()
{
	double h = grid_step.back();
	const double v = NumFunc(final_num_values.back(), h);
	const double v2 = DNumFunc(final_num_values.back(), h);
	const double s = abs(v2 - v) / 15;

	if (s > EPS && ctrl_local_err)
	{
		grid_step.back() /= 2;
		div2++;
	}
	else
	{
		const double x = grid.back() + h;
		const double u = TrueFunc(x);
		if (s < EPS / 32 && ctrl_local_err)
		{
			h *= 2;
			mult2++;
		}

		grid_step.push_back(h);
		grid.push_back(x);
		true_values.push_back(u);
		num_values.push_back(v);
		d_num_values.push_back(v2);
		final_num_values.push_back(v + 16 * s);
	}
}

void TestWork::Run()
{
	int n = 0;
	while (grid.back() + grid_step.back() < right_border && n < max_steps)
	{
		MethodStep();
		n++;
	}
}

void TestWork::Print()
{
	unsigned long long N = grid.size();
	for ( unsigned int i = 0; i < N; i++ )
	{
		std::cout << "Num: (" << grid[i] << ", " << num_values[i] << ")" << "\tTrue: (" << grid[i] << ", " << true_values[i] << ")"
		<< "\th = " << grid_step[i] << "\tv = " << num_values[i] << "\tvD = " << d_num_values[i]
		<< "\tDiff = " << true_values[i] - final_num_values[i]
		<< std::endl;
	}
	std::cout << "\nmult2 = " << mult2 << ", div2 = " << div2 << std::endl;
}
