//	Algo.cpp
//	Version : 0.1.1
//	Date : Fri Jul 31 21:28:30 2020
//	Last revise : Thu Sep 17 21:13:30 2020
//	Symbol-Constraint :
//			_Xx..._ - Function Symbol
//			Xx...|x|X - Variable Symbol
//	Description :
//		Function procedure definition.
//
//	Functions :
//		char *_Encode_(const char *Buff,unsigned short int Len);
//		char *_Decode_(const char *Buff,unsigned short int Len);
//
//	Header :
//		"Algo.h"
//
//	Fix : 
//		1> Algothrim adding base64 coding.

#include"Algo.h"

namespace cryptor {

  using namespace base64;

  #define TEMPBUFFER_SIZE 1024
  static char base64_buffer[TEMPBUFFER_SIZE];


  Cryptor::_scale=SCALE_VALUE;

  Cryptor::Cryptor(){

    _list_length = HASHLISTLENGTH;
    _division = _list_length;
    _resort_distance = 4;	// If didnt give this value,default will be 4.

    _hashlist_of_p2c = _hashlist_of_k2c = NULL;

  }

  Cryptor::Cryptor(unsigned int sort_distance){

    _list_length = HASHLISTLENGTH;
    _division = _list_length;
    _resort_distance = sort_distance;

    _hashlist_of_p2c = _hashlist_of_k2c = NULL;

  }

  Cryptor::~Cryptor() {

    delete[] _hashlist_of_p2c,_hashlist_of_p2c = NULL;
    delete[] _hashlist_of_k2c,_hashlist_of_k2c = NULL;

  }

  Cryptor::Cryptor(const Cryptor & cryptor){

    _list_length = cryptor._list_length;
    _division = cryptor._division;
    _resort_distance = cryptor._resort_distance;

    _hashlist_of_p2c=new char[_list_length];
    _hashlist_of_k2c=new char[_list_length];

    if (_hashlist_of_p2c == NULL || _hashlist_of_k2c == NULL)
      exit(EMEMAPPLY);
    else {

      strncpy(_hashlist_of_p2c,cryptor._hashlist_of_p2c,_list_length);
      strncpy(_hashlist_of_k2c,cryptor._hashlist_of_k2c,_list_length);

    }

  }

  int Cryptor::init_Cryptor(void){

    if (_hashlist_of_p2c == NULL)
      _hashlist_of_p2c = new char[_list_length];
    
    if (_hashlist_of_k2c == NULL)
      _hashlist_of_k2c = new char[_list_length];

    // copy context of hashlist into class memory.
    if (strncpy(_hashlist_of_p2c,HASHP2C,HASHLISTLENGTH) == NULL || strncpy(_hashlist_of_p2c,HASHK2C,HASHLISTLENGTH) == NULL)
      return 0;

    sort_hashlist();	// resort elements into hashlist.

    return 1;
  }

  inline template<TYPE>
  TYPE Cryptor::scale(TYPE x){
    return (TYPE)(x * _scale);
  }

  // sort_hashlist() just exchanges two elements both at the position is not same as each.
  // If exceed memory size limit,just does nothing.
  void Cryptor::sort_hashlist(void){

    unsigned short int index(0);
    char i='\0';

    for (index = 0; index < _list_length; ++index) {
      i = _hashlist_of_p2c[index];
      _hashlist_of_p2c[index] = _hashlist_of_p2c[index + _resort_distance];
      _hashlist_of_p2c[index + _resort_distance] = i;
    }

    for (index = 0; index < _list_length; ++index) {
      i = _hashlist_of_k2c[index];
      _hashlist_of_k2c[index] = _hashlist_of_k2c[index + _resort_distance];
      _hashlist_of_k2c[index + _resort_distance] = i;
    }

  }

  char *Cryptor::encode(const char *input_buffer,size_t input_len,
			char *output_buffer,size_t output_len)
  {

  }

  char *Cryptor::decode(const char *input_buffer,size_t len,
			char *output_buffer,size_t output_len)
  {


  }



}


