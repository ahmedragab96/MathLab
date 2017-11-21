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
	ifstream file(File); int linesNumber = 0;
	while(!file.eof())
	{
		string inputLine;
		getline(file,inputLine);
		linesNumber++;
		if (inputLine[inputLine.length()-1] != ';')
			inputLine += ";";
		//cout << linesNumber << "  "<< inputLine << endl;
		if(inputLine.find("[")>0 && inputLine.find("[")<inputLine.length())
		{
			int equalCounter=0;
			for(int i=0;i<inputLine.length();i++)
			{
				if(inputLine[i]=='=')
					equalCounter++;
			}
		
			if(equalCounter==1)
			{

				char* seps = " =;	";
				char* token = NULL;
				char* LineToBeExecuted = new char [inputLine.length()+1];
				strcpy(LineToBeExecuted,inputLine.c_str());

				token = strtok(LineToBeExecuted , seps);

				bool flag = false;
				for (int i=0;i<matricesNumber;i++)
				{
					if (token == matrixx[i]->getName())
					{
						matrixx[i] = new CMatrix (inputLine);
						cout << *matrixx[i] <<endl;
						flag = true;
						break; 
					}
				}
				if (flag == false)
				{
					matrixx[matricesNumber] = new CMatrix(inputLine);
					matrixx[matricesNumber]->setName(token);
					cout << *matrixx[matricesNumber] <<endl;
					matricesNumber++;	
				}
			}
		
			else if(equalCounter>1)
			{
				string cascadedInput = "C";
				string SS =inputLine.substr(inputLine.find('['),inputLine.find(']')+1);
				cascadedInput += SS ;
				CMatrix keyMatrix(cascadedInput);
				string cleanInput=inputLine.substr(0,inputLine.find('['));

				char* seps = " =;	";
				char* token = NULL;
				char* LineToBeExecuted = new char [cleanInput.length()+1];
				strcpy(LineToBeExecuted,cleanInput.c_str());
			
				token = strtok(LineToBeExecuted , seps);
			
				while(token)
				{
					bool flag = false;
					for (int i=0;i<matricesNumber;i++)
					{
						if (token == matrixx[i]->getName())
						{
							*matrixx[i] = keyMatrix;
							cout  << *matrixx[i] <<endl;
							flag = true;
							break; 
						}
					}
					if (flag == false)
					{
						matrixx[matricesNumber] = new CMatrix;
						*matrixx[matricesNumber] = keyMatrix;
						matrixx[matricesNumber]->setName(token);
						cout << *matrixx[matricesNumber] <<endl;
						matricesNumber++;	
					}
			
					token=strtok(NULL,seps);
				}
			
							
			}
		}
	
		else if (inputLine.find("=")>0 && inputLine.find("=")<inputLine.length())
		{

			bool error =false;
			char* seps = " =;	";
			char* context = NULL;
			char* token = NULL;
			char *LineToBeSplitted = new char [inputLine.length()+1];
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
		
			bool checkTranspose = false;
			for (int i=0; i <128 ; i++)
			{
			
				if (token[i] != NULL)
				{

					if (token[i] == 39)
					{ 
						checkTranspose = true;
						token[i] = NULL;
						break;
					}
				}
				else break;
			}			
			try {
				bool op1found = false;
				for (int i=0;i<matricesNumber;i++)
				{
					if (token == matrixx[i]->getName())
					{
						result=*matrixx[i];
						op1found = true;
						break; 
					}
				}
				if (op1found == false) 
				{
					throw("One or more operands are not definied yet.");
				}
				if(checkTranspose == true)	
				{
					result = result.Transpose();
				}
				token = strtok(NULL , seps);
			}
			catch(char const* Error)
			{
				cout<<"Error: '"<<Error << "' at line "<<linesNumber<<":" << inputLine <<endl;
				error=true;
			}		
			while(token!=NULL && error == false)
			{
		
				try
				{
					//char* op = token;
				
					if(*token == '+')
					{
						token = strtok(NULL , seps);
						bool op2found = false;
						for (int i=0;i<matricesNumber;i++)
						{	
							if (token == matrixx[i]->getName())
							{
				
								operand1=*matrixx[i];
								op2found = true;
								break; 
							}
						}
						if (op2found == false) 
						{
					
							throw("One or more operands are not definied yet.");
						}
				
						result = result + operand1;
				

					}
					else if(*token == '-')
					{
						token = strtok(NULL , seps);
						bool op2found = false;
						for (int i=0;i<matricesNumber;i++)
						{	
							if (token == matrixx[i]->getName())
							{
				
								operand1=*matrixx[i];
								op2found = true;
								break; 
							}
						}
						if (op2found == false) 
						{
					
							throw("One or more operands are not definied yet.");
						}
						result = result - operand1;
					}
					else if(*token == '*')
					{
						token = strtok(NULL , seps);
						bool op2found = false;
						for (int i=0;i<matricesNumber;i++)
						{	
							if (token == matrixx[i]->getName())
							{
				
								operand1=*matrixx[i];
								op2found = true;
								break; 
							}
						}
						if (op2found == false) 
						{
					
							throw("One or more operands are not definied yet.");
						}
						result = result * operand1;
					}
					else if(*token == '.')					//it mentions to './'
					{
						token = strtok(NULL , seps);
						bool op2found = false;
						for (int i=0;i<matricesNumber;i++)
						{	
							if (token == matrixx[i]->getName())
							{
				
								operand1=*matrixx[i];
								op2found = true;
								break; 
							}
						}
						if (op2found == false) 
						{
					
							throw("One or more operands are not definied yet.");
						}
						result =elementDivision(result,operand1);
					}
					else if(*token == '/')
					{
						token = strtok(NULL , seps);
						bool op2found = false;
						for (int i=0;i<matricesNumber;i++)
						{	
							if (token == matrixx[i]->getName())
							{
				
								operand1=*matrixx[i];
								op2found = true;
								break; 
							}
						}
						if (op2found == false) 
						{
					
							throw("One or more operands are not definied yet.");
						}
						result = result / operand1;
					}
				
				
		
				}
				catch(char const* Error)
				{
					cout<<"Error: '"<<Error << "' at line "<<linesNumber<<":" << inputLine <<endl;
					error=true;
				}
				token = strtok(NULL , seps);
			}
				if(error==false)
				{
				

					*matrixx[outputIndex] = result;

					cout << *matrixx[outputIndex]<< endl;
				}

		

		}
	
	}
}

