#include "joueur.h"

#include <stdio.h>
#include <stdlib.h>
#include "affichage.h"
#include "sauvegarde.h"

#define DEE_MAX 6
#define DEE_MIN 1

int actionEstDispo(int action, int tirage, int couleurJouer, cheval_Struct chevaux[4][4]) {
  int nbChevalEc = nbChevalEcurie(couleurJouer, chevaux);

  return ((action == 1 && nbChevalEc >= 1 && tirage >= 6) || (action == 2 && nbChevalEc < 4) || action == 0 || action == 3 ||
          action == 30);
}

int chevalEstDispo(int chevalPosition, int couleurJouer, cheval_Struct chevaux[4][4], int horsEcurie) {
  int resultat = 1;
  int depRelatif = chevaux[couleurJouer][chevalPosition].deplacement;

  if (chevalPosition < 0 || chevalPosition > 3 || (horsEcurie && depRelatif == -1) || (!horsEcurie && depRelatif >= 0))
    resultat = -1;

  return resultat == 1;
}

int choixAction(int* couleurJouer, joueur_Struct joueurs[4], cheval_Struct chevaux[4][4], char* couleursS[]) {
  int tirage = tirageDe();
  affActions(tirage, *couleurJouer, chevaux);
  int action = -1;

  printf("\n");

  do {
    if (action == 30) {
      printf("    Mode développeur\n");
      printf("      Tirage: ");
      scanfD(&tirage);
      affActions(tirage, *couleurJouer, chevaux);
      printf("\n");
    }

    printf("    Votre choix: ");
    scanfD(&action);
  } while (!actionEstDispo(action, tirage, *couleurJouer, chevaux) || action == 30);

  if (action == 3) {
    int slot = choixSlot(0);
    saveNormal(slot, *couleurJouer, joueurs, chevaux);
  }

  else if (action != 0) {
    action--;
    int chevalPosition;

    printf("  Choisissez le cheval (via son numéro) : ");
    affChevaux(*couleurJouer, chevaux, action);

    do {
      printf("    Votre choix: ");
      scanfD(&chevalPosition);
      chevalPosition--;
    } while (!chevalEstDispo(chevalPosition, *couleurJouer, chevaux, action));

    executeAction(tirage, chevalPosition, *couleurJouer, chevaux, action, couleursS);
  }

  return tirage;
}

void executeAction(int tirage,
                   int chevalPosition,
                   int couleurJouer,
                   cheval_Struct chevaux[4][4],
                   int horsEcurie,
                   char* couleursS[]) {
  cheval_Struct* chev = &(chevaux[couleurJouer][chevalPosition]);

  if (horsEcurie) {
    int retour = avancerCheval(tirage, chev, chevaux, couleursS);

    if (retour)
      printf("  Votre cheval s'est avancé\n");
    else
      printf("  Votre cheval n'a pas pu s'avancer\n");
  } else {
    sortirEcurie(chev, chevaux, couleursS);
    printf("  Votre cheval est sorti de son écurie\n");
  }
}

int aJoueurGagnant(int couleur, cheval_Struct chevaux[4][4]) {
  int win = 1;

  for (int cheval = 0; cheval < 4 && win; cheval++)
    if (chevaux[couleur][cheval].deplacement < TOUR_MAX + 3)
      win = 0;

  return win;
}

int nbChevalEcurie(int couleurJouer, cheval_Struct chevaux[4][4]) {
  int count = 0;

  for (int i = 0; i < 4; i++)
    if (chevaux[couleurJouer][i].deplacement < 0)
      count++;

  return count;
}

int tirageDe() {
  return rand() % (DEE_MAX - DEE_MIN + 1) + DEE_MIN;
}