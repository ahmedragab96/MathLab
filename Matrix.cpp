#include <iostream>
#include <string>
#include <cstdio>
#include "stdarg.h"
#include <math.h>
#include <cstring>
#include <fstream>
#include <stdlib.h>
#include "Matrix.h"
using namespace std;
          // Default Constructor
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
CMatrix :: CMatrix (CMatrix& m)
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
         // Retun the Matrix in a string form
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
			s+=" ; ";
	}
	s+="]";

return s ;
} 
      //Multiplacation
CMatrix& CMatrix :: operator* (CMatrix &x)
{
	if(this->coloumnsNumbers==x.rowsNumbers )
	{
	CMatrix *rere = new CMatrix (this->matrixName,rowsNumbers,x.coloumnsNumbers,0,0);

		for (int rows=0;rows<rowsNumbers;rows++)
			{
				for (int cols=0;cols<x.coloumnsNumbers;cols++)
					{
						double sum=0;
						for (int i=0;i<coloumnsNumbers;i++)
							{
								sum+= this->matrix[rows][i]*x.matrix[i][cols];
							}
						rere->matrix[rows][cols]=sum;
					}
			}
		return *rere;
	}
	else
	{
		throw("Cannot Multiply Matrices: 1st cols != 2nd rows");

	}
}
          // Minus operator
CMatrix& CMatrix::operator - (CMatrix& m)
	{	
      if(rowsNumbers!=m.rowsNumbers||coloumnsNumbers!=m.coloumnsNumbers)
	  {
			throw("Substraction must be among matrices of same order");

	  }
	else { CMatrix *r = new CMatrix (this->matrixName,rowsNumbers,coloumnsNumbers,0,0);
        for(int iR=0;iR<rowsNumbers;iR++)
            for(int iC=0;iC<coloumnsNumbers;iC++)
              {
                r->matrix[iR][iC] = this->matrix[iR][iC]- m.matrix[iR][iC];
              }
	return *r; 
	}
	//r=*this;
	}
        // plus operator
CMatrix& CMatrix::operator +(CMatrix& m)
	{	
      if(rowsNumbers!=m.rowsNumbers||coloumnsNumbers!=m.coloumnsNumbers)
	  {
			throw("Addiion must be among matrices of same order");
	  }
         else {CMatrix *r = new CMatrix(this->matrixName,this->rowsNumbers,this->coloumnsNumbers,0,0);
        for(int iR=0;iR<rowsNumbers;iR++)
		{
			for(int iC=0;iC<coloumnsNumbers;iC++)
              {
                r->matrix[iR][iC] = this->matrix[iR][iC]+ m.matrix[iR][iC];
              }
		}
	return *r;}
	//r=*this;
	}
        //Transpose function
CMatrix CMatrix:: Transpose()
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

ostream& operator << (ostream& out , CMatrix& m){
 
	 out << m.getstring();
 return out ;
 
 }

