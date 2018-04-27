#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "../include/rm.h"
#include "../utils/macro_main.h"

MAIN(rm)

int rm(int argc, char *argv[]) {
    if (argc < 1) {
        printf("rm: missing operand\n");
        return -1;
    }

    char *filename = argv[0];
    if (remove(filename) != 0) {
        printf("rm: cannot remove '%s': %s\n", filename, strerror(errno));
        return -1;
    }
    return 0;
}
