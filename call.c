#include <stdio.h>
#include <string.h>

int call(int argc, char *argv[]) {
    char *cmd = argv[0];
    
    #ifdef identifier  
        char path[80];
		strcpy(path, cmd);
		strcat(path, ".exe");
  	    execv(path,argv + 1);
    #elif 

    #else

    #endif

}