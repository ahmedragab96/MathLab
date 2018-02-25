#include <iostream>
#include <string>
#include <sstream>
using namespace std;
class CColor {

	int red ; 
	int green ;
	int blue ;
public:
	CColor();
	CColor(int R , int G , int B);
	CColor(int Hex) ;
	CColor average (CColor a , CColor b , CColor c);
	string output ();
	friend ostream& operator <<  (ostream& out , CColor s);
};