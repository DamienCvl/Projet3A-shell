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
    if (mkdir(argv[0], 0777) == -1) {
        printf("%s, %s\n", argv[0], strerror(errno));
        return 1;
    }
    return 0;
}
