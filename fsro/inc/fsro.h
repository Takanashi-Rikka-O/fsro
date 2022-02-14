
/* Name: fileSystemRecursiveOperation.h
 * Type: C++ program code file
 * Description: Head file of fsro,it contains some definition.
 * Header:
 * 	C++ header
 *	C header
 *	Linux header
 * Function prototype:
 *	Claasical functions
 * Last modified date: 2022-02-06
 * Fix:
 */

 /* Feature */
#ifndef _FSRO_H_
#define _FSRO_H_

#define _GNU_SOURCE

 /* Header */
#include<iostream>
#include<fstream>
#include<string>

#include<cstring>
#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>

#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<sys/mman.h>
#include<dirent.h>
#include<limits.h>

 /* Macro */
#define KB			1024
#define MB			(KB * KB)

#define OUTPUTSIZE		(KB / 2)
#define ALIGNMENTSIZE		(KB / 16)

#define EXECPARS_NUMBER	34	// total of args at most is 32

#define CFGPATH			"/etc/fsro/fsro.cfg"
#define FILTERPATH		"/etc/fsro/fsro_filter.o"


// Should always set error variable to zero before function invoking
#define FSRO_SUCCESS		0

#define REGULAR			0
#define DIRECTORY		1
#define SOCKET			2
#define CHAR_DEVICE		3
#define BLOCK_DEVICE		4
#define FIFO			5

// There are some error codes
#define CFG_NOTEXISTEDORDENYPERMISSION		1
#define CFG_OPENFAIL				2
#define CFG_READFAIL				3
#define OPERATION_NOTEXISTEDORDENYPERMISSION   	4	// It's not executable

#define FILTER_CANTGETFILEINFO			5
#define FILTER_UNKNOWN				6

#define STR_DESNULL				7
#define STR_NOFINDSUB				8
#define STR_APPENDFAULT				9
#define ACCESS_LIMITFAULT			10
#define FSRO_PIPEOPENFAIL			11
#define FSRO_MEMAPPLYFAULT			12
#define FSRO_CANTCOPY				13	// This is a debug code,that notes dont use copy constructor
#define FSRO_OPENDIRFAULT			14
#define FSRO_NOTINITED				15
#define FSRO_FORKFAULT				16
#define FSRO_PIPEREADINGERR			17
#define FSRO_CPEXCEPTION			18

#define MAKEOUTPUT_FAULT			19


 /* Data */

extern "C" {
  // C functions

  //  char *strstr(const char *__haystack,const char *__needle);
  char *strcat(char *,const char *);
  int lstat(const char *,struct stat *);
  int access(const char *,int);
  int open(const char *,int,...);
  int close(int);
  FILE *fmemopen(void *,size_t,const char *);
  int fprintf(FILE *,const char *,...);
  int fscanf(FILE *,const char *,...);
  int fclose(FILE *);
  int fseek(FILE *,off_t,int);
  int fprintf(FILE *,const char *,...);
  int fscanf(FILE *,const char *,...);
  pid_t fork(void);
  pid_t wait(void *);
  int dup2(int,int);
}

extern int fsroError;

 /* Function */

#define cStringAppend(desStr,toAppend)			\
	do {						\
	  if (! desStr)					\
	    fsroError=STR_DESNULL;			\
	  else if (strcat(desStr,toAppend) != desStr)	\
	    fsroError=STR_APPENDFAULT;			\
	  else;						\
	    } while (0)


// C string is end with '\0',so just erase '/' as well
#define cStringErase(srcStr,toErase)			\
	do {						\
	  char *erasePos=strrchr(srcStr,toErase);	\
	    if (! erasePos)				\
	      fsroError=STR_NOFINDSUB;			\
	    else					\
	      *erasePos='\0';				\
	      } while (0)


	  namespace fsrospace {
	    using namespace std;

	    class Fsro{
	    private:
	      string _outputContents;
	      string _alignmentCharacters;

	      size_t _operationPathSize;	// defined by _POSIX_PATH_MAX
	      char *_operationExec;		// path of executable file
	      char **_operationPara;

	      size_t _operationParaLength;	// option length for each
	      char *_operationArgs[EXECPARS_NUMBER];	// exec args max
	      unsigned int _endOfexecPara;

	      ifstream _readCfg;

	      size_t _fileContentBufferSize;
	      char *_fileContentBuffer;

	      int _pipeFD[2];
	      const size_t _pipeSize;
	      char _pipeMessage[PIPE_BUF];

	      int _fsroInitStatus;
	      int _fsrofilter;	// filter pattern switch

	      void fsroMain(char *nextDir);
	      int fsroCheckConfig(void)const;
	      int fsroCheckOperation(void)const;
	      int fsroFilter(const char *filepath);

	      void fsroErrorBroadcast(void);
	      int fsroBuildExecutition(void);
	      int fsroGenerateOutput(const char *content,...);
	      int fsroExec(char *target);

	    protected:
	      
	    public:

	      Fsro();
	      explicit Fsro(const Fsro &copy);
	      ~Fsro();

	      void fsroInit(void);
	      void fsroStartWork(void);
	      void fsroHelp(void)const;
	      void fsroSetFilterMode(int WHICH);

	    };



	  }

#endif
