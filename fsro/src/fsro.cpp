
/* Name: fsro.cpp
 * Type: C++ program code file
 * Description: Main file of fsro.
 * Header: "fsro.h"
 * Function prototype:
 * Last modified date:
 * Fix:
 */

 /* Feature */
 /* Header */
#include"fsro.h"
using namespace fsrospace;
 /* Macro */
 /* Data */
 /* Function */

int main(int argc,char *argv[]){

  Fsro fsromain;	// Create class object
  fsromain.fsroSetFilterMode(REGULAR);		// This is default pattern

  if (argc < 2) {
    cerr<<"must select filter mode."<<endl;
    return 1;
  }
  else {

    // options resolving

    int getoptreturn=0;
    while ((getoptreturn=getopt(argc,argv,"nhm:")) != -1)
      switch ((char)getoptreturn) {
      case 'n':
	if (dup2(open("/dev/null",O_WRONLY),STDOUT_FILENO) < 0){
	  fprintf(stderr,"Set silent mode was failed.\n");
	  return -1;
	}
	break;

      case 'h':
	fsromain.fsroHelp();
	return 0;

      case 'm':
	if (strcmp(optarg,"regular") == 0)
	  fsromain.fsroSetFilterMode(REGULAR);
	else if (strcmp(optarg,"directory") == 0)
	  fsromain.fsroSetFilterMode(DIRECTORY);
	else if (strcmp(optarg,"socket") == 0)
	  fsromain.fsroSetFilterMode(SOCKET);
	else if (strcmp(optarg,"chardev") == 0)
	  fsromain.fsroSetFilterMode(CHAR_DEVICE);
	else if (strcmp(optarg,"blockdev") == 0)
	  fsromain.fsroSetFilterMode(BLOCK_DEVICE);
	else if (strcmp(optarg,"fifo") == 0)
	  fsromain.fsroSetFilterMode(FIFO);
	else {
	  cerr<<"Unknown filter pattern."<<endl;
	  return -1;
	}

	break;

      default:
	cerr<<"Unknown option "<<optopt<<endl;
      }
  }

  fsromain.fsroInit();
  fsromain.fsroStartWork();

  return 0;
}

