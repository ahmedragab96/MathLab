#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
using namespace std;
class CColor {

	int red ; 
	int green ;
	int blue ;
public:
	CColor();
	CColor(int R , int G , int B);
	CColor(int Hex) ;
	friend CColor average (CColor a , CColor b , CColor c);
	string decimal_output ();
	string hexa_output();
	string operator () (string type);
	friend ostream& operator <<  (ostream& out , CColor s);

};
