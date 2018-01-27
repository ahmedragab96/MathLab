#ifndef MATLAB_H
#define MATLAB_H
#include "matrix.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <cctype>

using namespace std;


	//functions for expression
	void shift_array(double a[], int s, int shift_index);
	void shift_array(string a[], int s, int shift_index);
	bool isNumber(string s);
	void Split_Expression(string expression, string operands[], int& n, string operators_e[], int& r, bool matrices_expression);
	//double calculate_rExpression(string operands[], int n, string operators_e[], int r);
	//CMatrix calculate_MExpression(string operands[], int n, string operators_e[], int r);
	//void Extract(string s1, int pos, string& result, int& new_pos);
	//void special_Extract(string s1, int pos, string& result);
	int needExtract(string s);

	//functions for concatenation
	string  getstring_arr(string** arr,int row,int col); 
	string** SetArray( string inputLine,int& rows,int& cols);
	string** CatCol( string** arr1,int arr1R,int arr1C,string**arr2,int arr2R,int arr2C ,int &rows,int& cols);
	string** CatRow( string** arr1,int arr1R,int arr1C,string** arr2,int arr2R,int arr2C ,int& rows,int& cols);
	int needconcat(string s);
	string delete_spaces (string s,int& new_size);
	//string concatenation(string input);
	//string  GetStringByName(string name);


#endif