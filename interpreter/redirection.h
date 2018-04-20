#ifdef _REDIRECTION_H_
#define _REDIRECTION_H_

  int redirectionCommandeVersCommande(char *entree, char *sortie);
  int redirectionCommandeVersFichierEnAjout(char *entree, char *sortie);
  int redirectionCommandeVersFichierEnEcrasant(char *entree, char *sortie);
  int redirectionFichierVersCommande(char *entree, char *sortie);
  int redirectionClavierVersCommande(char *entree, char *sortie);

#endif
