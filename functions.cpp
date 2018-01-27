
#include "functions.h"
#include "matrix.h"
//#include "Matlab.h"


void shift_array(double a[], int s, int shift_index) // s ==> size of array
{
	for (int i = shift_index; i<s; i++)
		a[i] = a[i + 1];
}

void shift_array(string a[], int s, int shift_index) // s ==> size of array
{
	for (int i = shift_index;i<s;i++)
		a[i] = a[i + 1];
}

bool  isNumber(string s)
{
	bool isNum = 0;
	int c = 0;
	for (int i = 0;i <s.length();i++)
	{
		if (isdigit(s[i]) == 1 || s[i] == '-')
			c++;
	}
	if (c == s.length())
		isNum = 1;
	return isNum;
}

int needExtract(string s)
{
	int n=0;
	for(int i=0;i<s.length();i++)
	{
		if(s[i]=='(')
		n++;
	}
	return n;
}
int needconcat(string s)
{
	int n=0;
	for(int i=0;i<s.length();i++)
	{
		if(s[i]=='[')
		n++;
	}
	return n;
}
//======================================================================================================
void Split_Expression(string expression, string operands[], int& n, string operators_e[],int& r, bool matrices_expression)
{
	string operators = "*-/^%+";
	char* sep = " =+-*/^%;,";
	char* token = NULL;
	n = 0; //operands Index
    r = 0; //operators Index

	if (expression[0] == '-')
		expression[0] = '$';

	for (int i = 1;i < expression.length();i++)
	{
		if (expression[i] == '-')
		{
			for (int j = 0;j < operators.length();j++)
				if (expression[i - 1] == operators[j])
					expression[i] = '$';
		}
	}

	for (int i = 0;i < expression.length();i++)
	{
		if (expression[i] == '.')
		{
			for (int j = 0;j < operators.length();j++)
			{
				if (expression[i + 1] == operators[j])
				{
					expression[i] == ',';
					operators_e[r] = expression[i];
					operators_e[r] += expression[i + 1];
					r++;
					i++;
					break;
				}
			}
		}

		else
		{
			for (int j = 0;j < operators.length();j++)
			{
				if (expression[i] == operators[j])
				{
					operators_e[r] = expression[i];
					r++;
					break;
				}
			}
		}
	}
	// filling the array of operands
	char* LineToBeSplitted = new char[expression.length() + 1];
	strcpy(LineToBeSplitted, expression.c_str());
	token = strtok(LineToBeSplitted, sep);

	bool matrices_expression = 0;
	while (token != NULL)
	{
		if (token[0] == '$')
			token[0] = '-';

		if (isNumber(token) == 0) //Operations on matrices
			matrices_expression = 1;

		operands[n] = token;
		n++;
		token = strtok(NULL, sep);
	}
}



//=================================================== Retun the Matrix in a string form ===================================================
string  getstring_arr(string** arr,int row,int col) 
{
	double** arr1=new double*[row];
	for (int i = 0; i < row; i++)
	{
		arr1[i]=new double [col];
		for (int j = 0; j < col; j++)
		{
			arr1[i][j]=stod(arr[i][j]);	
		}
	}
	string s ;
	s='[';
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			char buffer[1000];
			sprintf(buffer, "%g", arr1[i][j]);
			s += buffer;
			if (j != col - 1)
				s += " ";
		}
		if (i != row - 1)
			s += " ; ";
	}
	s+=']';
	return s;
}


