#ifndef MATRIX_H 
#define MATRIX_H

#include <iostream>
#include <string>
#include <cstdio>
#include "stdarg.h"
#include <math.h>
#include <cstring>
using namespace std;
class CMatrix {
  int rowsNumbers;
  int coloumnsNumbers ;
  char matrixName [128];
  //double** matrix ;
public:
	double** matrix ;
	enum MI {zeros,ones,value};
	CMatrix();
	CMatrix(const char* name,int rn , int cn , int initial , double initialvalue);
	CMatrix (string s);
	CMatrix (CMatrix& m);
	~CMatrix();

	void setName(string name);
	string getName();
	string getstring ();

	/*CMatrix Transpose();
	double Determinant();
	CMatrix COFactor();
	CMatrix& Inverse();*/
	
	friend ostream& operator << (ostream& out , CMatrix& m);
	friend istream& operator >> (istream & in , CMatrix& m);
	friend void readfile (const char* m);
	
	
	CMatrix& operator =(const CMatrix &other);    
	CMatrix& operator* (CMatrix &x);
	CMatrix& operator - (CMatrix& m);
    CMatrix& operator + (CMatrix& m);
	CMatrix& operator / (CMatrix& const m);
	CMatrix& operator*(double d);
	CMatrix& getTranspose();
	double getDeterminant();
	CMatrix& getinverse();

	/**************************************************/
};

#endif