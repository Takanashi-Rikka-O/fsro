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

#include"algo.h"

#define remainder(x,mod) ((x) - ((x) / (mod)) * (mod))
#define position(list,c,pos) 				\
  do {			 				\
  unsigned short int condition(0);			\
  unsigned short int iterator(0);			\
  for (const char *travel=list; *travel != '\0';	\
       ++travel,++iterator) {				\
      if (*travel == c) {				\
      condition = 1;					\
      break;						\
      }						        \
  }							\
  pos = (condition) ? iterator : pos;			\
  } while (0)						\

namespace cryptor {

  using namespace base64;
  using namespace std;

  #define TEMPBUFFER_SIZE 1024
  static char base64_buffer[TEMPBUFFER_SIZE];

  Cryptor::Cryptor():_scale(SCALE_VALUE){

    _list_length = HASHLISTLENGTH;
    _division = HASHLISTLEN;
    _resort_distance = 0;

    _hashlist_of_p2c = _hashlist_of_k2c = NULL;

  }

  Cryptor::Cryptor(unsigned int sort_distance):_scale(SCALE_VALUE){

    _list_length = HASHLISTLENGTH;
    _division = HASHLISTLEN;
    _resort_distance = sort_distance;

    _hashlist_of_p2c = _hashlist_of_k2c = NULL;

  }

  Cryptor::~Cryptor(){

    delete[] _hashlist_of_p2c,_hashlist_of_p2c = NULL;
    delete[] _hashlist_of_k2c,_hashlist_of_k2c = NULL;

  }

  Cryptor::Cryptor(const Cryptor & cryptor):_scale(SCALE_VALUE){

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
    if (strncpy(_hashlist_of_p2c,HASHP2C,HASHLISTLENGTH) == NULL || strncpy(_hashlist_of_k2c,HASHK2C,HASHLISTLENGTH) == NULL)
      return 0;

    sort_hashlist();	// resort elements into hashlist.

    return 1;
  }

  // sort_hashlist() just exchanges two elements both at the position is not same as each.
  // If exceed memory size limit,just does nothing.
  void Cryptor::sort_hashlist(void){

    unsigned short int index(0);
    char i = '\0',j = '\0';

    for (index = 0; index < _list_length; ++index) {
      if (index + _resort_distance < _list_length) {
	i = _hashlist_of_p2c[index];
	j = _hashlist_of_p2c[index + _resort_distance];

	if (j != '\0') {
	  _hashlist_of_p2c[index] = j;
	  _hashlist_of_p2c[index + _resort_distance] = i;
	}
      }
      else
	break;
    }

    for (index = 0; index < _list_length; ++index) {
      if (index + _resort_distance < _list_length) {
	i = _hashlist_of_k2c[index];
	j = _hashlist_of_k2c[index + _resort_distance];

	if (j != '\0') {
	  _hashlist_of_k2c[index] = _hashlist_of_k2c[index + _resort_distance];
	  _hashlist_of_k2c[index + _resort_distance] = i;
	}
      }
      else
	break;
    }

  }

  void Cryptor::set_keyword_value(unsigned short int x){
    _resort_distance = x;
    sort_hashlist();
  }

  char *Cryptor::encode(const char *input_buffer,size_t input_len,
			char *output_buffer,size_t output_len)
  {
    long int after_scale(0);
    int quotient_value(0),remainde_value(0);
    char *after_base64_encode(NULL);

    // There is not enough space to save data that had encoded.
    //    if (output_len / input_len < 4)
    //      return NULL;

    memset(base64_buffer,'\0',TEMPBUFFER_SIZE);

    // mapping i into 'p2c',mapping the key for decode i into 'k2c'.
    for (unsigned short int input_index(0),r(1),q(0); input_index < input_len; ++input_index) {
      after_scale = scale_element(static_cast<long int>(input_buffer[input_index]));
      quotient_value = after_scale / _division;
      remainde_value = remainder(after_scale,_division);

      output_buffer[r] = _hashlist_of_p2c[remainde_value];
      output_buffer[q] = _hashlist_of_k2c[quotient_value];

      r+=2;
      q+=2;

    }

    after_base64_encode=base64_encode(output_buffer,base64_buffer,TEMPBUFFER_SIZE);

    if (after_base64_encode == NULL)
      return NULL;

    memset(output_buffer,'\0',output_len);


    return strncpy(output_buffer,after_base64_encode,strlen(after_base64_encode));
  }

  char *Cryptor::decode(const char *input_buffer,size_t input_len,
			char *output_buffer,size_t output_len)
  {
    short int tempvalue(0);
    unsigned short int quotient_value(0),remainde_value(0),output_index(0);
    char rc('\0'),qc('\0');
    char *after_base64_decode(NULL);

    // The encoding will mappes an element to two elements.
    //    if (input_len / output_len > 4)
    //  return NULL;

    memset(base64_buffer,'\0',TEMPBUFFER_SIZE);

    after_base64_decode=base64_decode(input_buffer,base64_buffer,TEMPBUFFER_SIZE);

    if (after_base64_decode == NULL)
      return NULL;

    for (unsigned short int r(1),q(0); r < input_len; r+=2,q+=2) {
      rc = after_base64_decode[r];
      qc = after_base64_decode[q];

      // Zero is not in our hashlist.In the case,must arrived end of input.
      if (qc == '\0')
	break;

      position(_hashlist_of_p2c,rc,tempvalue);
      remainde_value = (tempvalue != -1) ? tempvalue : 0;

      position(_hashlist_of_k2c,qc,tempvalue);
      quotient_value = (tempvalue != -1) ? tempvalue : 0;

      output_buffer[output_index++] = (quotient_value * _division + remainde_value) / _scale;
    }

    output_buffer[output_index] = '\0';

    return output_buffer;
  }



}
