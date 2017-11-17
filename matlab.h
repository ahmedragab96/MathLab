#ifndef MATLAB_H 
#define MATLAB_H
#include <iostream>
#include "Matrix.h"
using namespace std;
class Matlab
{
	CMatrix *matrixx[100];
	int matricesNumber;

public:
	Matlab();
	void loadfile (const char* File);
	void loadconsole ();
	
};

 #endif
