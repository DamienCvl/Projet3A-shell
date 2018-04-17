#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "argument.h"

Argument whichArgument(char argv[]){

  Argument argum;
  int n = strlen(argv), i;

  if (n > 2 && argv[0] == '-' && argv[1] == '-' && argv[2] != '-') {
    i = 2;
    argum.type = UNIQ;
  }
  else if (n > 1 && argv[0] == '-' && argv[1] != '-') {
    i = 1;
    argum.type = MULTI;
  }
  else if (n >= 1 && argv[0] != '-'){
    i = 0;
    argum.type = PATH;
  }
  else {
    i = 0;
    argum.type = INVALID;
  }
  argum.dataSize = n-i;
  argum.data = malloc((n-i)*sizeof(char));
  int x = i;
  for (i; argv[i] != '\0'; ++i)
    argum.data[i-x] = argv[i];
  argum.data[i-x]= '\0';
  return argum;
}

Argument* readArguments(int argc, char *argv[]) {
  Argument* argums;
  argums = malloc(argc*sizeof(Argument));
  for (int i = 0; i < argc; i++){
    argums[i] = whichArgument(argv[i]);
  }
  return argums;
}
