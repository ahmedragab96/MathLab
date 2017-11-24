#include <iostream>
#include <string>
#include <cstdio>
#include "stdarg.h"
#include <math.h>
#include <cstring>
#include <fstream>
#include <stdlib.h>

using namespace std ;
 class CMatrix {
  int rowsNumbers;
  int coloumnsNumbers ;
  char matrixName [128];
  double** matrix ;
public:
	//double** matrix ;
	enum MI {zeros,ones,value};
	CMatrix();
	CMatrix&  Transpose();
	string getstring ();
	string getName();
	CMatrix COFactor();
	CMatrix& Inverse();
	CMatrix(const char* name,int rn , int cn , int initial , double initialvalue);
	CMatrix (string s);
	CMatrix (const CMatrix& m);
	~CMatrix();
	CMatrix& operator =(const CMatrix &other);
	double Determinant();
	friend ostream& operator << (ostream& out , CMatrix& m);
 };
 CMatrix& CMatrix:: operator = (const CMatrix &m)
 {
	//strcpy(matrixName,m.matrixName);
	
	this->coloumnsNumbers = m.coloumnsNumbers;
	this->rowsNumbers = m.rowsNumbers ;
	matrix = new double*[rowsNumbers] ;
	for (int i = 0 ; i < this->rowsNumbers ; i++)
	{    
		matrix[i] = new double[this->coloumnsNumbers];
		for(int j=0;j < this->coloumnsNumbers;j++)
		{
			this->matrix[i][j]=m.matrix[i][j] ;
		}
	}
	return *this;
}
 string CMatrix:: getName()
 {
	string s = "";
	for (int i = 0; i <128;i++)
	{
			if(matrixName[i] == NULL) break;
			else s += matrixName[i];
	}
	return s;
 }
 
 double CMatrix:: Determinant()
{   int counter = 1;
    CMatrix r = *this ;
	for (int i=0;i<r.rowsNumbers;i++)                    //Pivotisation
		for (int k=i+1;k<r.coloumnsNumbers;k++)
            if (abs(r.matrix[i][i])<abs(r.matrix[k][i]))
			{   counter *= -1 ;
				for (int j=0;j<=r.rowsNumbers;j++)
                {
                    double temp=r.matrix[i][j];
                    r.matrix[i][j]=r.matrix[k][j];
                    r.matrix[k][j]=temp;
				}
			}
	//cout << *this << endl;
				for (int i=0 ; i<(r.coloumnsNumbers)-1 ; i++) 
				{   
					int zero_counter = 0 ;
					for (int l = 0 ; l < r.rowsNumbers ; l++)
							if (r.matrix[l][l] == 0) zero_counter++ ;
					if (zero_counter > 1) return 0 ;
						//loop to perform the gauss elimination
					for (int k=i+1 ; k < r.coloumnsNumbers ; k++)
                {
                double t = r.matrix[k][i] / r.matrix[i][i];
				for (int j=0 ; j < r.coloumnsNumbers  ; j++)
                    r.matrix[k][j] = r.matrix[k][j]- t*r.matrix[i][j];    //make the elements below the pivot elements equal to zero or elimnate the variables
					}}
double deter = 1 ;
for (int i = 0 ; i < rowsNumbers ; i++)
		deter *= r.matrix[i][i];

return deter*counter ;



	/*int diagrowindex=0;
	int counter=0;
	
    for(int diagcoloumnindex=0;diagcoloumnindex<this->coloumnsNumbers;diagcoloumnindex++)
	{
		int maxindex=0;
		double max=0;
		for(int rowsindex=diagrowindex+1;rowsindex<rowsNumbers;rowsindex++)
		{
			max=this->matrix[diagrowindex][diagcoloumnindex];
			if(abs(this->matrix[rowsindex][diagcoloumnindex]>max))
			{
				max=this->matrix[rowsindex][diagcoloumnindex];
				counter++;
				maxindex=rowsindex;
			}
			
		}
		swap(this->matrix[diagcoloumnindex][diagrowindex],max);
		for(int i=0;i<rowsNumbers;i++)
		{
			for(int j=0;j<coloumnsNumbers;j++)
			{
				if(j== diagcoloumnindex)
					continue;
				swap(this->matrix[diagrowindex][diagcoloumnindex],this->matrix[i][j]);
			}
		}
	diagrowindex++;
	
	}
 
return *this;*/

}
 string CMatrix :: getstring (){
	string s = this->getName();
	s+=" = [";
	for (int i = 0; i < rowsNumbers ; i++)
	{
		for(int j = 0; j < coloumnsNumbers ; j++)
		{
			char buffer [1000] ;
			sprintf(buffer,"%g",matrix[i][j]);
			s+=buffer;
			if (j != coloumnsNumbers-1) 
				s+=" ";
		}
		if (i!=rowsNumbers-1)
			s+=" \n     ";
	}
	s+="]";

return s ;
} 
 ostream& operator << (ostream& out , CMatrix& m){
 
	 out << m.getstring();
 return out ;
 
 }
 CMatrix :: CMatrix ()
{
	rowsNumbers = 0 ;
	coloumnsNumbers=0;
	matrix=NULL;
}
// (zero,unit and any initial value) matrix constructor
CMatrix :: CMatrix (const char* name,int rn , int cn , int initial , double initialvalue ) 
{
	strcpy(matrixName,name);
	this->rowsNumbers = rn ;
	this->coloumnsNumbers = cn ;
	if (rn*cn == 0){ matrix = NULL ;return;}
	matrix = new double* [rn];
	for(int i=0;i<rn;i++)
	{
		matrix[i]=new double[cn];
		for(int j=0;j<cn;j++)
		{
			switch (initial)
			{
				case zeros : 
				{
					matrix[i][j]=0;
					break;
				}
				case ones :
				{
					matrix[i][j]=1;
					break;
				}
				case value :
				{
					matrix[i][j] = initialvalue ; 
					break;
				}
			}
		}
	}
}

            ////string constructor  ----------------->