void Matlab::loadconsole()
{
	int linesNumber = 0;
	while(1)
	{
		string inputLine;
		getline(cin,inputLine);
		linesNumber++;
		inputLine[inputLine.length()+2] = ';';
		cout << inputLine << endl;
		if(inputLine.find("[")>0 && inputLine.find("[")<inputLine.length())
		{
			int equalCounter=0;
			for(int i=0;i<inputLine.length();i++)
			{
				if(inputLine[i]=='=')
					equalCounter++;
			}
			
			if(equalCounter==1)
			{

				char* seps = " =;	";
				char* token = NULL;
				char* LineToBeExecuted = new char [inputLine.length()+1];
				strcpy(LineToBeExecuted,inputLine.c_str());

				token = strtok(LineToBeExecuted , seps);

				bool flag = false;
				for (int i=0;i<matricesNumber;i++)
				{
					if (token == matrixx[i]->getName())
					{
						matrixx[i] = new CMatrix (inputLine);
						cout << *matrixx[i] <<endl;
						flag = true;
						break; 
					}
				}
				if (flag == false)
				{
					matrixx[matricesNumber] = new CMatrix(inputLine);
					matrixx[matricesNumber]->setName(token);
					cout << *matrixx[matricesNumber] <<endl;
					matricesNumber++;	
				}
			}
			
			else if(equalCounter>1)
			{
				string cascadedInput = "C";
				string SS =inputLine.substr(inputLine.find('['),inputLine.find(']')+1);
				cascadedInput += SS ;
				CMatrix keyMatrix(cascadedInput);
				string cleanInput=inputLine.substr(0,inputLine.find('['));

				char* seps = " =;	";
				char* token = NULL;
				char* LineToBeExecuted = new char [cleanInput.length()+1];
				strcpy(LineToBeExecuted,cleanInput.c_str());
				
				token = strtok(LineToBeExecuted , seps);
				
				while(token)
				{
					bool flag = false;
					for (int i=0;i<matricesNumber;i++)
					{
						if (token == matrixx[i]->getName())
						{
							*matrixx[i] = keyMatrix;
							cout  << *matrixx[i] <<endl;
							flag = true;
							break; 
						}
					}
					if (flag == false)
					{
						matrixx[matricesNumber] = new CMatrix;
						*matrixx[matricesNumber] = keyMatrix;
						matrixx[matricesNumber]->setName(token);
						cout << *matrixx[matricesNumber] <<endl;
						matricesNumber++;	
					}
				
					token=strtok(NULL,seps);
				}
				
								
			}
		}
		
		else if (inputLine.find("=")>0 && inputLine.find("=")<inputLine.length())
		{

			bool error =false;
			char* seps = " =;	";
			char* context = NULL;
			char* token = NULL;
			char *LineToBeSplitted = new char [inputLine.length()+2];
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
			
			bool checkTranspose = false;
			for (int i=0; i <128 ; i++)
			{
				
				if (token[i] != NULL)
				{

					if (token[i] == 39)
					{ 
						checkTranspose = true;
						token[i] = NULL;
						break;
					}
				}
				else break;
			}			
			try {
				bool op1found = false;
				for (int i=0;i<matricesNumber;i++)
				{
					if (token == matrixx[i]->getName())
					{
						result=*matrixx[i];
						op1found = true;
						break; 
					}
				}
				if (op1found == false) 
				{
					throw("One or more operands are not definied yet.");
				}
				if(checkTranspose == true)	
				{
					result = result.Transpose();
				}
				token = strtok(NULL , seps);
			}
			catch(char const* Error)
			{
				cout<<"Error: '"<<Error << "' at line "<<linesNumber<<":" << inputLine <<endl;
				error=true;
			}		
			while(token!=NULL && error == false)
			{
			
				try
				{
					//char* op = token;
					
					if(*token == '+')
					{
						token = strtok(NULL , seps);
						bool op2found = false;
						for (int i=0;i<matricesNumber;i++)
						{	
							if (token == matrixx[i]->getName())
							{
					
								operand1=*matrixx[i];
								op2found = true;
								break; 
							}
						}
						if (op2found == false) 
						{
						
							throw("One or more operands are not definied yet.");
						}
					
						result = result + operand1;
					

					}
					else if(*token == '-')
					{
						token = strtok(NULL , seps);
						bool op2found = false;
						for (int i=0;i<matricesNumber;i++)
						{	
							if (token == matrixx[i]->getName())
							{
					
								operand1=*matrixx[i];
								op2found = true;
								break; 
							}
						}
						if (op2found == false) 
						{
						
							throw("One or more operands are not definied yet.");
						}
						result = result - operand1;
					}
					else if(*token == '*')
					{
						token = strtok(NULL , seps);
						bool op2found = false;
						for (int i=0;i<matricesNumber;i++)
						{	
							if (token == matrixx[i]->getName())
							{
					
								operand1=*matrixx[i];
								op2found = true;
								break; 
							}
						}
						if (op2found == false) 
						{
						
							throw("One or more operands are not definied yet.");
						}
						result = result * operand1;
					}
					else if(*token == '.')					//it mentions to './'
					{
						token = strtok(NULL , seps);
						bool op2found = false;
						for (int i=0;i<matricesNumber;i++)
						{	
							if (token == matrixx[i]->getName())
							{
					
								operand1=*matrixx[i];
								op2found = true;
								break; 
							}
						}
						if (op2found == false) 
						{
						
							throw("One or more operands are not definied yet.");
						}
						result =elementDivision(result,operand1);
					}
					else if(*token == '/')
					{
						token = strtok(NULL , seps);
						bool op2found = false;
						for (int i=0;i<matricesNumber;i++)
						{	
							if (token == matrixx[i]->getName())
							{
					
								operand1=*matrixx[i];
								op2found = true;
								break; 
							}
						}
						if (op2found == false) 
						{
						
							throw("One or more operands are not definied yet.");
						}
						result = result / operand1;
					}
					
					
			
				}
				catch(char const* Error)
				{
					cout<<"Error: '"<<Error << "' at line "<<linesNumber<<":" << inputLine <<endl;
					error=true;
				}
				token = strtok(NULL , seps);
			}
				if(error==false)
				{
					

					*matrixx[outputIndex] = result;

					cout << *matrixx[outputIndex]<< endl;
				}

			

		}
		
		
	}
}
