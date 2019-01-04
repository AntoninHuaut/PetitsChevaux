#include "jeu.h"

#include <stdio.h>
#include <stdlib.h>
#include "affichage.h"
#include "plateau.h"
#include "sauvegarde.h"

void startJeu() {
  int couleurJouer = -1;
  int couleurWin = -1;

  char* couleursS[] = {"Jaune", "Bleu", "Rouge", "Vert"};

  joueur_Struct joueurs[4];
  cheval_Struct chevaux[4][4];  // 1e liste: joueur - 2e liste: les chevaux de
                                // chaque joueur
  int plateau[TPLATEAU][TPLATEAU];
  int unDimTo2DM[TOUR_MAX + 1][2];

  initPlateau(plateau, unDimTo2DM);

  int saveChargee = choixSave(&couleurJouer, joueurs, chevaux);
  if (saveChargee != 1)
    initJeu(saveChargee, couleursS, joueurs, chevaux, &couleurJouer);

  affCouleur(couleurJouer);
  printf("\nC'est la couleur %s qui commence ! \n", couleursS[couleurJouer]);
  affCouleur(-1);
  printf("Démarrage du jeu... > [entrer]\n");

  do {
  } while (getchar() != '\n');

  while (couleurWin == -1) {
    affCouleur(couleurJouer);
    printf("\nA vous de jouer %s (%s) > [entrer]", joueurs[couleurJouer].pseudo, couleursS[couleurJouer]);
    affCouleur(-1);
    do {
    } while (getchar() != '\n');

    system("clear");
    affPlateau(couleurJouer, plateau, chevaux, unDimTo2DM);

    int tirage = 0;

    do {
      if (tirage >= 6) {
        affPlateau(couleurJouer, plateau, chevaux, unDimTo2DM);
        printf("\n  Vous aviez fait 6, vous obtenez la possibilité de rejouer !\n\n");
      }

      tirage = choixAction(&couleurJouer, joueurs, chevaux, couleursS);
    } while (tirage >= 6);

    do {
    } while (getchar() != '\n');

    if (aJoueurGagnant(couleurJouer, chevaux))
      couleurWin = couleurJouer;
    else
      couleurJouer = (couleurJouer + 1) % 4;
  }

  affCouleur(couleurWin);
  printf("\nLe joueur %s (%s) a gagné la partie !\n", joueurs[couleurWin].pseudo, couleursS[couleurWin]);
  affCouleur(-1);
}

void initJeu(int saveChargee, char* couleursS[], joueur_Struct joueurs[], cheval_Struct chevaux[4][4], int* couleurJouer) {
  printf("\nPréparation des joueurs... \n");
  for (int i = 0; i < 4; i++) {
    affCouleur(i);
    printf("  Joueur: %s \n", couleursS[i]);
    affCouleur(-1);
    printf("  Entrer votre pseudo: ");
    affCouleur(i);
    scanf("%s", joueurs[i].pseudo);
    affCouleur(-1);

    joueurs[i].couleur = JAUNE + i;
    do {
    } while (getchar() != '\n');

    for (int j = 0; j < 4; j++) {
      chevaux[i][j].couleur = joueurs[i].couleur;
      chevaux[i][j].numero = j;

      if (!saveChargee)
        chevaux[i][j].deplacement = -1;
    }

    printf("\n");
  }

  *couleurJouer = tirageCouleur();
}

int tirageCouleur() {
  return rand() % 4;
}