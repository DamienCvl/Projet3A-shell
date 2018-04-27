#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "../include/cp.h"
#include "../utils/macro_main.h"

MAIN(cp)

int cp(int argc, char *argv[]) {
  //On s'assure de la bonne utilisation de la commande
    if (argc < 2) {
        perror("cp: missing file operand");
        return -1;
    }

    FILE* fileSource = NULL;
    FILE* fileDestination = NULL;
    int currentChar;

    //On essaye d'ouvrir le fichier à copier en lecture uniquement
    if ((fileSource = fopen(argv[0], "r")) == NULL) {
        printf("%s, %s\n", argv[0], strerror(errno));
        return -1;
    }

    //On crée la copie du fichier si il n'existe pas sinon on l'écrase
    if ((fileDestination = fopen(argv[1], "w+")) == NULL) {
        printf("%s, %s\n", argv[1], strerror(errno));
        return -1;
    }

    //On lit le contenu du fichier source et on écrit dans le fichier
    while ((currentChar = fgetc(fileSource)) != EOF) {
        fputc(currentChar, fileDestination);
    }

    fclose(fileSource);
    fclose(fileDestination);
    return 0;
}
