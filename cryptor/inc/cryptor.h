
/* Name: cryptor.h
 * Type: Header
 * Description:
 * Header:
 * Function prototype:
 * Last modified date:
 * Fix:
 */

 /* Feature */
 /* Header */
 /* Macro */
 /* Data */
 /* Function */

#ifndef _CRYPTOR_H_
#define _CRYPTOR_H_

#include"algo.h"
#include"base64.h"

using namespace cryptor;
using namespace std;

#define ENCODE_OPT	'e'
#define DECODE_OPT	'd'
#define SETSORT_OPT	's'

#define OPT_UNKNOWN	1
#define OPT_REQARG	2
#define OPT_ERR		3

#define ENCODE_ERR	4
#define DECODE_ERR	5
#define COPY_ERR	6
#define PROGRAM_ERR	7

#define car(x) (*x)
#define cdr(x) (*(x + 1))
#define if_into_it(list,c)			\
  ({						\
      unsigned short int cond = 0;		\
      const char *travel = list;		\
      while (*travel != '\0') {			\
          if (*travel == c) {			\
              cond=1;				\
              break;				\
          }					\
          else ++travel;			\
      }						\
      travel = (cond) ? travel : NULL;		\
  })

#define ENCODEBUFF_SIZE		64+1
#define DECODEBUFF_SIZE		4 * (ENCODEBUFF_SIZE)

#endif