char *encode(const char *Buff,unsigned short int Len)
{


	char Quotient('\0');	// Quotient.
	char Remainder('\0');	// Remainder.

	char *TempSpace=new char[Len*4];	// This will use to copy by class.
						/*
 						 * This will invoke 'new' method with twoce,the first address will be pointed by Buff.
 						 * The second address will be pointed by TempSpace;
 						 */
 
	char *TIndex((char *)0);	// Cycle index.

	if (! TempSpace)	// Checking.
	{
		// Failed to apply memory.

		delete[] TempSpace;
		TempSpace=(char *)0;

		return (char *)0;		// Failed.

	}
	else if (! Buff)
		return TempSpace;	// Input buffer.
	else;

	
	// Up to here,had some memories for two of array.

	//	Env
	
	TIndex=TempSpace;	// Assignment.

	for (unsigned short int IndexP(0); IndexP < Len; ++IndexP)
	{
		Quotient=Buff[IndexP]/Convertion;	// Calculate Quotient.
		Remainder=Buff[IndexP]-(Quotient*Convertion); // Calculate Remainder.

		*TIndex++=Mapping_P2C[Remainder];	// Mapping. P2C.
		*TIndex++=Mapping_K2C[Quotient];	// Mapping. K2C.

	}

	*TIndex='\0';	// Set end.

	/* Do base64 */
	
	if (_Base64_Encode_(TempSpace,CodeBuff,MAXLEN) != NULL)
	{
		/* Clear */
		memset(TempSpace,'\0',Len*4);
		/* Do copy */
		strncpy(TempSpace,CodeBuff,strlen(CodeBuff));
	}
	else
	{
		/* Failed in base64 */
		delete[] TempSpace;
		TempSpace=NULL;
	}


	//	Primary

	delete[] Buff;

	return TempSpace;	// Finished convert.
				// This pointer will recycle in Class.

	//	Return
}

char *decode(const char *Buff,unsigned short int Len)
{

	char Quotient('\0');	// Quotient.
	char Remainder('\0');	// Remainder.

	char *TempSpace=new char[Len*4];	// This will use to copy by class.
						/*
 						 * This will invoke 'new' method with twoce,the first address will be pointed by Buff.
 						 * The second address will be pointed by TempSpace;
 						 */

	unsigned short int IndexC(0);	// For Buff;
	unsigned short int IndexT(0);	// For TempSpace;


	if (! TempSpace)	// Checking.
	{
		// Failed to apply memory.

		delete[] TempSpace;
		TempSpace=(char *)0;

		return (char *)0;		// Failed.

	}
	else if (! Buff)
		return TempSpace;	// Input buffer.
	else;
	
	// Up to here,had some memories for two of array.


	//	Env

	/* Before decode,must do decode for base64 */
	
	if (_Base64_Decode_(Buff,CodeBuff,MAXLEN) == NULL)
	{
		/* Failed in decode base64 */
		delete[] Buff;
		delete[] TempSpace;
		return NULL;
	}
	else
		Len=strlen(CodeBuff);	// Get plaintext.
	
	

	{
		unsigned short int SearchC(0),SearchK(0);

		for (IndexC=0; IndexC < Len; IndexC+=2,++IndexT,SearchC=SearchK=0)
		{
			while (CodeBuff[IndexC] != Mapping_P2C[SearchC])
				++SearchC;	// Search remainder.

			while (CodeBuff[IndexC+1] != Mapping_K2C[SearchK])
				++SearchK;	// Search quotient.
	
			/*	Assignment.	*/
	
			Quotient=(char)SearchK;
			Remainder=(char)SearchC;
	
			TempSpace[IndexT]=(Quotient*Convertion)+Remainder;	// Restore.
		}
	
	}

	TempSpace[IndexT]='\0';	// Set end.


	//	Primary

	delete[] Buff;	// Recycle resource.

	return TempSpace;	// Finished convert.
				// This pointer will recycle in Class.

	//	Return
}