CMatrix :: CMatrix (string inputLine)
{
	int rows = 0, cols = 0;
	for(int i = 0,l =inputLine.length(); i < l ; i++)
	{
	   if (inputLine[i] == ';')
	       rows++;
	}
	rowsNumbers = rows;
	matrix = new double* [rowsNumbers];
	string x = inputLine.substr(inputLine.find("[")+1,inputLine.find(";")-inputLine.find("[")-1);
	char* seps_c = " ,;=[]";
	char* context_c = NULL;
    char* token_c = NULL;
	char* rowString = new char [x.length()+1];;
	strcpy(rowString,x.c_str());
	token_c = strtok(rowString , seps_c);
	while(token_c)
	{
		 cols++;
		token_c = strtok(NULL , seps_c);
	}
	coloumnsNumbers = cols;
    char* stringToBeSplitted = new char [inputLine.length()+1];
	strcpy(stringToBeSplitted,inputLine.c_str());
	char* seps = " ,;=[]";
	char* context = NULL;
    char* token = NULL;
	token = strtok(stringToBeSplitted , seps);
	strcpy(matrixName,token);
	token = strtok(NULL,seps);
	for (int i =0;i< rowsNumbers;i++)
	{
		matrix[i] = new double [coloumnsNumbers];
		for (int j=0;j<coloumnsNumbers;j++)
		{
			double item = atof(token);
			matrix[i][j]=item;
			token = strtok(NULL,seps);
		}
	}
}
       // copy constructor 
CMatrix :: CMatrix (const CMatrix& m)
{
	//strcpy(matrixName,m.matrixName);
	
	this->coloumnsNumbers = m.coloumnsNumbers;
	this->rowsNumbers = m.rowsNumbers ;
	matrix = new double*[rowsNumbers] ;
	for (int i = 0 ; i < rowsNumbers ; i++)
	{    
		matrix[i] = new double[coloumnsNumbers];
		for(int j=0;j < coloumnsNumbers;j++)
		{
			this->matrix[i][j]=m.matrix[i][j] ;
		}
	}
}
       // Destructor
