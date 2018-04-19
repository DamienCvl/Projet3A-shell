#include <stdio.h>
#include "../include/cat.h"
#include "../utils/argument.h"
#include "../utils/macro_main.h"

MAIN(cat)

int cat(int argc, char *argv[]) {
  FILE *f0;
  char *targetPath = argv[0];
  char line[1000] = "";
  char *notEndFile;
  
  f0 = fopen(targetPath,"r");
  if (f0) {
    do {
      printf("%s", line);
      notEndFile = fgets(line, 1000, f0);
    } while(notEndFile);
  }
  else {
    printf("cat: %s: No such file or directory",targetPath);
  }
  fclose(f0);
  return(0);
}
