#include <iostream>
#include <fstream>
#include "matlab.h"
#include "Matrix.h"
#include <string>
using namespace std;

Matlab:: Matlab()
{
	matricesNumber=0;
}

void Matlab::loadfile(const char* File)
{
	ifstream file(File);
	while(!file.eof())
	{
		string inputLine;
		getline(file,inputLine);
		if(inputLine.find("[")>0 && inputLine.find("[")<inputLine.length())
		{
			matrixx[matricesNumber] = new CMatrix(inputLine);
			cout << matrixx[matricesNumber]->getstring()<<endl;
			matricesNumber++;
		}
		
		else if (inputLine.find("=")>0 && inputLine.find("=")<inputLine.length())
		{
			char* seps = " =;";
			char* context = NULL;
			char* token = NULL;
			char* LineToBeSplitted = new char [inputLine.length()+1];;
			strcpy(LineToBeSplitted,inputLine.c_str());
			token = strtok(LineToBeSplitted , seps);
			int outputIndex; bool flag = false;
			for (int i=0;i<matricesNumber;i++)
			{
				if (token == matrixx[i]->getName())
				{
					outputIndex=i; flag = true;
					break; 
				}
			}
			if (flag == false)
			{
				matrixx[matricesNumber] = new CMatrix(token,1,1,0,0);
				outputIndex = matricesNumber;
				matricesNumber++;
			}
			CMatrix operand1;
			CMatrix result;
			token = strtok(NULL , seps);

			for (int i=0;i<matricesNumber;i++)
			{
				if (token == matrixx[i]->getName())
				{
					result=*matrixx[i];
				
					break; 
				}
			}
			token = strtok(NULL , seps);
			
			while(token)
			{
				
				if(*token == '+')
				{
 					token = strtok(NULL , seps);
			
					
					for (int i=0;i<matricesNumber;i++)
					{	
						
						string ss = matrixx[i]->getName();
						const char * ssp = ss.c_str();
						
						if (*token == *ssp)
						{
							operand1=*matrixx[i];
							break; 
						}
					}
					result = result + operand1;
				}
				else if(*token == '-')
				{
					token = strtok(NULL , seps);
					flag = true;
					for (int i=0;i<matricesNumber;i++)
					{
						string ss = matrixx[i]->getName();
						const char * ssp = ss.c_str();
						if (*token == *ssp)
						{
							operand1=*matrixx[i];
							break; 
						}
					}
					result = result - operand1;
				}
				else if(*token == '*')
				{
					token = strtok(NULL , seps);
					flag = true;
					for (int i=0;i<matricesNumber;i++)
					{
						string ss = matrixx[i]->getName();
						const char * ssp = ss.c_str();
						if (*token == *ssp)
						{
							operand1=*matrixx[i];
							break; 
						}
					}
					result = result * operand1;
				}
				else if(*token == '/')
				{
					token = strtok(NULL , seps);
					flag = true;
					for (int i=0;i<matricesNumber;i++)
					{
						string ss = matrixx[i]->getName();
						const char * ssp = ss.c_str();
						if (*token == *ssp)
						{
							operand1= *matrixx[i];
							break;  
						}
					}
					result = result / operand1;
				}
				token = strtok(NULL , seps);
			}
			*matrixx[outputIndex] = result;
			cout << matrixx[outputIndex]->getstring() << endl;
		}
		/*else
		{
			break;
		}*/
		
		
	}
}
void Matlab::loadconsole()
{
	while(1)	
	{
		string inputLine;
		getline(cin,inputLine);
		if(inputLine.find("[")>0 && inputLine.find("[")<inputLine.length())
		{
			matrixx[matricesNumber] = new CMatrix(inputLine);
			cout << matrixx[matricesNumber]->getstring()<<endl;
			matricesNumber++;
		}

		else if (inputLine.find("=")>0 && inputLine.find("=")<inputLine.length())
		{
			char* seps = " =;";
			char* context = NULL;
			char* token = NULL;
			char* LineToBeSplitted = new char [inputLine.length()+1];;
			strcpy(LineToBeSplitted,inputLine.c_str());
			token = strtok(LineToBeSplitted , seps);
			int outputIndex; bool flag = false;
			for (int i=0;i<matricesNumber;i++)
			{
				if (token == matrixx[i]->getName())
				{
					outputIndex=i; flag = true;
					break; 
				}
			}
			if (flag == false)
			{
				matrixx[matricesNumber] = new CMatrix(token,1,1,0,0);
				outputIndex = matricesNumber;
				matricesNumber++;
			}
			CMatrix operand1;
			CMatrix result;
			token = strtok(NULL , seps);

			for (int i=0;i<matricesNumber;i++)
			{
				if (token == matrixx[i]->getName())
				{
					result=*matrixx[i];
		
					break; 
				}
			}
			token = strtok(NULL , seps);
	
			while(token)
			{
		
				if(*token == '+')
				{
					token = strtok(NULL , seps);
	
			
					for (int i=0;i<matricesNumber;i++)
					{	
				
						string ss = matrixx[i]->getName();
						const char * ssp = ss.c_str();
						if (*token == *ssp)
						{
							operand1=*matrixx[i];
							break; 
						}
					}
					result = result + operand1;
				}
				else if(*token == '-')
				{
					token = strtok(NULL , seps);
					flag = true;
					for (int i=0;i<matricesNumber;i++)
					{
						string ss = matrixx[i]->getName();
						const char * ssp = ss.c_str();
						if (*token == *ssp)
						{
							operand1=*matrixx[i];
							break; 
						}
					}
					result = result - operand1;
				}
				else if(*token == '*')
				{
					token = strtok(NULL , seps);
					flag = true;
					for (int i=0;i<matricesNumber;i++)
					{
						string ss = matrixx[i]->getName();
						const char * ssp = ss.c_str();
						if (*token == *ssp)
						{
							operand1=*matrixx[i];
							break; 
						}
					}
					result = result * operand1;
				}
				else if(*token == '/')
				{
					token = strtok(NULL , seps);
					flag = true;
					for (int i=0;i<matricesNumber;i++)
					{
						string ss = matrixx[i]->getName();
						const char * ssp = ss.c_str();
						if (*token == *ssp)
						{
							operand1= *matrixx[i];
							break;  
						}
					}
					result = result / operand1;
				}
				token = strtok(NULL , seps);
			}
			*matrixx[outputIndex] = result;
			cout << matrixx[outputIndex]->getstring() << endl;
		}
		else if(inputLine == "quit")
		{
			break;
		}

	}
}
/*Matlab:: ~Matlab()
{
	for(int i=0;i<matricesNumber;i++)
		if (matrixx[i] != NULL)
			delete[] matrixx[i];
	
}*/

