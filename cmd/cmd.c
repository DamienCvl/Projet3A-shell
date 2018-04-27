#ifdef INTEGRATED_FUNCTION

#include <string.h>
#include "cmd.h"

// Répertorisation de toutes les fonctions de commande
#include "include/echo.h"
#include "include/pwd.h"
#include "include/cat.h"
#include "include/cd.h"
#include "include/rm.h"
#include "include/ls.h"
#include "include/chmod.h"
#include "include/cp.h"
#include "include/mv.h"
#include "include/makedir.h"

int NB_CMD = 10;
cmd_t CMD_FUNCTIONS[] = {echo, pwd, cat, cd, rm, ls, chmod, cp, mv, makedir};
char *CMD_NAMES[] = {"echo", "pwd", "cat", "cd", "rm", "ls", "chmod", "cp", "mv", "makedir"};

// Récupération d'une fonction de commande à partir de son nom
// Si le nom renseigné est dans la liste ci-dessus : on retourne sa fonction respective
cmd_t getCmd(char *name) {
    for (int i = 0; i < NB_CMD; i++) {
        if (strcmp(name, CMD_NAMES[i]) == 0) {
            return CMD_FUNCTIONS[i];
        }
    }
    return NULL;
}

#endif
