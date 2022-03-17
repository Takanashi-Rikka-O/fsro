
/* Name: cryptor.cpp
 * Type: C++ program code file
 * Description:
 *	main file of Cryptor.
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

#include"cryptor.h"
#include<iostream>

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

static int getopt(int argc,char * const argv[],const char *optstring);
static void getopt_strerror(void);

//static unsigned short int cond = 0;
//static const char *travel = NULL;

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

static int option_err = 0;
static const char *optarg = NULL;
static long int optopt = '\0';

static void cryptor_help(void);


#define ENCODEBUFF_SIZE		64+1
#define DECODEBUFF_SIZE		4 * (ENCODEBUFF_SIZE)

static char toencode[ENCODEBUFF_SIZE];
static char todecode[DECODEBUFF_SIZE];

int main(int argc,char *argv[]){

  char option='\0';
  Cryptor cpt;

  if (argc < 3)
    cryptor_help();
  else;

  if (! cpt.init_Cryptor())
    return -PROGRAM_ERR;

  while ((option = getopt(argc,argv,"e:d:s:")) != -1) {
    switch (option) {
    case ENCODE_OPT:
      if (strncpy(toencode,optarg,strlen(optarg))) {
	if (cpt.encode(toencode,strlen(toencode),todecode,DECODEBUFF_SIZE))
	  cout<<todecode<<endl;
	else
	  return -ENCODE_ERR;
      }
      else
	return -COPY_ERR;

      break;

    case DECODE_OPT:
      if (strncpy(todecode,optarg,strlen(optarg))) {
	if (cpt.decode(todecode,strlen(todecode),toencode,ENCODEBUFF_SIZE))
	  cout<<toencode<<endl;
	else
	  return -DECODE_ERR;
      }
      else
	return -COPY_ERR;

      break;

    case SETSORT_OPT:
      cpt.set_keyword_value((*optarg) - '0');
      break;

    default :
      getopt_strerror();
      cryptor_help();

    }

  }


  return 0;
}

static void cryptor_help(void){

  cerr<<"usage: cryptor [ -eds ] argument"<<endl
      <<"-e <string>: encode"<<endl
      <<"-d <string>: decode"<<endl
      <<"-s <value>: set keyword value"<<endl;

  exit (0);

}

static int getopt(int argc,char * const argv[],const char *optstring){

  static unsigned short int args_pos_record = 1;
  static unsigned short int &call_count = args_pos_record;
  static const char *args = argv[1];
  static const char *entry = NULL;
  const char *opt_in_optstr = NULL;
  int result = 0;

  // cant exceed argv.
  if (call_count > argc - 1)
    return -1;

  entry = argv[args_pos_record];	// We wish it be a pair like this (- c)

  if (car(entry) == '-') {

    // style alike to '-x'
    if (cdr(entry) != '\0' && car((char *) ((&cdr(entry)) +1 )) == '\0') {

      // To find out whether cdr(entry) into optstring.
      opt_in_optstr = if_into_it(optstring,cdr(entry));
      if (opt_in_optstr) {

	// If the option needs an argument
	if (cdr(opt_in_optstr) == ':') {
	  optarg = argv[args_pos_record + 1];
	  if (car(optarg) == '-') {
	    result = '?';
	    option_err = OPT_REQARG;
	    optarg = NULL;
	    optopt = cdr(entry);
	  } else {
	    ++args_pos_record;
	    result = cdr(entry);
	  }
	}
	else
	  result = cdr(entry);
      } else {
	result = '?';
	option_err = OPT_UNKNOWN;
	optopt = cdr(entry);
      }
    } else {
      if (car((&cdr(entry)) + 1) != '\0') {
	result = '?';
	option_err =OPT_ERR;
	optopt = (long int)entry;
      }
      // style alike to '-'
	opt_in_optstr = if_into_it(optstring,car(entry));
	if (opt_in_optstr)
	  result = car(opt_in_optstr);
	else {
	  result = '?';
	  option_err = OPT_UNKNOWN;
	  optopt = cdr(entry);
	}
    }
  } else {
    result = '?';
    option_err = OPT_ERR;
    optopt = (long int)entry;
  }

  ++args_pos_record;
  return result;
}




static void getopt_strerror(void){

  switch (option_err) {
  case OPT_UNKNOWN:
    cerr<<"option "<<static_cast<char>(optopt)<<" unknown."<<endl;
    break;

  case OPT_REQARG:
    cerr<<"option "<<static_cast<char>(optopt)<<" needs an argument."<<endl;
    break;

  case OPT_ERR:
    cerr<<"option "<<(char *)optopt<<" is not an option."<<endl;
    break;

  default:
    cerr<<"analyzing unknown error."<<endl;
  }

}