//====================================================== set a string in form of a 2D array ====================================================================/
string**  SetArray( string inputLine,int& rows,int& cols)
{
	if (inputLine[0]!='[')
	{
		 inputLine='['+inputLine+']';
	}
	
	string ss = inputLine.substr(inputLine.find("[")+1, inputLine.find("]") - inputLine.find("[")-1 );
	
	 rows = 1; cols = 0;
	for(int i = 0;i<ss.length();i++)
	{
		if (inputLine[i] == '$')
			rows++;
	}
	string**array= new string*[rows];
	string x = inputLine.substr(inputLine.find("[") + 1, inputLine.find("$") - inputLine.find("[") - 1);
	
	char * sep= " ";
	char* token= NULL;
	char* rowString = new char[x.length() + 1];;
	strcpy(rowString, x.c_str());
	token= strtok(rowString,sep);
	
	while (token!=NULL)
	{
		cols++;
		token = strtok(NULL,sep);
	}

	char* seps = " $";
	char* tokenn = NULL;
	char* T = new char[ss.length()+1]; 
	strcpy(T,ss.c_str());
	tokenn = strtok(T, seps);
	
	for(int i=0;i< rows;i++)
	{
		array[i] = new string[cols];
	}
	for(int i=0;i< rows;i++)
	{
		for (int j=0;j<cols;j++)
		{
			array[i][j] = tokenn;
			tokenn = strtok(NULL, seps);
		}
		
	}
	
	return array;
}
//==================================================== concatenation col==========================================================
string**  CatCol( string** arr1,int arr1R,int arr1C,string**arr2,int arr2R,int arr2C ,int &rows,int& cols)
{ 
	
	 cols=arr1C+arr2C;rows=arr1R;
	if(arr1R==arr2R)
	{
		rows=arr1R;
		string** CatArr=new string*[arr1R];
	    for (int i=0;i<arr1R;i++)
	   {
		CatArr[i]=new string [cols];
	   }
	   for (int i=0;i<arr1R;i++)//filling the big array with first array
	     {
		for(int j=0;j<arr1C;j++)
			CatArr[i][j]=arr1[i][j];

	     }
	for (int i=0;i<arr1R;i++)//filling the big array with second array
	{
		for(int j=arr1C;j<cols;j++)
			CatArr[i][j]=arr2[i][j-arr1C];

	}



	return CatArr;
	
	}
}
//==========================================  concatenation row ================================================================
string**  CatRow( string** arr1,int arr1R,int arr1C,string** arr2,int arr2R,int arr2C ,int& rows,int& cols)
{
	 rows=arr1R+arr2R;
	if(arr1C==arr2C)
	{
		cols=arr1C;
		string** CatArr=new string*[rows];
	    for (int i=0;i<rows;i++)
	   {
		CatArr[i]=new string [arr1C];
	   }
	   for (int i=0;i<arr1R;i++)//filling the big array with first array
	     {
		for(int j=0;j<arr1C;j++)
			CatArr[i][j]=arr1[i][j];

	     }
	for (int i=arr1R;i<rows;i++)//filling the big array with second array
	{
		for(int j=0;j<arr1C;j++)
			CatArr[i][j]=arr2[i-arr1R][j];

	}
	return CatArr;
	}
}

//============================================================ to delete spaces ============================================
string delete_spaces (string s,int& new_size)
{
	  new_size=s.length();
	 for(int i=0;i<new_size;i++)
	 {
		 char* e=NULL;
		 int in=0;
	     if((s.find(' ',i)==i+2&& s.find('\r\n',i-1)==i))
			 {
				 for (int j = i+2; j<new_size; j++)
		          s[j] = s[j + 1];
	              i--; new_size--;
		     }
		 if(s.rfind(' ',i+1)==i&& s.find('\r\n',i)==i+1)
		 {
			 for (int j = i; j<new_size; j++)
		          s[j] = s[j + 1];
	              i-=2; new_size--;
		 }
	 
		 if((s.find(' ',i)==i+1&&( s.find(',',i-1)==i||s.find(';',i-1)==i)))
			 {
				 for (int j = i+1; j<new_size; j++)
		          s[j] = s[j + 1];
	              i--; new_size--;
		     }
		 if(s.rfind(' ',i+1)==i&& (s.find(',',i)==i+1||s.find(';',i)==i+1))
		 {
			 for (int j = i; j<new_size; j++)
		          s[j] = s[j + 1];
	              i-=2; new_size--;
		 }
	 }
	 for(int i=0;i<new_size;i++)
	 {
		  if(s.find(' ',i)==i+1 && s.find(']',i)==i && s.find('[',i)==i+2)
			 {
		          s[i+1] = ',';
		     }

	 }
	 return s;
}




