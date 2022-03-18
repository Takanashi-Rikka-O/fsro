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

#include"base64.h"

namespace base64 {

/* Data structures */
  static const char *BASE64_MAP = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";	/* Mapping table,length is 65Bytes. */


#define index_of_map(c)			\
  ({					\
  unsigned short int index(0);		\
  const char *base64map(BASE64_MAP);	\
  for (index = 0; *base64map != '\0';	\
       ++base64map,index++)		\
    if (*base64map == c)		\
      break;				\
  index + 0;				\
  })

#define next_address(src,displacement)	\
  ((src) + (displacement))

#define first_of(x)	(*(x))
#define second_of(x)	(*((x) + 1))
#define third_of(x)	(*((x) + 2))
#define fourth_of(x)	(*((x) + 3))

  char *base64_encode(const char *plaintext,char *buffer,size_t buffer_len){
    const char *entry(NULL);
    char *encode_buffer(NULL),*return_value(NULL);

    // three element form a component
    unsigned char first('\0'),second('\0'),third('\0');

    unsigned char map_index('\0');
    unsigned short int plain_len(0),encode_buffer_index(0);
    unsigned short int &buffer_index = encode_buffer_index;
    unsigned short int quotient(0),remainder(0);

    // NULL target
    if (plaintext == NULL || buffer == NULL)
      return NULL;

    plain_len = strlen(plaintext);
    encode_buffer = new char[plain_len + 16];

    if (!encode_buffer)
      return NULL;

    // buffer space is not enough
    if (buffer_len < plain_len * 4)
      goto base64_encode_exit;

    strncpy(encode_buffer,plaintext,plain_len);
    quotient = plain_len / 3;
    remainder = plain_len - (plain_len / 3) * 3;
    if (remainder != 0) {
      // replenish zero.
      encode_buffer_index = plain_len;
      for (unsigned short int count(0); count < 3 - remainder; ++count)
	encode_buffer[encode_buffer_index++] = '\0';
      encode_buffer[encode_buffer_index] = '\0';	// end as '\0'
      quotient = encode_buffer_index / 3;
    }

    entry = encode_buffer;
    buffer_index = 0;
    for (unsigned short int iterator(0); iterator < quotient; ++iterator) {
      first = first_of(entry);
      second = second_of(entry);
      third = third_of(entry);

      map_index = (unsigned char)(first >> 2);
      buffer[buffer_index++] = BASE64_MAP[map_index];

      map_index = (unsigned char)((unsigned char)(first << 6) >> 2) | (unsigned char)(second >> 4);
      buffer[buffer_index++] = BASE64_MAP[map_index];

      map_index = (unsigned char)((unsigned char)(second << 4) >> 2) | (unsigned char)(third >> 6);
      buffer[buffer_index++] = BASE64_MAP[map_index];

      map_index = (unsigned char)(third << 2) >> 2;
      buffer[buffer_index++] = BASE64_MAP[map_index];

      entry = next_address(entry,3);
    }

    for (unsigned short int count(0),index(buffer_index - 1); remainder != 0 && count < 3 - remainder;
	 ++count)
      buffer[index--] = '=';
    buffer[buffer_index] = '\0';
    return_value = buffer;


  base64_encode_exit:
    delete[] encode_buffer;
    return return_value;
  }

  char *base64_decode(const char *ciphtertext,char *buffer,size_t buffer_len){
    const char *entry(NULL);
    char *decode_buffer(NULL),*return_value(NULL);
    size_t ciphter_len(0);

    // four elements form a component
    unsigned char first('\0'),second('\0'),third('\0'),fourth('\0');
    unsigned char map_index1(0),map_index2(0),map_index3(0),map_index4(0);
    unsigned short int quotient(0),remainder(0),decode_buffer_index(0);
    unsigned short int &buffer_index = decode_buffer_index;

    if (ciphtertext == NULL || buffer == NULL)
      return NULL;

    ciphter_len = strlen(ciphtertext);
    quotient = ciphter_len / 4;
    remainder = ciphter_len - (ciphter_len / 4) * 4;

    // output buffer is not enough
    if (buffer_len < (quotient * 3))
      return NULL;

    // It's not a right string formed by base64
    if (remainder != 0)
      return NULL;

    decode_buffer = new char[ciphter_len];
    if (!decode_buffer)
      goto base64_decode_exit;

    strncpy(decode_buffer,ciphtertext,ciphter_len);
    // delete zero
    for (unsigned short int index(ciphter_len - 1); 
	 decode_buffer[index] == '=' && index > 0; --index)
      decode_buffer[index] = *BASE64_MAP;

    entry = decode_buffer;
    buffer_index = 0;
    for (unsigned short int count(0); count < quotient; ++count) {
      first = first_of(entry);
      second = second_of(entry);
      third = third_of(entry);
      fourth = fourth_of(entry);

      map_index1 = index_of_map(first);
      map_index2 = index_of_map(second);
      map_index3 = index_of_map(third);
      map_index4 = index_of_map(fourth);

      if (map_index1 >= 64 || map_index2 >= 64 ||
	  map_index3 >= 64 || map_index4 >= 64)
	goto base64_decode_exit;

      buffer[buffer_index++] = (unsigned char)(map_index1 << 2) | (unsigned char)(map_index2 >> 4);
      buffer[buffer_index++] = (unsigned char)(map_index2 << 4) | (unsigned char)(map_index3 >> 2);
      buffer[buffer_index++] = (unsigned char)(map_index3 << 6) | map_index4;

      entry = next_address(entry,4);
    }

    buffer[buffer_index] = '\0';
    return_value = buffer;

  base64_decode_exit:
    delete[] decode_buffer;
    return return_value;
  }

}	/* End named space */
