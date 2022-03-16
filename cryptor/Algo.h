//	Algo.h
//	Version : 0.1.1
//	Date : Fri Jul 31 21:28:32 2020
//	Last revise : Thu Sep 17 21:12:32 2020
//	Symbol-Constraint :
//			_Xx..._ - Function Symbol
//			Xx...|x|X - Variable Symbol
//	Description :
//		Algothrim function header.
//
//	Functions :
//		char *_Encode_(const char *Buff,unsigned short int Len);
//		char *_Decode_(const char *Buff,unsigned short int Len);
//
//	Header :
//		<cstddef>
//		"Base64.h"
//
//	Fix : 
//		1> Adding base64 encode and decode.

#ifndef _ALGO_H_
#define _ALGO_H_

#include<cstddef>
#include"Base64.h"

#define HASHP2C "XJwd!fGZib<l,)Opq<(tuvCayhSnERkm"	// Maping A->B.
#define HASHK2C "xbedPfvhSzW+-1m}?@#tQ&c(%Hsq;a<>"	// Maping x'->B.
#define HASHLISTLEN 32
#define HASHLISTLENGTH HASHLISTLEN + 1

// error code
#define EMEMAPPLY 16

#define SCALE_VALUE 1193

#define scale(x) ((x) * SCALE_VALUE)

namespace cryptor {

  class Cryptor {
  private:

    char *_hashlist_of_p2c;
    char *_hashlist_of_k2c;
    size_t _list_length;
    size_t _division;
    unsigned short int _resort_distance;
    const unsigned int _scale;

  protected:


  public:

    Cryptor();
    Cryptor(unsigned int sort_distance);
    ~Cryptor();
    Cryptor(const Cyptor & cryptor);

    int init_Cryptor(void);

    void sort_hashlist(void);

    char *decode(const char *input_buffer,size_t input_len,
		 char *output_buffer,size_t output_len);
    char *encode(const char *input_buffer,size_t input_len,
		 char *output_buffer,size_t output_len);

    template<TYPE>
    TYPE scale_element(TYPE x);


  };






}



#endif

