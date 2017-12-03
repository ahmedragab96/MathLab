#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
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
 	 this->red = (Hex >> 16 ) ;
	 this->green = (Hex >> 8 & 0xff) ;
	 this->blue =(Hex & 0xff) ;

}

string CColor :: decimal_output ()
{
   stringstream out ;
   out << '(' << this->red << ',' << this->green << ',' << this->blue << ')' ;
   return out.str() ;
}

string CColor :: hexa_output()
{
	stringstream out ;
	out << "0x00" ;
	out << hex << this->red << hex << this->green << hex << this->blue ;
	return out.str() ;
}


ostream& operator << (ostream& out , CColor s )
{

		out << s.decimal_output() ;
		return out ;

}

string CColor :: operator () (string type)
{
	string out ;
	if (type == "hex")
		out = this->hexa_output() ;
	return out ;
}
CColor average (CColor a , CColor b , CColor c)
{
	CColor x ;
	x.red = (a.red + b.red + c.red) / 3 ;
	x.green = (a.green + b.green + c.green) / 3 ;
	x.blue = (a.blue + b.blue + c.blue) / 3 ;
		return x ;
}
