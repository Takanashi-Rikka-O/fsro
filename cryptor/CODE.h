//	CODE.h
//	Version : 0.1
//	Date : Mon Jul 27 20:32:19 2020
//	Last revise : Mon Jul 27 20:32:19 2020
//	Symbol-Constraint :
//			_Xx..._ - Function Symbol
//			Xx...|x|X - Variable Symbol
//	Description :
//		This file will define a class which contain encode and decode method,and some data structure.
//	Program use C++ to be made,and use interactive mode to select encode/decode and get input.
//
//		Class encode and decode use call-back function to do works.
//		These call-back function must receive the parameter :
//			L->R
//				char *,			// Target array use '\0' as end.
//				unsigned short int,	// Target array length.
//		They are return a 'char *',this pointer must from command 'new',functions must check it whether is NULL.
//	If this pointer is not a NULL pointer,must be '\0' as end,and it will be recycling by _CODING_.
//		char *(*)(const char *,unsigned short int);	// Prototype.
//		/*
//		 * Verbose: 
//		 *	If send it a NULL pointer,it will only get memory length like (unsigned short int) and return the pointer.
//		 * 	If send it a pointer which is not NULL,then go working.
//		 *	If happend an error in internal for it,will recycle memory automaticly,otherwise recycled by _CODING_.
//		 */
//
//	Functions :
//		Class methods.
//
//	Header :
//		<iostream>
//
//	Fix : 

#ifndef _CODE_H_
#define _CODE_H_

#include<iostream>
#include<cstring>

namespace CODE{

	using namespace std;

	class _CODE_
	{
		private:	// Private members.	
		
			unsigned short int Input_Len; // Input length.
			
			char *InputBuff;	// Input buffer.
			char *OutputBuff;	// Output buffer.

			enum {MAX_LENGTH=1024};	// Max length for array. enumerate type.

		public:		// Public members.

			bool _CODE_Init_state;	// If class succeed to be initialized.	

			_CODE_();
			~_CODE_();

			bool _GET_INPUT_(void);		// Get input plaintext/ciphertext.
			bool _CODING_(char *(*CallBack)(const char *Buff,unsigned short int Len));	// coding.			
			void _PRIMARY_DRIVE_(char *(*CallBack)(const char *,unsigned short int));	// Primary code.
	};


}



#endif
