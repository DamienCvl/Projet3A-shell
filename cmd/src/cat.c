#include <stdio.h>
#include "../include/cat.h"

#ifdef CREATE_MAIN
#include "../include/macro_main.h"
MAIN(cat)
#endif

int cat(int argc, char *argv[]) {
  return 0;
}
