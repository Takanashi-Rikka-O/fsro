//	CODE.cpp
//	Version : 0.1.1
//	Date : Thu Sep 17 20:15:50 2020
//	Last revise : Tue Jul 28 20:26:50 2020
//	Symbol-Constraint :
//			_Xx..._ - Function Symbol
//			Xx...|x|X - Variable Symbol
//	Description :
//		Class interface definitions.
//
//	Functions :
//		Class methods in *.h file.
//
//	Header :
//		"CODE.h"
//
//	Fix : 
//		1> Delete variables they are useless.

#include"CODE.h"

namespace CODE{

	/*	Public zone.	*/

	_CODE_::_CODE_():InputBuff(NULL),OutputBuff(NULL)
	{
		/* The Which_Method,
		 * true->encode ; false->decode ;
		 */

		//	Env
	
		_CODE_Init_state=true;	// Suppose it successful.

		InputBuff=new char[MAX_LENGTH];	// Get memory.	
		OutputBuff=new char[MAX_LENGTH]; // Get memory. 

		if (! InputBuff || ! OutputBuff)	// Checking.
			_CODE_Init_state=false;
		else;
		
		//	Primary


		//	Return
	}

	_CODE_::~_CODE_()
	{
		
		//	Env

		/*	Delete NULL pointer is secury.	*/
	
		delete[] InputBuff;
		delete[] OutputBuff;

		InputBuff=OutputBuff=NULL;
		
		//	Primary	
		
		//	Return
	}

	bool _CODE_::_GET_INPUT_(void)
	{
		//	Env

		cout<<"Please text > ";	// Hint.
		cin.getline(InputBuff,MAX_LENGTH);	// Get input.
		Input_Len=strlen(InputBuff);	// Length.		

		//	Primary


		return (cin.bad())?false:true;
		//	Return
	}


	bool _CODE_::_CODING_(char *(*CallBack)(const char *Buff,unsigned short int Len))
	{
		char *TempSpace(NULL);	
		
		//	Env
		
		TempSpace=CallBack(NULL,Input_Len);	// First invoke.
		if (TempSpace)
			strncpy(TempSpace,InputBuff,Input_Len);	// Move data.
		else
		{
			cerr<<"Got a NULL.\n";	//Error.
			return false;	
		}

		TempSpace=CallBack(TempSpace,Input_Len); // Second invoke.
		if (TempSpace)
		{
			strncpy(OutputBuff,TempSpace,strlen(TempSpace));	// Copy.
			delete[] TempSpace;	// Recycle.
			return true;		// Result view.
		}
		else
		{
			cerr<<"Got a NULL.\n";	// Error.
			return false;
		}
		
		//	Primary

		//	Return
	}


	void _CODE_::_PRIMARY_DRIVE_(char *(*CallBack)(const char *,unsigned short int))
	{

		//	Env

		if (_CODE_Init_state)
		{
			/*	Set zero for buffer.	*/

			memset(InputBuff,'\0',MAX_LENGTH);
			memset(OutputBuff,'\0',MAX_LENGTH);


			cout<<"Started up CODE tool..."<<endl;
		}
		else
		{
			cerr<<"Failed to start CODE tool!"<<endl;
			return;
		}
		
		/*	Get input.	*/
		if (_GET_INPUT_())
			cout<<"Succeed to got input!"<<endl;
		else
		{
			cerr<<"Failed to got input!"<<endl;
			return;
		}

		/*	Coding.	*/
		if (_CODING_(CallBack))
			cout<<"< "<<OutputBuff<<" >"<<endl;
		else
		{
			cerr<<"\n< Failed to convert!! >\n\n";
		}

		//	Primary


		return;
		//	Return
	}

}	// end of CODE.

