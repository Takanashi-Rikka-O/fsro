//	Base64.h
//	Version : 0.1.1
//	Date : Sun Sep  6 20:19:21 2020
//	Last revise : Wed Sep  16 20:24:21 2020
//	Symbol-Constraint :
//			_Xx..._ - Function Symbol
//			Xx...|x|X - Variable Symbol
//	Description :
//		Header of base64 cryptography.
//
//	Functions :
//		char *_Base64_Encode_(const char *PlainText,char *Buffer,const short int Len_Buff);
//		char *_Base64_Decode_(const char *CipherText,char *Buffer,const short int Len_Buff);
//
//	Header :
//		<cstring>	// ISO C string functions.
//		<cinttypes>	// ISO C Expended types.
//
//	Fix : 
//		1> Contain elements into named space.

#ifndef _BASE64_H_
#define _BASE64_H_

#include<cinttypes>	// C int type.
#include<cstring>	// C string.


namespace BASE64{

/* Functions */

/* Define :
 *	Len_Buff must greater than 0.
 *	Len_Buff must greater than Length-of-Data in 1/3 multiple.
 */ 

char *_Base64_Encode_(const char *PlainText,char *Buffer,size_t Len_Buff);
/*
 * Encode for base64.
 *  Per three bytes as a group,all is 24bits,and per six bits to make mapping with table.
 *  If length in bytes not is multipe of 3,then append 0x00(byte) in the end.The append byte would delete in the time of decode.
 */ 
/*
 * Return the address of Buffer on succeed,return NULL on failed.
 */ 

char *_Base64_Decode_(const char *CipherText,char *Buffer,size_t Len_Buff);
/*
 * Decode for base64.
 * Decode must scan bytes to search 0x00 byte and delete them,and then do decoding.
 */
/*
 * Return the address of Buffer on succeed,return NULL on failed.
 */  

}

#endif /* Header end */

