#ifndef _ARGUMENT_
#define _ARGUMENT_

  typedef enum ArgumentTypes {
    UNIQ = 1,
    MULTI = 2,
    PATH = 3,
    INVALID = 0
  }ArgumentTypes;

  typedef struct Argument {
    ArgumentTypes type;
    char* data;
    int dataSize;
  }Argument;

  Argument whichArgument(char argv[]);
  Argument* readArguments(int argc, char *argv[]);

#endif
