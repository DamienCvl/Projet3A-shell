#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "../include/mv.h"
#include "../utils/macro_main.h"

MAIN(cp)

int cp(int argc, char *argv[]) {
  if (argc != 2) {
    perror("Bad use");
    return -1;
  }

  FILE* Fsource = NULL;
  FILE* Fdestination = NULL;
  int currentChar;


  if ((Fsource = fopen(argv[0], "r")) == NULL) {
    printf("%s, %s\n", argv[0], strerror(errno));
    return 1;
  }

  if ((Fdestination = fopen(argv[1], "w+")) == NULL) {
    printf("%s, %s\n", argv[1], strerror(errno));
    return 1;
  }

  while ((currentChar = fgetc(Fsource)) != EOF) {
    fputc(currentChar, Fdestination);
  }

  fclose(Fsource);
  remove(Fsource);
  fclose(Fdestination);
  return 0;
}
