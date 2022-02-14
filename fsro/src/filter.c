#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
int fsroFilterDir(const char *path){
  struct stat temp={0};
  if (lstat(path,&temp) < 0)
    return 0;
  else;
  return S_ISDIR(temp.st_mode);  
}
