#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include "../utils/macro_main.h"
#include "../include/makedir.h"

MAIN(makedir)

int makedir(int argc, char *argv[]) {
    if (argc < 1) {
        perror("makedir: missing operand");
        return -1;
    }

    char *filename = argv[0];
    if (mkdir(filename, 0777) != 0) {
        printf("makedir: %s: %s\n", filename, strerror(errno));
        return -1;
    }
    return 0;
}
