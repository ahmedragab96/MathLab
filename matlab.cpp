#include <iostream>
#include <fstream>
#include "matlab.h"
#include "matrix.h"

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
		else if (inputLine == "Exit")
		{
			cout << "That's All for now!byee" << endl;
			break;
		}
		else
		{
			cout << inputLine<<endl;
			char* seps = " =;";
			char* context = NULL;
			char* token = NULL;
			char* LineToBeSplitted = new char [inputLine.length()+1];;
			strcpy(LineToBeSplitted,inputLine.c_str());
			token = strtok_s(LineToBeSplitted , seps, &context);
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
			token = strtok_s(NULL , seps, &context);

			for (int i=0;i<matricesNumber;i++)
			{
				if (token == matrixx[i]->getName())
				{
					result=*matrixx[i];
					break; 
				}
			}
			token = strtok_s(NULL , seps, &context);
			
			while(token)
			{
				
				if(*token == '+')
				{
					token = strtok_s(NULL , seps, &context);
			
					for (int i=0;i<matricesNumber;i++)
					{
						if (token == matrixx[i]->getName())
						{
							operand1=*matrixx[i];
							break; 
						}
					}
					result = result + operand1;
				}
				else if(*token == '-')
				{
					token = strtok_s(NULL , seps, &context);
					flag = true;
					for (int i=0;i<matricesNumber;i++)
					{
						if (token == matrixx[i]->getName())
						{
							operand1=*matrixx[i];
							break; 
						}
					}
					result = result - operand1;
				}
				else if(*token == '*')
				{
					token = strtok_s(NULL , seps, &context);
					flag = true;
					for (int i=0;i<matricesNumber;i++)
					{
						if (token == matrixx[i]->getName())
						{
							operand1=*matrixx[i];
							break; 
						}
					}
					result = result * operand1;
				}
				else if(*token == '/')
				{
					token = strtok_s(NULL , seps, &context);
					flag = true;
					for (int i=0;i<matricesNumber;i++)
					{
						if (token == matrixx[i]->getName())
						{
							operand1=*matrixx[i];
							break;  
						}
					}
					result = result / operand1;
				}
				token = strtok_s(NULL , seps, &context);
			}
			*matrixx[outputIndex] = result;
			cout << matrixx[outputIndex]->getstring() << endl;
		}
		


	}
	

	

}
/*Matlab:: ~Matlab()
{
	for(int i=0;i<matricesNumber;i++)
		if (matrixx[i] != NULL)
			delete[] matrixx[i];
	
}*/

