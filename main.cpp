#include <iostream>
#include <string>
#include <cstdio>
#include "stdarg.h"
#include <math.h>
#include "Matrix.h"
#include "matlab.h"
#include <cstring>

using namespace std;


int main (int argc , char* argv[]){
	
	Matlab myMatlab1;
	if(argc > 1)
	{
		myMatlab1.loadfile("D://testmatrix.txt");
	}
	else
	{
		myMatlab1.loadfile("D://testmatrix.txt");
	}
	system("pause");
	return 0;
}