double CMatrix:: Determinant()
{
	double det = 0;
	double **pd = matrix;
	switch (rowsNumbers)            
	{                
	case 2:                
		{                    
			det = pd[0][0] * pd[1][1] - pd[0][1] * pd[1][0];
			return det;
		}                    
		break;
	case 3:
		{                    
			double a = pd[0][0];
			double b = pd[0][1];
			double c = pd[0][2];
			double d = pd[1][0];
			double e = pd[1][1];
			double f = pd[1][2];
			double g = pd[2][0];
			double h = pd[2][1];
			double i = pd[2][2];
			double det = (a * e * i + b * f * g + c * d * h);
			det = det - a * f * h;
			det = det - b * d * i;
			det = det - c * e * g;
			return det;
		}
		break;
	case 4:
		{
			CMatrix *temp[4];
			for (int i = 0; i < 4; i++)
				temp[i] = new CMatrix("", 3, 3,1,1);
			for (int k = 0; k < 4; k++)                
			{            
				for (int i = 1; i < 4; i++)    
				{           
					int j1 = 0;     
					for (int j = 0; j < 4; j++)    
					{                
						if (k == j)    
							continue; 
						temp[k]->matrix[i - 1][j1++] = this->matrix[i][j];   
					}
				}
			}
			double det = this->matrix[0][0] * temp[0]->Determinant() - this->matrix[0][1] * temp[1]->Determinant() + this->matrix[0][2] * temp[2]->Determinant() - this->matrix[0][3] * temp[3]->Determinant();
			return det;
		}
		break;                
	case 5:                
		{                    
			CMatrix *temp[5];                    
			for (int i = 0; i < 5; i++)                        
				temp[i] = new CMatrix("", 4, 4,1,1); 
			for (int k = 0; k < 5; k++)
			{    
				for (int i = 1; i < 5; i++)   
				{             
					int j1 = 0;    
					for (int j = 0; j < 5; j++)     
					{           
						if (k == j)     
							continue;   
						temp[k]->matrix[i - 1][j1++] = this->matrix[i][j];                            
					}
				}
			}
			double det = this->matrix[0][0] * temp[0]->Determinant() - this->matrix[0][1] * temp[1]->Determinant() + this->matrix[0][2] * temp[2]->Determinant() - this->matrix[0][3] * temp[3]->Determinant() + this->matrix[0][4] * temp[4]->Determinant();
			return det;
		}
	case 6:                
	case 7:                
	case 8:                
	case 9:                
	case 10:                
	case 11:                
	case 12:                
	default:                
		{                    
			int DIM = rowsNumbers;                    
			CMatrix **temp = new CMatrix*[DIM];                   
			for (int i = 0; i < DIM; i++)                        
				temp[i] = new CMatrix("", DIM - 1, DIM - 1,1,1);
			for (int k = 0; k < DIM; k++)    
			{       
				for (int i = 1; i < DIM; i++)       
				{       
					int j1 = 0;    
					for (int j = 0; j < DIM; j++)    
					{       
						if (k == j)     
							continue;  
						temp[k]->matrix[i - 1][j1++] = this->matrix[i][j];
					}
				}
			}
			double det = 0;
			for (int k = 0; k < DIM; k++)        
			{     
				if ((k % 2) == 0)    
					det = det + (this->matrix[0][k] * temp[k]->Determinant());
				else
					det = det - (this->matrix[0][k] * temp[k]->Determinant());
			}
			for (int i = 0; i < DIM; i++)     
				delete temp[i];      
			delete[] temp;    
			return det;   
		}
		break;
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
	 if (rowsNumbers!= coloumnsNumbers)  
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
 
 void CMatrix:: setName(string name)
 {
	 strcpy(matrixName,name.c_str());
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
CMatrix& CMatrix:: operator / ( CMatrix& m)
{
	CMatrix* r = new CMatrix("",this->rowsNumbers,m.coloumnsNumbers,0,0);
	if ((m.rowsNumbers == m.coloumnsNumbers) )
	{
		*r = *this * m.Inverse();
		return *r;
	}
	else throw("Invalid matrix dimension please fix it");
}
 CMatrix& elementDivision(CMatrix &m,CMatrix &c)
{
	
	if(m.rowsNumbers!=c.rowsNumbers||m.coloumnsNumbers!=c.coloumnsNumbers)
	{
		
		throw("Invalid matrix dimension please fix it");
		
	}
	else
	{
		CMatrix *r=new CMatrix("",m.rowsNumbers,m.coloumnsNumbers,0,0);
		
		for(int ir=0;ir<m.rowsNumbers;ir++)
		{
			for(int ic=0;ic<m.coloumnsNumbers;ic++)
			{
			r->matrix[ir][ic]=m.matrix[ir][ic]/c.matrix[ir][ic];

			}
		}
	return *r;
	}
	
}
