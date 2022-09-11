#include <iostream>
#include "TestWork.h"
using namespace std;

int main()
{
	TestWork A(1.0, 3.0, 1.0, 0.01);
	A.Run();
	A.Print();


	return 0;
}