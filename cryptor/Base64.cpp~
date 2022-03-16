//	Base64.cpp
//	Version : 0.2
//	Date : Sun Sep  6 20:19:23 2020
//	Last revise : Wed Sep  16 21:24:00 2020
//	Symbol-Constraint :
//			_Xx..._ - Function Symbol
//			Xx...|x|X - Variable Symbol
//	Description :
//		Code/Decode feature functions of base64.
//
//	Functions :
//		char *_Base64_Encode_(const char *PlainText,char *Buff,const short int Len_Buff);
//		char *_Base64_Decode_(const char *CipherText,char *Buff,const short int Len_Buff);
//
//	Header :
//		"Base64.h"
//
//	Fix : 
//		1> Rewrite - Rewrite
//		2> Now _Base64_Encode_ function had have normally working.
//		3> Contains into a named space.

#include"Base64.h"

namespace BASE64{

/* Data structures */
static const char *BASE64_MAP="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";	/* Mapping table,length is 65Bytes. */

/* Functions definition. */

/*
static unsigned short int _Binary_Calculater_(const char *Binary,unsigned short int Length);
*
 * I think that need a binary calculating algorithm to help me get a decide number.
 * So,I had made this function.
 *

static unsigned short int _Binary_Calculater_(const char *Binary,unsigned short int Length)
{
	unsigned short int Result(0);	// For return.	
	unsigned short int PowerOf2(1);	// 2'0 power.

	//	Env

	*
 	 * I made the cycle to calculating index-calculation-in-based-2 together.
 	 * Ande before return,calculate the 2'0(1) multipes Binary's head element.
 	 * This method could prevent wasting.
 	 *
	for (unsigned short int Index(1); Index < Length; ++Index)
	{
		PowerOf2*=2;	// Index calculation in based 2.
		Result+=(Binary[Index]-'0')*PowerOf2;	// Convert.
	}
	//	Primary

	return (Binary[0]-'0')*1+Result;
	//	Return
} 
*/

static unsigned short int _Search_Index_(char c);
static unsigned short int _Search_Index_(char c)
{

	unsigned short int Scriptor(0);	// Init.

	//	Env

	for (unsigned short index(0); c != '\0' && index < 64; ++index)
		if (c == BASE64_MAP[index])
		{
			Scriptor=index;
			break;
		}
		else;

	//	Primary


	return Scriptor;
	//	Return
}

char *_Base64_Encode_(const char *PlainText,char *Buffer,size_t Len_Buff)
{
	/*
	 * Return Buffer on success,return NULL on failed.
	 * Calculate quotient and remainder for PlainText.
	 * If append zero byte,then append '=' number as same with zero bytes.
	 * Must to alloc memory.
	 * Use '=' to instead mapping for zero byte.
	 * Buffer's length must greater than PlainText in multiple of 4/3.
	 */

	char *TempBuff(NULL);	// For alloc memory.
	uint16_t PlainLen(0);	// For length.
	uint16_t Quotient(0),Remainder(0);	// For calculating.
	int32_t Value1(0),Value2(0),Value3(0);	// For temporarily save.
	int32_t BitValue(0);	// For bit operate.
	uint16_t BuffINDEX(0);	// Buffer pointer.

	//	Env
	
	/* Pointer must not NULL */
	if (PlainText == NULL || Buffer == NULL)
		return NULL;
	else;

	/* Get PlainText length. */
	PlainLen=strlen(PlainText);
	
	/* Check Len_Buff */
	if (Len_Buff <= PlainLen*4/3)
		return NULL;
	else;

	/* To get memory. */
	if ((TempBuff=new char[PlainLen+3]) == NULL)
		return NULL;
	else
		Remainder=PlainLen-(PlainLen/3)*3,	// Calculating quotient and remainder.
		Quotient=(Remainder == 0)?PlainLen/3:PlainLen/3+1;
	
	/* Copy PlainText */
	strncpy(TempBuff,PlainText,PlainLen);

	/* To checking whether need to append zero byte. */
	// If Remainder is equal to 0,then no append.
	for (uint16_t Count(0); Count < 3-Remainder && Remainder != 0; ++Count)
		*(TempBuff+PlainLen+Count)='\0';

	/* Cycle to translate */
	/*
	 * Displacement used to accessing the memory,Counter as the Cycle count number.
	 */ 
	for (uint16_t Counter(0),Displacement(0); Counter < Quotient; ++Counter,Displacement+=3)
	{
		/* Three bytes. */
		Value1=(TempBuff+Displacement)[0],Value2=(TempBuff+Displacement)[1],Value3=(TempBuff+Displacement)[2];

		/* First */
		BitValue=Value1 >> 2;
		
		if (BitValue == 0)
			break;
		else
			Buffer[BuffINDEX++]=BASE64_MAP[BitValue];


		/* Second */
		BitValue=((Value1 & 3) << 4) | (Value2 >> 4);

		if (BitValue == 0)
			break;
		else
			Buffer[BuffINDEX++]=BASE64_MAP[BitValue];

		/* Third */
		BitValue=((Value2 & 0x0F) << 2) | ((Value3 & 0xC0) >> 6);

		if (BitValue == 0)
			break;
		else
			Buffer[BuffINDEX++]=BASE64_MAP[BitValue];

		/* Fourth */
		BitValue=(Value3 & 0x3F);

		if (BitValue == 0)
			break;
		else
			Buffer[BuffINDEX++]=BASE64_MAP[BitValue];
	}

	/* To append '=' in buffer. */
	for (uint16_t Count(0); Count < 3-Remainder && Remainder != 0; ++Count)
		Buffer[BuffINDEX++]='=';
	Buffer[BuffINDEX]='\0';	// End of string.


	//	Primary

	/* Recycle */
	delete[] TempBuff;
	TempBuff=NULL;

	return Buffer;
	//	Return
}

char *_Base64_Decode_(const char *CipherText,char *Buffer,size_t Len_Buff)
{
	/*
	 * CipherText must be length equal to a value multiple of 4.
	 * Return Buffer on succeed,return NULL on failed.
	 * Would calculate Quotient and Remainder.
	 * Do count for the number of '='.
	 * Translate '=' to zero byte.
	 * So the least one in array must contains bits of zero byte.
	 */ 

	uint16_t Quotient(0),Remainder(0);	// To save calculate result.
	uint16_t CipherLen(0);	// For ciphertext length.
	int32_t Value1(0),Value2(0),Value3(0),Value4(0);	// For four values.
	int32_t BitValue(0);	// For convert temporary.
	unsigned short int BuffINDEX(0);	// For buffer pointer.
	char *TempMEM(NULL);	// For save CipherText.
	char *Pointer_To_Return(NULL);	// Pointer to return.

	//	Env

	/* Pointer must not NULL */
	if (CipherText == NULL || Buffer == NULL)
		return Pointer_To_Return;
	else;

	
	/* Get CipherText len. */
	CipherLen=strlen(CipherText);

	/* Len_Buff must length than a value multiple in 3/4 of CipherText length. */
	if (Len_Buff <= CipherLen*3/4)
		return Pointer_To_Return;
	else
		Quotient=CipherLen/4,
		Remainder=CipherLen-(CipherLen/4)*4;	// Calculate values.

	/* Checking Remainder. */
	if (Remainder != 0)	// Fault length.
		return Pointer_To_Return;
	else;
	
	if ((TempMEM=new char[CipherLen+1]) == NULL)
		return Pointer_To_Return;
	else;

	strncpy(TempMEM,CipherText,CipherLen);	// Copy.


	/* To scan '=' and translate them */
	--CipherLen;
	while (*(TempMEM+CipherLen) == '=')
		*(TempMEM+CipherLen--)='\0';

	// After this cycle end,CipherLen had point to a character it is not '='.

	Pointer_To_Return=Buffer;
	for (uint16_t Displacement(0),Counter(0); Counter < Quotient; ++Counter,Displacement+=4)
	{
		/* To get four values. */
		Value1=_Search_Index_((TempMEM+Displacement)[0]),Value2=_Search_Index_((TempMEM+Displacement)[1]),
		Value3=_Search_Index_((TempMEM+Displacement)[2]),Value4=_Search_Index_((TempMEM+Displacement)[3]);

		/* In the converting,if BitValue is equal to zero,then break cycle. */

		/* First */
		BitValue=(Value1 << 2) | (Value2 >> 4);
		if (BitValue == 0)
			break;
		else
			Buffer[BuffINDEX++]=BitValue;
	
		/* Second */
		BitValue=(Value2 << 4) | (Value3 >>2);
		if (BitValue == 0)
			break;
		else
			Buffer[BuffINDEX++]=BitValue;

		/* Third */
		BitValue=(Value3 << 6) | Value4;
		if (BitValue == 0)
			break;
		else
			Buffer[BuffINDEX++]=BitValue;

	}

	Buffer[BuffINDEX]='\0';	// End string.


	//	Primary

	/* Recycle. */
	delete[] TempMEM;
	TempMEM=NULL;

	return Pointer_To_Return;
	//	Return
}

}	/* End named space */
