#include <stdio.h>
#include "../include/rm.h"
#include "../utils/macro_main.h"

MAIN(rm)

int rm(int argc, char *argv[]) {
    if (argc < 1) {
        printf("rm: missing operand\n");
    }
    else {
        char *filename = argv[0];

        if (remove(filename) != 0) {
            printf("rm: cannot remove '%s': No such file or directory\n", filename);
        }
    }
    return 0;
}
