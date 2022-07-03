
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

static int getopt(int argc,char * const argv[],const char *optstring);
static void getopt_strerror(void);

static const char *read_plaintext_file(const char *filename);

static int option_err = 0;
static const char *optarg = NULL;
static long int optopt = '\0';
static void cryptor_help(void);

static char toencode[ENCODEBUFF_SIZE];
static char todecode[DECODEBUFF_SIZE];

int main(int argc,char *argv[]){
  char option('\0');
  enum cryptor_mode {INIT = -1, ENCODE = 0, DECODE = 1, ENCODE_CYCLE};
  cryptor_mode eord(INIT);	// encode(0) or decode(1).
  Cryptor cpt;
  const char *the_argument(NULL);
  const char *encode_from_file(NULL);
  const char *filename(NULL);

  if (argc < 3)
    cryptor_help();
  else;

  if (! cpt.init_Cryptor())
    return -PROGRAM_ERR;

  // cycyle to check options
  while ((option = getopt(argc,argv,"e:d:s:f:")) != -1) {
    switch (option) {
    case ENCODE_OPT:
      if (eord == DECODE)	// It will be activity just the first.
	break;
      else {
	eord = ENCODE;
	the_argument = optarg;
      }
      break;

    case DECODE_OPT:
      if (eord == ENCODE)
	break;
      else {
	eord = DECODE;
	the_argument = optarg;
      }
      break;

    case SETSORT_OPT:
      cpt.set_keyword_value((*optarg) - '0');
      break;

    case ENCODE_FROM_FILE:
      eord = ENCODE_CYCLE;
      filename = optarg;
      break;

    default :
      getopt_strerror();
      cryptor_help();
    }
  }

  // pick behavior
  switch (eord) {
  case ENCODE:
    if (strncpy(toencode,the_argument,strlen(the_argument))) {
      if (cpt.encode(toencode,strlen(toencode),todecode,DECODEBUFF_SIZE))
	cout<<todecode<<endl;
      else
	return -ENCODE_ERR;
    }
    else
      return -COPY_ERR;
    break;

  case DECODE:
    if (strncpy(todecode,the_argument,strlen(the_argument))) {
      if (cpt.decode(todecode,strlen(todecode),toencode,ENCODEBUFF_SIZE))
	cout<<toencode<<endl;
      else
	return -DECODE_ERR;
    }
    else
      return -COPY_ERR;
    break;

  case ENCODE_CYCLE:
    while ((the_argument = read_plaintext_file(filename)) != NULL) {

      /* if next input less than last,todecode will be overlapped.
       * that will trigger output error.
       */
      memset(toencode,'\0',ENCODEBUFF_SIZE);
      memset(todecode,'\0',DECODEBUFF_SIZE);

      if (strncpy(toencode,the_argument,strlen(the_argument))) {
	if (cpt.encode(toencode,strlen(toencode),todecode,DECODEBUFF_SIZE))
	  cout<<todecode<<endl;
	else
	  return -ENCODE_ERR;
      }
      else
	return -COPY_ERR;
    }
    read_plaintext_file(NULL);	/* noticing for close file */
    break;

  default:
    return -PROGRAM_ERR;
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
      // style alike to '-'
      if (car((&cdr(entry)) + 1) != '\0') {
	// In this case,probably the character '-' had palced at second position.
	result = '?';
	option_err = OPT_ERR;
	optopt = (long int)entry;
      }
      opt_in_optstr = if_into_it(optstring,car(entry));	// Check optstring.
      if (opt_in_optstr)
	result = car(opt_in_optstr);
      else {
	result = '?';
	option_err = OPT_UNKNOWN;
	optopt = cdr(entry);
      }
    }
  } else {
    // option is not placed '-' at ahead.
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

static const char *read_plaintext_file(const char *filename){

  static ifstream input_file;
  static char filebuff[ENCODEBUFF_SIZE];
  memset(filebuff,'\0',ENCODEBUFF_SIZE);

  if (NULL == filename) {
    input_file.close();
    return NULL;
  }

  if (!input_file.is_open()) {
    input_file.open(filename,ios_base::in);
    if (!input_file.is_open())
      return NULL;      
  }

  /* Must skip the case is readed a blank to prevent divide trap */
  do {
    input_file.getline(filebuff,ENCODEBUFF_SIZE);
    if (input_file.eof() || input_file.fail() || input_file.bad()) {
      input_file.close();
      return NULL;
    }
  } while (strlen(filebuff) == 0);

  return filebuff;
}
