#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "affichage.h"
#include "jeu.h"

int main() {
  srand(time(NULL));

  int run = 1;

  do {
    startJeu();

    run = -1;
    printf("\nVoulez-vous rejouer une nouvelle partie ?\nChoix disponibles : Non (0) Oui (1)\n");
    do {
      printf("  Votre choix : ");
      scanfD(&run);
    } while (run < 0 || run > 1);
  } while (run);

  return 0;
}