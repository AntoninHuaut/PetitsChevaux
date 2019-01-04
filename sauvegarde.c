#include "sauvegarde.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "affichage.h"

int choixSave(int* couleurJoueur, joueur_Struct joueurs[], cheval_Struct chevaux[4][4]) {
  int action = -1;
  int hasSauvegarde = fichierExiste();

  printf("Que souhaitez-vous faire ?\nChoix disponibles : Nouvelle partie (0) ");
  if (hasSauvegarde)
    printf("Charger une sauvegarde classique (1) ");
  printf("Charger une sauvegarde pré-configurée (2)\n");

  do {
    printf("  Votre choix : ");
    scanfD(&action);
  } while (action < 0 || action > 2 || (action == 1 && !hasSauvegarde));

  if (action == 1) {
    int slot = choixSlot(1);
    chargeNormalSav(slot, couleurJoueur, joueurs, chevaux);
  }

  else if (action == 2) {
    int save = 0;

    printf("\nQuelle sauvegarde pré-configurée souhaitez-vous charger ?\nChoix disponibles: 1  2  3\n");
    do {
      printf("  Votre choix : ");
      scanfD(&save);
    } while (save < 1 || save > 3);

    chargePreSav(save, chevaux);
  }

  return action;
}

void chargePreSav(int save, cheval_Struct chevaux[4][4]) {
  for (int joueur = 0; joueur < 4; joueur++) {
    for (int cheval = 0; cheval < 4; cheval++) {
      if (save == 3)
        chevaux[joueur][cheval].deplacement = 58 + cheval;
      else
        chevaux[joueur][cheval].deplacement = -1;
    }

    if (save == 1) {
      chevaux[joueur][2].deplacement = 3;
      chevaux[joueur][3].deplacement = 19;
    }

    else if (save == 2) {
      chevaux[joueur][0].deplacement = 54;
      chevaux[joueur][1].deplacement = 58;
    }

    if (save == 3)
      chevaux[joueur][0].deplacement = 57;
  }

  printf("\nLa sauvegarde pré-configurée %d a bien été chargée\n", save);
}

int choixSlot(int saveType) {
  int slot = -1;

  if (!saveType) {
    printf("\nSur quel emplacement souhaitez-vous sauvegarder ?");
    affCouleur(2);
    printf("\n  [x] = Occupé");
    affCouleur(-1);
    printf(" (possible d'écraser) ");
    affCouleur(3);
    printf("\n  [x] = Disponible \n");
    affCouleur(-1);
  } else
    printf("\nQuel emplacement de sauvegarde souhaitez-vous charger ?");

  printf("\nChoix disponibles: ");

  affSlotDispo(saveType);
  do {
    printf("  Votre choix : ");
    scanfD(&slot);
  } while (slot < 1 || slot > SLOT_MAX || (saveType && !slotChargeable(slot)));

  return slot - 1;
}

void affSlotDispo(int saveType) {
  sauvegarde sav[SLOT_MAX];
  getNormalSav(sav);

  for (int i = 0; i < SLOT_MAX; i++) {
    if (sav[i].couleurJoueur == -1 && saveType)
      continue;

    int couleur = 3;
    if (sav[i].couleurJoueur != -1 && !saveType)
      couleur = 2;

    affCouleur(couleur);
    printf("[%d] ", i + 1);
    affCouleur(-1);
  }

  printf("\n");
}

int slotChargeable(int slot) {
  sauvegarde sav[SLOT_MAX];
  getNormalSav(sav);
  int retour = 1;

  for (int i = 0; i < SLOT_MAX && retour; i++)
    if (sav[i].couleurJoueur == -1 && i == slot - 1)
      retour = 0;

  return retour;
}

void saveNormal(int slot, int couleurJoueur, joueur_Struct joueurs[], cheval_Struct chevaux[4][4]) {
  sauvegarde sav[SLOT_MAX];

  getNormalSav(sav);
  sav[slot].couleurJoueur = couleurJoueur;

  for (int boucleJoueur = 0; boucleJoueur < 4; boucleJoueur++) {
    sav[slot].joueurs[boucleJoueur] = joueurs[boucleJoueur];

    for (int boucleCheval = 0; boucleCheval < 4; boucleCheval++)
      sav[slot].chevaux[boucleJoueur][boucleCheval] = chevaux[boucleJoueur][boucleCheval];
  }

  FILE* fichier = fopen(FICHIER_SAV, "wb");
  sauvegardeList savList;
  for (int i = 0; i < SLOT_MAX; i++)
    savList.sav[i] = sav[i];
  fwrite(&savList, sizeof(savList), 1, fichier);
  fclose(fichier);

  printf("\nVotre partie a été sauvegardée avec succès sur l'emplacement %d > [entrer]", slot + 1);

  do {
    do {
    } while (getchar() != '\n');
  } while (getchar() != '\n');

  exit(0);
}

void getNormalSav(sauvegarde sav[]) {
  if (fichierExiste()) {
    FILE* fichier = fopen(FICHIER_SAV, "rb");
    sauvegardeList savList;
    fread(&savList, sizeof(savList), 1, fichier);
    fclose(fichier);

    for (int i = 0; i < SLOT_MAX; i++)
      sav[i] = savList.sav[i];
  } else
    for (int i = 0; i < SLOT_MAX; i++)
      sav[i].couleurJoueur = -1;
}

void chargeNormalSav(int slot, int* couleurJoueur, joueur_Struct joueurs[], cheval_Struct chevaux[4][4]) {
  sauvegarde sav[SLOT_MAX];

  if (fichierExiste()) {
    getNormalSav(sav);
    *couleurJoueur = sav[slot].couleurJoueur;

    for (int boucleJoueur = 0; boucleJoueur < 4; boucleJoueur++) {
      joueurs[boucleJoueur] = sav[slot].joueurs[boucleJoueur];

      for (int boucleCheval = 0; boucleCheval < 4; boucleCheval++)
        chevaux[boucleJoueur][boucleCheval] = sav[slot].chevaux[boucleJoueur][boucleCheval];
    }

    printf("\nLa sauvegarde de l'emplacement %d a bien été chargée\n", slot + 1);
  } else
    printf("\nUne erreur est survenue pendant le chargement de la sauvegarde\n");
}

int fichierExiste() {
  FILE* fichier;
  if ((fichier = fopen(FICHIER_SAV, "r"))) {
    fclose(fichier);
    return 1;
  }

  return 0;
}