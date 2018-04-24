#ifndef _REDIRECTION_H_
#define _REDIRECTION_H_

  int redirectionCommandeVersCommande(int argcEntree, char *argvEntree[], int argcSortie, char *argvSortie[]);
  int redirectionCommandeVersFichierEnAjout(int argcEntree, char *argvEntree[], int argcSortie, char *argvSortie[]);
  int redirectionCommandeVersFichierEnEcrasant(int argcEntree, char *argvEntree[], int argcSortie, char *argvSortie[]);
  int redirectionFichierVersCommande(int argcEntree, char *argvEntree[], int argcSortie, char *argvSortie[]);
  int redirectionClavierVersCommande(int argcEntree, char *argvEntree[], int argcSortie, char *argvSortie[]);

#endif
