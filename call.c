#include <stdio.h>
#include <string.h>

int exeExists(char arg) {
  
}

int fctExists() {
  
}

int libExists() {
  
}


int call(int argc, char *argv[]) {
  char *cmd = argv[0];
	if (exeExists(cmd)) {
    char path[80];
		strcpy(path, cmd);
		strcat(path, ".exe");
  	execv(path,argv + 1);
  }
  else if (fctExists()) {
    
  }
  else if (libExists()) {
	    
  }
  else {
    return -1;
  }
}