//	main.cpp
//	Version : 0.1
//	Date : Thu Sep 17 21:16:08 2020
//	Last revise : Fri Jul 31 21:44:08 2020
//	Symbol-Constraint :
//			_Xx..._ - Function Symbol
//			Xx...|x|X - Variable Symbol
//	Description :
//		Main thread to process work start up.
//
//	Functions :
//		Algothrim function.Defined in "Algo.h"
//
//	Header :
//		"CODE.H"
//		"Algo.h"
//
//	Fix :


#include"CODE.h"
#include"Algo.h"

using namespace CODE;	// Import named space.

typedef char *(*CallBackFunc)(const char *,unsigned short int);

int main(void)
{

	char Select_Option('\0');	// For user select.
	CallBackFunc Cryption(NULL);	// Function pointer.
	_CODE_ Code_Obj;		// Class object.
	
	if (! Code_Obj._CODE_Init_state)	// testing.
	{
		cerr<<"Failed to start up tool!!"<<endl;
		return 1;
	}
	else
		cout<<"Succeed to start up tool!"<<endl;
	//	Env

	do
	{
		cout<<"Please select method : "<<endl
		<<"('e',encode)"<<endl
		<<"('d',decode)"<<endl
		<<"> ";

		cin>>Select_Option;	// Get input.

		switch (Select_Option)
		{
			case 'e':
				Cryption=_Encode_;
				Select_Option='\0';
				break;

			case 'd':
				Cryption=_Decode_;
				Select_Option='\0';
				break;

			default:
				cerr<<"Input incorrect!"<<endl;
		}


	} while (Select_Option);	// If Select_Option is 0B00000000,then cycle quit.

		
	cin.ignore(255,'\n');	// Drop invalid data.
	Code_Obj._PRIMARY_DRIVE_(Cryption);

	//	Primary


	cout<<"Any key press to quit..."<<endl;	// Hint.

	cin.clear();		// Prevent badbit.
	(void)cin.get();	// Receive input.

	return 0;
	//	Return
}
