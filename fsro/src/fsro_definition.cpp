
/* Name: fsro_definition.cpp
 * Type: C++ program code file
 * Description:
 * Header:
 * Function prototype:
 * Last modified date:
 * Fix:
 */

 /* Feature */
 /* Header */
#include"fsro.h"

int fsroError=0;

 /* Macro */
 /* Data */
 /* Function */

#define execFsroErrorBC(errorCode)	\
  do {					\
  fsroError=errorCode;			\
  fsroErrorBroadcast();			\
  } while (0)

#define YES	"yes"
#define NO	"no"
static const char *result=NULL;

static int
ifAdir(const char *itemName);


namespace fsrospace{


  Fsro::Fsro():_outputContents(OUTPUTSIZE,'\0'),_alignmentCharacters(ALIGNMENTSIZE,'\0'),_pipeSize(PIPE_BUF){

    int tmpValue=0;

    fsroError=FSRO_SUCCESS;

    // get system limits and set value
    if ((tmpValue=pathconf("/",_PC_PATH_MAX)) < 0)
      execFsroErrorBC(ACCESS_LIMITFAULT);
    else _operationPathSize=tmpValue;

    if ((tmpValue=pathconf("/",_PC_NAME_MAX)) < 0)
      execFsroErrorBC(ACCESS_LIMITFAULT);           
    else _operationParaLength=tmpValue+1;	// Last one is '\0'

    // apply memory for save exec arguments in further

    if (! (_operationArgs[0]=new char[_operationPathSize]))
      execFsroErrorBC(FSRO_MEMAPPLYFAULT);
    else
      _operationExec=_operationArgs[0];

    for (int iterator(1); iterator < EXECPARS_NUMBER-1; ++iterator)
      if (! (_operationArgs[iterator]=new char[_operationParaLength]))
	execFsroErrorBC(FSRO_MEMAPPLYFAULT);
      else;
    _operationArgs[EXECPARS_NUMBER-1]=NULL;	// Last one is NULL as end of exec parameters

    _endOfexecPara=0;
    _targetIndexOfexec=0;

    // Major message only one statement
    _fileContentBufferSize=_operationParaLength*EXECPARS_NUMBER+_operationPathSize+32;

    if (! (_fileContentBuffer=new char[_fileContentBufferSize]))
      execFsroErrorBC(FSRO_MEMAPPLYFAULT);
    else;


    memset(_pipeMessage,'\0',_pipeSize);

    _fsroInitStatus=0;

  }

  Fsro::~Fsro(){

    fsroError=FSRO_SUCCESS;

    if (fsroError != FSRO_SUCCESS)
      execFsroErrorBC(fsroError);
    else;

    if (_endOfexecPara != 0){
      for (int iterator(0); iterator < _targetIndexOfexec+1; ++iterator)
	if (_operationArgs[iterator])
	  delete[] _operationArgs[iterator],_operationArgs[iterator]=NULL;
	else;

      for (int iterator(_endOfexecPara+1); iterator < EXECPARS_NUMBER-1; ++iterator)
	if (_operationArgs[iterator])
	  delete[] _operationArgs[iterator],_operationArgs[iterator]=NULL;
	else;

    }
    else
      for (int iterator(0); iterator < EXECPARS_NUMBER-1; ++iterator)
	if (_operationArgs[iterator])
	  delete[] _operationArgs[iterator],_operationArgs[iterator]=NULL;
	else;

    if (_readCfg.is_open())
      _readCfg.close();
    else;

    if (_fileContentBuffer)
      delete[] _fileContentBuffer,_fileContentBuffer=NULL;
    else;

  }

  Fsro::Fsro(const Fsro &copy):_pipeSize(0){
    execFsroErrorBC(FSRO_CANTCOPY);
  }

  void Fsro::fsroHelp(void)const{
    cout<<"fsro helper:"<<endl
	<<"\tUsage: fsro <options>"<<endl
	<<"\t Options: -n -h -m <pattern>"<<endl
	<<"\t -n told fsro that doesnt output any messages on termination"<<endl
	<<"\t -h get help messages"<<endl
	<<"\t -m select filter match pattern,that are regular|directory|socket|chardev|blockdev|fifo"<<endl
	<<"# Dont use -h option with others at same time!"<<endl
	<<"# If you didnt select any filter pattern,it will be set regular by default"<<endl;
  }

