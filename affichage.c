#include "affichage.h"
#include <stdio.h>
#include <stdlib.h>

void affRentrerEcurie(cheval_Struct cheval, char* couleursS[]) {
  printf("Le cheval %s n°%d a été renvoyé à l'écurie\n", couleursS[cheval.couleur], cheval.numero + 1);
}

void affActions(int tirage, int couleurJouer, cheval_Struct chevaux[4][4]) {
  int nbChevalEc = nbChevalEcurie(couleurJouer, chevaux);

  printf("  Vous avez tiré le nombre %d\n", tirage);
  printf("  Choix disponibles: ");
  printf("Ne rien faire (0)  ");

  if (nbChevalEc >= 1 && tirage >= 6)
    printf("Sortir un cheval (1)  ");

  if (nbChevalEc < 4)
    printf("Déplacer un cheval (2)  ");

  printf("Sauvegarder et quitter (3)");
}

void affChevaux(int couleurJouer, cheval_Struct chevaux[4][4], int horsEcurie) {
  for (int iCheval = 0; iCheval < 4; iCheval++) {
    cheval_Struct chev = chevaux[couleurJouer][iCheval];

    if ((horsEcurie && chev.deplacement >= 0) || (!horsEcurie && chev.deplacement < 0))
      printf("%d ", iCheval + 1);
  }

  printf("\n");
}

void affPlateau(int couleurJouer,
                int plateau[TPLATEAU][TPLATEAU],
                cheval_Struct chevaux[4][4],
                int unDimTo2DM[TOUR_MAX + 1][2]) {
  cheval_Struct placement[TPLATEAU][TPLATEAU];
  chevauxTo2D(placement, chevaux, unDimTo2DM);

  printf("\n");

  for (int lig = 0; lig < TPLATEAU; lig++) {
    for (int col = 0; col < TPLATEAU; col++) {
      setCouleur(lig, col);

      int typeCase = plateau[lig][col];
      cheval_Struct chev = placement[lig][col];

      if (typeCase >= 0 && typeCase <= 8) {
        // Si c'est une case vide
        if (chev.numero == -1) {
          if (typeCase == 0 || typeCase == 7) {
            if (typeCase == 0)
              printf(GREY);
            printf("*");
          } else if (typeCase >= 1 && typeCase <= 6)
            printf("%d", typeCase);
          else
            printf(" ");
        }

        // Si ce n'est pas une case vide
        else {
          affCouleur(chev.couleur);

          if (chev.deplacement == -1 || couleurJouer == (int)chev.couleur) {
            if (chev.deplacement > TOUR_MAX)
              printf(WHITE);

            printf("%d", chev.numero + 1);
          } else {
            if (chev.couleur == 0)
              printf("J");
            else if (chev.couleur == 1)
              printf("B");
            else if (chev.couleur == 2)
              printf("R");
            else if (chev.couleur == 3)
              printf("V");
          }
        }
      } else
        printf(" ");

      printf(" ");
    }

    printf("\n");
  }

  printf(WHITE);
}

void setCouleur(int lig, int col) {
  if (lig < 8 && col < 7)
    printf(YELLOW);
  else if (lig >= 8 && col <= 7)
    printf(GREEN);
  else if (lig < 7 && col >= 7)
    printf(BLUE);
  else if (lig >= 7 && col > 7)
    printf(RED);

  if (lig == 7 && col == 7)
    printf(WHITE);
}

void affCouleur(int couleur) {
  if (couleur == 0)
    printf(YELLOW);
  else if (couleur == 1)
    printf(BLUE);
  else if (couleur == 2)
    printf(RED);
  else if (couleur == 3)
    printf(GREEN);
  else
    printf(WHITE);
}

void scanfD(int* entier) {
  int retour = scanf("%d", entier);

  if (retour < 1) {
    char* poubelle = malloc(32);
    scanf("%s", poubelle);
    free(poubelle);
  }
}