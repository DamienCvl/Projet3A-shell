#include <stdio.h>
#include "../include/cat.h"
#include "../utils/argument.h"
#include "../utils/macro_main.h"

MAIN(cat)

int cat(int argc, char *argv[]) {
  FILE *file;
  char *filename = argv[0];
  char c;

  file = fopen(filename,"r");

  if (!file) {
      printf("cat: %s: No such file or directory\n", filename);
      return(-1);
  }

  while (!feof(file)) {
    c = fgetc(file);
    printf("%c", c);
  }

  fclose(file);
  return(0);
}