  inline  int Fsro::fsroCheckConfig(void)const{
    fsroError=(access(CFGPATH,F_OK|R_OK) < 0)?CFG_NOTEXISTEDORDENYPERMISSION:fsroError;
    return (fsroError == FSRO_SUCCESS)?0:-1;
  }

  inline  int Fsro::fsroCheckOperation(void)const{
    fsroError=(access(_operationExec,F_OK|X_OK) < 0)?OPERATION_NOTEXISTEDORDENYPERMISSION:fsroError;
    return (fsroError == FSRO_SUCCESS)?0:-1;
  }

  int Fsro::fsroGenerateOutput(const char *content,...){

    va_list args;
    va_start(args,content);

    static char outputbuffer[OUTPUTSIZE]="\0";
    memset(outputbuffer,'\0',OUTPUTSIZE);

    // There use variable arguments with vsnprintf() to generate content
    if (vsnprintf(outputbuffer,OUTPUTSIZE,content,args) < 0){
      fsroError=MAKEOUTPUT_FAULT;
      return -1;
    }
    else{
      _outputContents.clear();
      _outputContents.assign(outputbuffer);
    }

    return 0;
  }

  int Fsro::fsroBuildExecutition(void){

    int cycleIterator=0;
    char *temppointer=NULL;
    char *pos=NULL;

    _readCfg.open(CFGPATH,ios_base::in);
    if (! _readCfg.is_open()){
      fsroError=CFG_OPENFAIL;
      return -1;
    }
    else;
    
    // Cycle to reads configure file
    while (1){
      memset(_fileContentBuffer,'\0',_fileContentBufferSize);
      _readCfg.getline(_fileContentBuffer,_fileContentBufferSize);
      if (*_fileContentBuffer == '#')
	continue;
      else{
	// after the first statement was readed from the file,quit this cycle
	_readCfg.close();
	break;
      }
    }

    _operationExec=_operationArgs[0];
    _operationPara=&_operationArgs[1];
    temppointer=_fileContentBuffer;


    // exec path
    pos=strchr(temppointer,' ');
    if (pos == NULL){
      // In this case,nothing of arg was followed.
      strcpy(_operationExec,temppointer);
      _targetIndexOfexec=0;
      _endOfexecPara=_targetIndexOfexec+1;
      return 0;

    }
    else{
      *pos='\0';
      strcpy(_operationExec,temppointer);
      temppointer=pos+1;
    }

    // exec para
    while (1){
      pos=strchr(temppointer,' ');

      // If pos == NULL,it's possible temppointer point to the last arg
      if (pos == NULL){
	strcpy(_operationPara[cycleIterator],temppointer);
	++cycleIterator;
	break;
      }
      else;

      *pos='\0';
      strcpy(_operationPara[cycleIterator],temppointer);
      temppointer=pos+1;
      ++cycleIterator;      
    }

    _targetIndexOfexec=cycleIterator;
    _endOfexecPara=_targetIndexOfexec+1;
    return 0;
  }

  void Fsro::fsroInit(void){

    // check cfg

    fsroError=FSRO_SUCCESS;
    if (fsroCheckConfig() < 0)
      execFsroErrorBC(fsroError);
    else;

    fsroError=FSRO_SUCCESS;
    if (fsroBuildExecutition() < 0)
      execFsroErrorBC(fsroError);
    else;

    fsroError=FSRO_SUCCESS;
    if (fsroCheckOperation() < 0)
      execFsroErrorBC(fsroError);
    else{
      // will set end of parameters be there.
      delete[] _operationPara[_targetIndexOfexec];
      _operationPara[_targetIndexOfexec]=NULL;		// file name will put in there

      delete[] _operationPara[_endOfexecPara];	// end of execv() args
      _operationPara[_endOfexecPara]=NULL;
    }

    _fsroInitStatus=1;

  }

  void Fsro::fsroStartWork(void){
    char *itempath=NULL;
    if (! _fsroInitStatus)
      execFsroErrorBC(FSRO_NOTINITED);
    else{
      itempath=_fileContentBuffer;
      memset(itempath,'\0',_fileContentBufferSize);
      *itempath='.';
      fsroMain(itempath);
    }

  }

