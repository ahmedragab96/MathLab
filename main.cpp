#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include "CColor.h"
using namespace std ;

int main () {


	CColor a(255,128,192);
	CColor b(0x00667755) ;
	cout << "Color a = " << a << endl;
	cout << "Color b = " << b("hex") << endl;
	CColor c(0x00552211);
	CColor y = average(a,b,c);
	cout << "Color y = " << y << endl;
	return 0 ;
}
