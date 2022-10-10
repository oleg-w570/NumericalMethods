#include <iostream>
#include "TestWork.h"
#include "MainWork1.h"
#include "MainWork2.h"

using namespace std;

int main()
{
	MainWork1 A(3.0, 1.0, 0.01, 1000);
	//A.Run();
	//A.Print();
	//MainWork2 A(1.0, 1.0, 3.0, 2.0, 2.0, 0.01, 1000);
	A.Run();
	A.Print();


	return 0;
}