  void Fsro::fsroMain(char *nextDir){
    DIR *dirPtr=NULL;
    struct dirent *currentDir=NULL;
    pid_t operateProgram=0;
    int programExitCode=-1;	// get the code returned by exit() or _exit()
    char *fullPath=nextDir;

    if (! (dirPtr=opendir(nextDir)))
      execFsroErrorBC(FSRO_OPENDIRFAULT);
    else;

    _alignmentCharacters+=' ';	// add alignments for new level

    // A cycle to reads directory
    while ((currentDir=readdir(dirPtr)) != NULL){

      // skip current and parent
      if (*currentDir->d_name == '.' && *(currentDir->d_name+1) == '\0')
	continue;
      else if (*currentDir->d_name == '.' && *(currentDir->d_name+1) == '.' &&
	       *(currentDir->d_name+2) == '\0')
	continue;
      else;

      // append path
      fsroError=FSRO_SUCCESS;
      cStringAppend(fullPath,"/");
      if (fsroError != FSRO_SUCCESS)
	execFsroErrorBC(fsroError);
      fsroError=FSRO_SUCCESS;
      cStringAppend(fullPath,currentDir->d_name);
      if (fsroError != FSRO_SUCCESS)
	execFsroErrorBC(fsroError);

      if (! fsroFilter(fullPath))
	goto nextcycle;
      else;

      memset(_pipeMessage,'\0',_pipeSize);	// reset pipe bufffer
      programExitCode=fsroExec(fullPath);	// exec operation

      if (programExitCode == 0)
	result=YES;
      else
	result=NO;

      fsroError=FSRO_SUCCESS;
      if (fsroGenerateOutput("%s %s %s",currentDir->d_name,result,_pipeMessage) < 0)
	execFsroErrorBC(fsroError);
      else
	cout<<_alignmentCharacters<<_outputContents;

       if (ifAdir(fullPath))
	fsroMain(fullPath);
      else;

    nextcycle:

      fsroError=FSRO_SUCCESS;
      cStringErase(fullPath,'/');
      if (fsroError != FSRO_SUCCESS)
	execFsroErrorBC(fsroError);

    }

    closedir(dirPtr);

    // reset for parent
    _alignmentCharacters.erase(_alignmentCharacters.begin()+_alignmentCharacters.length()-1);

  }

  int Fsro::fsroExec(char *target){
    int termOut=-1;	// Save standard output
    int statusloc=-1;
    pid_t forkReturn=-1;
    ssize_t readcount=0;
    ssize_t posoffset=0;

    // pipe should be open at the time that was necessary
    if (pipe(_pipeFD) < 0)
      execFsroErrorBC(FSRO_PIPEOPENFAIL);
    else;

    termOut=dup(STDOUT_FILENO);
    dup2(_pipeFD[1],STDOUT_FILENO);	// Open new pipe fd that would use by exec program
    _operationPara[_targetIndexOfexec]=target;

    if ((forkReturn=fork()) < 0)
      execFsroErrorBC(FSRO_FORKFAULT);
    else if (forkReturn != 0){

      // if dont close these fds,read() will trap into block even child exit
      (void)close(_pipeFD[1]);
      (void)close(STDOUT_FILENO);

      // read pipe,if child stop,pipe would returns EOF at last
      while ((readcount=read(_pipeFD[0],_pipeMessage+posoffset,_pipeSize-posoffset)) > 0)
	posoffset+=readcount;
      
      if (readcount < 0)
	execFsroErrorBC(FSRO_PIPEREADINGERR);
      else;

      if (wait(&statusloc) < 0)
	execFsroErrorBC(FSRO_CPEXCEPTION);
      else;
    }
    else{
      (void)close(_pipeFD[0]);			// child process doesnt read pipe
      execv(_operationExec,_operationArgs);	// child process exec
    }

    (void)close(_pipeFD[0]);

    dup2(termOut,STDOUT_FILENO);	// reset standard output

    if (WIFEXITED(statusloc))
      return WEXITSTATUS(statusloc);
    else
      execFsroErrorBC(FSRO_CPEXCEPTION);

  }