CMatrix :: ~CMatrix (){

	if (this->matrix != NULL ) 
	{
		for(int i = 0 ; i < rowsNumbers ; i++)
			delete[] matrix[i];
		delete[] matrix ;
	}
}
CMatrix CMatrix:: COFactor()  
{
	CMatrix *cofactor = new CMatrix("COF", rowsNumbers, coloumnsNumbers,1,1);
	if (rowsNumbers != coloumnsNumbers) 
		return *cofactor; 
	if (rowsNumbers < 2)   
		return *cofactor;   
	else if (rowsNumbers == 2)    
	{        
		cofactor->matrix[0][0] = matrix[1][1];   
		cofactor->matrix[0][1] = -matrix[1][0];       
		cofactor->matrix[1][0] = -matrix[0][1];    
		cofactor->matrix[1][1] = matrix[0][0];    
		return *cofactor; 
	}  
	else if (rowsNumbers >= 3)      
	{       
		int DIM = rowsNumbers ;     
		CMatrix ***temp = new CMatrix**[DIM];    
		for (int i = 0; i < DIM; i++)   
			temp[i] = new CMatrix*[DIM];   
		for (int i = 0; i < DIM; i++)     
			for (int j = 0; j < DIM; j++)   
				temp[i][j] = new CMatrix("", DIM - 1, DIM - 1,1,1);      
		for (int k1 = 0; k1 < DIM; k1++)     
		{              
			for (int k2 = 0; k2 < DIM; k2++)        
			{                        

				int i1 = 0;                       
				for (int i = 0; i < DIM; i++)                        
				{     
					int j1 = 0;      
					for (int j = 0; j < DIM; j++)    
					{      
						if (k1 == i || k2 == j)   
							continue; 
						temp[k1][k2]->matrix[i1][j1++]
						= this->matrix[i][j];    
					}         
					if (k1 != i)    
						i1++;       
				}       
			}    
		}   
		bool flagPositive = true;    
		for (int k1 = 0; k1 < DIM; k1++)      
		{         
			flagPositive = ((k1 % 2) == 0);    
			for (int k2 = 0; k2 < DIM; k2++)      
			{                
				if (flagPositive == true)      
				{                 
					cofactor->matrix[k1][k2] = temp[k1][k2]->Determinant();    
					flagPositive = false;    
				}          
				else     
				{     
					cofactor->matrix[k1][k2] = -temp[k1][k2]->Determinant();
					flagPositive = true; 
				}     
			}     
		}  
		for (int i = 0; i < DIM; i++)           
			for (int j = 0; j < DIM; j++)   
				delete temp[i][j];     
		for (int i = 0; i < DIM; i++)  
			delete[] temp[i];   
		delete[] temp;    
	}     
	return *cofactor;
}
 CMatrix& CMatrix:: Inverse()  
 {
	 CMatrix cofactor("COF", rowsNumbers, coloumnsNumbers,1,1);
	CMatrix* inv = new CMatrix("INV", rowsNumbers, coloumnsNumbers,1,1);   
	 if (rowsNumbers != coloumnsNumbers)  
		 return *inv;    
	 // to find out Determinant   
	 double det = this->Determinant();  
	 cofactor = this->COFactor();      
	 // inv = transpose of cofactor / Determinant     
	 for (int i = 0; i < rowsNumbers; i++)      
	 {
		 if(det==0)
		 {
			 throw("Determinant is equal zero division is invalid");
		 }
		 else
		 {
			for (int j = 0; j < coloumnsNumbers; j++)      
			{              
				inv->matrix[j][i] = cofactor.matrix[i][j] / det;   
			}
		 }
	 }
	 return *inv;   
 }   
 CMatrix& CMatrix:: Transpose()
	{   
		CMatrix *r = new CMatrix(this->matrixName,coloumnsNumbers,rowsNumbers,0,0);
		for(int iR=0;iR<rowsNumbers;iR++)
		{
			for(int iC=0;iC<coloumnsNumbers;iC++)
			{
				r->matrix[iC][iR]=matrix[iR][iC];
			}
		}
		return *r;

	}
 
void main (){
	CMatrix A ("B = [1.2 3.4 5.6 7.8 1.0 3.2 2.1 2.3 1.4 2.6 2.7 2.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 3.7 1.2 3.4 5.6 7.8 9.0 1.2 2.1 2.3 2.4 1.6; 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4; 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 7.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 4.1 2.3; 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 1.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1; 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2; 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 17.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0; 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8; 9.0 2.2 2.1 2.3 2.4 1.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 2.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6; 7.4 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4; 5.6 7.8 9.0 2.2 4.4 2.3 2.4 2.6 2.7 1.2 3.4 5.6 2.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2; 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 1.8 9.0 1.2 2.1 2.3 2.4 8.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7; 1.2 3.4 5.6 7.8 9.0 2.2 5.1 4.3 12.4 2.6 2.7 1.2 3.4 5.6 97.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 3.4 2.6; 2.7 1.2 3.4 5.6 7.5 9.0 2.2 2.1 3.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 5.1 2.3 2.4 5.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4; 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 8.2 2.1 2.3; 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 6.6 2.7 1.2 3.4 5.6 2.8 9.0 1.2 2.1; 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 5.1 2.3 2.4 0.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 0.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2; 0.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0; 4.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 5.2 2.1 2.3 2.4 9.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8; 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 5.3 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.3; 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 3.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 3.4 2.6 3.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 8.4 2.6 2.7 1.2 3.4; 5.6 7.8 9.0 2.2 2.1 2.3 3.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 1.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2; 3.4 1.6 7.8 9.0 2.2 3.1 6.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7; 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 4.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 1.6; 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 1.4 2.6 2.7 1.2 3.4 9.6 7.8 9.0 2.2 2.1 2.3 2.4; 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 1.4 2.6 2.7 2.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3; 2.4 2.6 2.7 1.2 3.4 5.6 7.8 1.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 8.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 2.6 7.8 9.0 2.2 2.1; 7.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 3.6 1.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2; 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 7.2 3.4 5.6 7.8 9.0; 2.2 2.1 2.3 2.4 2.6 7.7 9.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.9 2.4 2.6 2.7 1.2 3.4 5.6 7.8; 9.0 2.2 2.1 2.3 2.4 2.6 7.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6; 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4; 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 5.7 9.3 3.4 5.6 3.8 9.0 2.2 5.1 2.3 2.4 2.6 2.7 1.2];");
	cout << A << endl;
	try {
	 cout << A.Determinant() << endl;
	 cout << A.Inverse() << endl;
	    }
	catch (char const* error)
	{
	 cout << error << endl;
	  
	}
	cout << A << endl;
	cout << A.Transpose() << endl;
system("pause");
}