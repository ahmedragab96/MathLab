#include <iostream>
#include <string>
#include <sstream>
#include "CColor.h"
using namespace std ;

CColor :: CColor()
{

	red = 0 ;
	green = 0 ;
	blue = 0 ;

}

CColor :: CColor(int R , int G , int B)
{
	red = R ;
	green = G ;
	blue = B ;
}

CColor :: CColor (int Hex)
{
	cout << Hex << endl;
}

string CColor :: output ()
{
   stringstream out ;
   out << '(' << this->red << ',' << this->green << ',' << this->blue << ')' ;
   cout << out.str() << endl;
   out.clear();
}


ostream& operator << (ostream& out , CColor s )
{

		out << s.output() ;
		return out ;

}