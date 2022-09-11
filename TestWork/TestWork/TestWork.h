#pragma once
#include <vector>
#include <iostream>
#define EPS 1e-8

class TestWork
{
	std::vector<double> grid;
	std::vector<double> grid_step;
	std::vector<double> true_values;
	std::vector<double> num_values;
	std::vector<double> d_num_values;
	double b;
	int mult2;
	int div2;
public:
	TestWork(double a = 0.0, double b = 1.0, double u0 = 1.0, double h0 = 0.01);
	double Func(double u);
	double TrueFunc(double x);
	double NumFunc(double v, double h);
	double DNumFunc(double v, double h);
	void MethodStep();
	void Run();
	void Print();
};

