#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "../include/cat.h"
#include "../utils/argument.h"
#include "../utils/macro_main.h"

MAIN(cat)

int cat(int argc, char *argv[]) {
  FILE *file;
  char c;
  if (argc >= 1) {
    char *filename = argv[0];

    file = fopen(filename,"r");

    if (!file) {
        printf("cat: %s: %s\n", filename, strerror(errno));
        return(-1);
    }
  }
  else {
    file = stdin;
  }

  while (!feof(file)) {
    c = fgetc(file);
    printf("%c", c);
  }

  fclose(file);
  return(0);
}
