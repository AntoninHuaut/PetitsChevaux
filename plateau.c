#include "plateau.h"

#include <stdio.h>

void chevauxTo2D(cheval_Struct placement[TPLATEAU][TPLATEAU], cheval_Struct chevaux[4][4], int unDimTo2DM[TOUR_MAX + 1][2]) {
  for (int lig = 0; lig < TPLATEAU; lig++)
    for (int col = 0; col < TPLATEAU; col++) {
      placement[lig][col].numero = -1;
    }

  for (int nJoueur = 0; nJoueur < 4; nJoueur++) {
    for (int nCheval = 0; nCheval < 4; nCheval++) {
      cheval_Struct cheval = chevaux[nJoueur][nCheval];
      int depRelatif = cheval.deplacement;
      int depAbsolu = depRelatifToAbsolu(cheval);

      setCordonnee(depRelatif, depAbsolu, unDimTo2DM, placement, cheval);
    }
  }
}

void setCordonnee(int depRelatif,
                  int depAbsolu,
                  int unDimTo2DM[TOUR_MAX + 1][2],
                  cheval_Struct placement[TPLATEAU][TPLATEAU],
                  cheval_Struct cheval) {
  int x, y;

  // Il est dans le tour du plateau
  if (depRelatif <= TOUR_MAX && depRelatif >= 0) {
    x = unDimTo2DM[depAbsolu][0];
    y = unDimTo2DM[depAbsolu][1];
  }

  // Il est dans les cases du centre ou écurie   de sa couleur
  else {
    switch (cheval.couleur) {
      case 0:  // Jaune
        if (depRelatif == -1) {
          x = 2;
          y = 2;
        } else {
          x = 7;
          y = depRelatif - TOUR_MAX;
        }
        break;

      case 1:  // Bleu
        if (depRelatif == -1) {
          x = 2;
          y = 11;
        } else {
          x = depRelatif - TOUR_MAX;
          y = 7;
        }
        break;

      case 2:  // Rouge
        if (depRelatif == -1) {
          x = 11;
          y = 11;
        } else {
          x = 7;
          y = 14 - (depRelatif - TOUR_MAX);
        }
        break;

      case 3:  // Vert
        if (depRelatif == -1) {
          x = 11;
          y = 2;
        } else {
          x = 14 - (depRelatif - TOUR_MAX);
          y = 7;
        }
        break;
    }
  }

  if (depRelatif == -1)
    switch (cheval.numero) {
      case 1:
        y++;
        break;
      case 2:
        x++;
        break;
      case 3:
        x++;
        y++;
        break;
    }

  placement[x][y] = cheval;
}

void initTab1DTo2D(int unDimTo2DM[TOUR_MAX + 1][2]) {
  for (int x = 0; x < TPLATEAU; x++) {
    for (int y = 0; y < TPLATEAU; y++) {
      if (x == 6 && y < 7) {
        unDimTo2DM[y][0] = x;
        unDimTo2DM[y][1] = y;
      }

      else if (x < 6 && y == 6) {
        unDimTo2DM[6 + (6 - x)][0] = x;
        unDimTo2DM[6 + (6 - x)][1] = y;
      }

      else if (x == 0 && y == 7) {
        unDimTo2DM[13][0] = x;
        unDimTo2DM[13][1] = y;
      }

      else if (x < 7 && y == 8) {
        unDimTo2DM[14 + x][0] = x;
        unDimTo2DM[14 + x][1] = y;
      }

      else if (x == 6 && y > 8) {
        unDimTo2DM[20 + (y - 8)][0] = x;
        unDimTo2DM[20 + (y - 8)][1] = y;
      }

      else if (x == 7 && y == 14) {
        unDimTo2DM[27][0] = x;
        unDimTo2DM[27][1] = y;
      }

      else if (x == 8 && y > 7) {
        unDimTo2DM[34 - (y - 8)][0] = x;
        unDimTo2DM[34 - (y - 8)][1] = y;
      }

      else if (x > 8 && y == 8) {
        unDimTo2DM[35 + (x - 9)][0] = x;
        unDimTo2DM[35 + (x - 9)][1] = y;
      }

      else if (x == 14 && y == 7) {
        unDimTo2DM[41][0] = x;
        unDimTo2DM[41][1] = y;
      }

      else if (x > 7 && y == 6) {
        unDimTo2DM[48 - (x - 8)][0] = x;
        unDimTo2DM[48 - (x - 8)][1] = y;
      }

      else if (x == 8 && y < 6) {
        unDimTo2DM[54 - y][0] = x;
        unDimTo2DM[54 - y][1] = y;
      }

      else if (x == 7 && y == 0) {
        unDimTo2DM[55][0] = x;
        unDimTo2DM[55][1] = y;
      }
    }
  }
}

void initPlateau(int plateau[TPLATEAU][TPLATEAU], int unDimTo2DM[TOUR_MAX + 1][2]) {
  int lig, col;

  for (lig = 0; lig < TPLATEAU; lig++) {
    for (col = 0; col < TPLATEAU; col++) {
      if (lig <= 5 && col <= 5)
        plateau[lig][col] = CASE_ECURIE;  // Ecurie Jaune

      else if (col >= 9 && lig <= 5)
        plateau[lig][col] = CASE_ECURIE;  // Ecurie Bleu

      else if (col <= 5 && lig > 8)
        plateau[lig][col] = CASE_ECURIE;  // Ecurie Vert

      else if (col >= 9 && lig > 8)
        plateau[lig][col] = CASE_ECURIE;  // Ecurie Rouge

      else if ((lig == 1 && col == 7) || (lig == 7 && col == 1) || (lig == 13 && col == 7) || (lig == 7 && col == 13))
        plateau[lig][col] = CASE_1;

      else if ((lig == 2 && col == 7) || (lig == 7 && col == 2) || (lig == 12 && col == 7) || (lig == 7 && col == 12))
        plateau[lig][col] = CASE_2;

      else if ((lig == 3 && col == 7) || (lig == 7 && col == 3) || (lig == 11 && col == 7) || (lig == 7 && col == 11))
        plateau[lig][col] = CASE_3;

      else if ((lig == 4 && col == 7) || (lig == 7 && col == 4) || (lig == 10 && col == 7) || (lig == 7 && col == 10))
        plateau[lig][col] = CASE_4;

      else if ((lig == 5 && col == 7) || (lig == 7 && col == 5) || (lig == 9 && col == 7) || (lig == 7 && col == 9))
        plateau[lig][col] = CASE_5;

      else if ((lig == 6 && col == 7) || (lig == 7 && col == 6) || (lig == 8 && col == 7) || (lig == 7 && col == 8))
        plateau[lig][col] = CASE_6;

      else if (lig == 7 && col == 7)
        plateau[lig][col] = CASE_CENTRE;

      else if ((lig == 0 && col == 8) || (lig == 6 && col == 0) || (lig == 14 && col == 6) || (lig == 8 && col == 14))
        plateau[lig][col] = CASE_SORTIE_ECURIE;

      else
        plateau[lig][col] = NORMAL;
    }
  }

  initTab1DTo2D(unDimTo2DM);
}