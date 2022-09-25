#include <iostream>
#include "TestWork.h"
using namespace std;

int main()
{
	TestWork A(3.0, 1.0, 0.01, 1000, true);
	A.Run();
	A.Print();


	return 0;
}