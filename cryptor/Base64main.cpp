//	Base64main.cpp
//	Version : 0.1
//	Date : Tue Sep  8 12:54:05 2020
//	Last revise : Tue Sep  8 12:54:05 2020
//	Symbol-Constraint :
//			_Xx..._ - Function Symbol
//			Xx...|x|X - Variable Symbol
//	Description :
//		Test base64 coding.
//
//	Functions :
//
//	Header :
//		"Base64.h"
//
//	Fix : 

#include"Base64.h"

int main(void)
{

	using namespace std;

	char *Input=new char[64];
	char *Output=new char[64];
	char Buff[64];
	

	//	Env

	/* Checking Mem */

	if (Input == NULL)
	{
		cerr<<"Failed to get memory for input."<<endl;
		goto Main_Exit;
	}
	else;

	if (Output == NULL)
	{
		cerr<<"Failed to get memory for output."<<endl;
		goto Main_Exit;
	}
	else;

	do
	{
		cout<<"Input - ";
		cin.getline(Input,64);

		if (_Base64_Encode_(Input,Output,64) != NULL)
			cout<<"CipherText : "<<Output<<endl;
		else
		{
			cerr<<"Failed to encode..."<<endl;
			goto Main_Exit;
		}

		memset(Buff,'\0',64);

		if (_Base64_Decode_(Output,Buff,64) != NULL)
			cout<<"PlainText : "<<Buff<<endl;
		else
		{
			cerr<<"Failed to decode..."<<endl;
			goto Main_Exit;
		}


	} while (1);
	

	//	Primary

	Main_Exit:

		delete[] Input;
		delete[] Output;

		Input=Output=NULL;


	return 0;
	//	Return
}

