#include <stdio.h>
#include "../include/cat.h"
#include "../utils/argument.h"
#include "../utils/macro_main.h"

MAIN(cat)

int cat(int argc, char *argv[]) {
// FONCTION QUI N'A RIEN A VOIR AVEC CAT, UTILISER POUR TESTER ARGUMENT.C
  Argument* arguments = readArguments(argc, argv);
  char* str;

  for (int i = 0; i < argc; i++){
    switch (arguments[i].type) {
      case INVALID: {
        str = "INVALID";
        break;
      }
      case UNIQ: {
        str = "UNIQ";
        break;
      }
      case MULTI: {
        str = "MULTI";
        break;
      }
      case PATH: {
        str = "PATH";
        break;
      }
    }
    printf("---------------------------\n");
    printf("Argument : %d\n", i+1);
    printf("type : %s\n", str);
    printf("data : %s\n", arguments[i].data);
    printf("dataSize : %d\n", arguments[i].dataSize);
  }

  return 0;
}
