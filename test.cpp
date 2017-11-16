#include <iostream>
#include <string>
#include <cstdio>
#include "stdarg.h"
#include <math.h>
#include "matrix.h"
#include "matlab.h"
#include <cstring>


using namespace std;


int main (int argc , char* argv[]){
	
	Matlab myMatLab1;
//  readfile("G:\\test.txt");
	/*if(argc > 1)
	{*/
		myMatLab1.loadfile("D://testmatrix.txt");
	/*}
	else
	{
	
	cout << "read from console" << endl;
	}*/
	system("pause");
	return 0;
}