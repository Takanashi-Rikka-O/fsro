#include<iostream>
#include<cstring>
#include"base64.h"

using namespace std;
using namespace base64;
static char buffer_out[1024];


int main(int argc,char *argv[]){


  if (argc < 3)
    return 1;

  const char *arg = argv[2];

  if (strcmp(argv[1],"e") == 0) {
    if (arg != NULL)
      cout<<base64_encode(arg,buffer_out,1024)<<endl;
    else
      return 1;

  } else if (strcmp(argv[1],"d") == 0) {
    if (arg!= NULL)
      cout<<base64_decode(arg,buffer_out,1024)<<endl;
    else
      return 1;
  }
  else
    cerr<<"Usage: base64 [ -e | -d ] arg"<<endl;


  return 0;
}
