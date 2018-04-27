# Projet Mini-Shell

## Présentation
Ce projet a pour objectif de recréer un Shell (quelques fonctionnalités de base) et  le langage C.

La contrainte de pouvoir utiliser les commandes du Mini-Shell sous 3 formes, nous a été imposée :
- Exécutables indépendants
- Intégrées à l'exécutable de l'interpreteur de commande
- Librairies

## Utilisation
### Génération des exécutables
Pour tester notre application, il faut d'abord générer les exécutables grâce à la commande `make`.

Il est possible de générer seulement les parties souhaitées :
- `make as_executable` génère tous les exécutables des commandes, ainsi que l'exécutable de l'interpreteur correspondant
- `make as_integrated_function` génère l'interpreteur de commande avec les fonctions de commandes intégrées
- `make as_library` génère les librairies (fichiers ".so"), ainsi que l'exécutable de l'interpreteur correspondant

Pour executer le Mini-Shell dans l'un des trois, il suffit de taper la commande suivante dans le terminal :

> Lorsque l'on est placé à la racine du projet

- `./asExecutable`
- `./asIntegratedFunction`
- `./asLibrary`


Pour quitter le Mini-Shell il faut taper `exit`.

`make clean` afin d'effacer tous les fichiers générés.

## Membres du groupe
Yves LE PALUD

Damien CHEVALERIAS

Bastien CHUPIN

Johan SORETTE