  void Fsro::fsroErrorBroadcast(void){

    switch (fsroError){
    case CFG_NOTEXISTEDORDENYPERMISSION:
      cerr<<"The config file had not be existed or deny accessing."<<endl;
      break;
    case CFG_OPENFAIL:
      cerr<<"Open config file failed."<<endl;
      break;
    case CFG_READFAIL:
      cerr<<"Read config file failed."<<endl;
      break;
    case OPERATION_NOTEXISTEDORDENYPERMISSION:
      cerr<<"The operating file had not be existed or deny accessing."<<endl;
      break;
    case STR_DESNULL:
      cerr<<"Copy a string to a NULL position."<<endl;
      break;
    case STR_NOFINDSUB:
      cerr<<"Had not find the substring from target string.This is possible cause path error."<<endl;
      break;
    case STR_APPENDFAULT:
      cerr<<"Failed while append a string to another."<<endl;
      break;
    case ACCESS_LIMITFAULT:
      cerr<<"Program cant search system limit."<<endl;
      break;
    case FSRO_PIPEOPENFAIL:
      cerr<<"Failed to open a pipe."<<endl;
      break;
    case FSRO_MEMAPPLYFAULT:
      cerr<<"Failed to apply memory for any buffer."<<endl;
      break;
    case FSRO_CANTCOPY:
      cerr<<"Dont use the copy-constractor in source code."<<endl;
      break;
    case FSRO_OPENDIRFAULT:
      cerr<<"Failed to open a directory.It's could be deny permission or program error."<<endl;
      break;
    case FSRO_NOTINITED:
      cerr<<"Program had not be initialized."<<endl;
      break;
    case FSRO_FORKFAULT:
      cerr<<"Fork a child process was failed."<<endl;
      break;
    case FSRO_PIPEREADINGERR:
      cerr<<"Read pipe appearance an error or retrieved nothing."<<endl;
      break;
    case FSRO_CPEXCEPTION:
      cerr<<"The process that exec the operation had not normally to exit."<<endl;
      break;
    case MAKEOUTPUT_FAULT:
      cerr<<"Program cant make output messages."<<endl;
      break;
    case FILTER_CANTGETFILEINFO:
      cerr<<"Cant get file info."<<endl;
      break;
    case FILTER_UNKNOWN:
      cerr<<"Unknown filter match pattern."<<endl;
      break;
    default:
      cerr<<"Unknown error."<<endl;
    }

    _exit(fsroError);

  }
  
  /* fsroFilter() would checks the global variable value for select which pattern to test.
     That variable value will be assigned by command option.
  */

  int Fsro::fsroFilter(const char *fullpath){
    struct stat filestat={0};
    if (lstat(fullpath,&filestat) < 0)
      execFsroErrorBC(FILTER_CANTGETFILEINFO);
    else
      switch (_fsrofilter){
      case REGULAR:
	return S_ISREG(filestat.st_mode);
      case DIRECTORY:
	return S_ISDIR(filestat.st_mode);
      case SOCKET:
	return S_ISSOCK(filestat.st_mode);
      case CHAR_DEVICE:
	return S_ISCHR(filestat.st_mode);
      case BLOCK_DEVICE:
	return S_ISBLK(filestat.st_mode);
      case FIFO:
	return S_ISFIFO(filestat.st_mode);
      default:
	return 0;
      }

  }

  void Fsro::fsroSetFilterMode(int WHICH){
    switch (WHICH){
    case REGULAR: _fsrofilter=REGULAR; break;
    case DIRECTORY: _fsrofilter=DIRECTORY; break;
    case SOCKET: _fsrofilter=SOCKET; break;
    case CHAR_DEVICE: _fsrofilter=CHAR_DEVICE; break;
    case BLOCK_DEVICE: _fsrofilter=BLOCK_DEVICE; break;
    case FIFO: _fsrofilter=FIFO; break;
    default:
      execFsroErrorBC(FILTER_UNKNOWN);
    }
  }


}

static int
ifAdir(const char *path){
  struct stat temp={0};
  if (lstat(path,&temp) < 0){
    fprintf(stderr,"Failed to get item stat structe!\n");
    _exit(-1);
  }
  else;
  return S_ISDIR(temp.st_mode);  
}
