#include "cheval.h"
#include "affichage.h"

int avancerChevalFin(int nbDeplacement, cheval_Struct* cheval, cheval_Struct chevaux[4][4]) {
  int retour = 0;
  int caseRetour = 0;

  if (cheval->deplacement + nbDeplacement > CASE_MAX) {
    caseRetour = CASE_MAX - cheval->deplacement;
    caseRetour = nbDeplacement - caseRetour;
  }

  for (int posCheval = 0; posCheval < 4 && retour != -1; posCheval++) {
    cheval_Struct chevalJoueur = chevaux[cheval->couleur][posCheval];

    if (chevalJoueur.numero == cheval->numero)
      continue;

    if (chevalJoueur.deplacement > cheval->deplacement && chevalJoueur.deplacement <= cheval->deplacement + nbDeplacement)
      retour = -1;

    if (cheval->deplacement + nbDeplacement > CASE_MAX)
      if (CASE_MAX > chevalJoueur.deplacement && CASE_MAX - caseRetour <= chevalJoueur.deplacement)
        retour = -1;
  }

  if (!retour) {
    cheval->deplacement += nbDeplacement - caseRetour;

    if (caseRetour > 0)
      cheval->deplacement -= caseRetour;
  }

  return retour;
}

int gestionTransition(int nbDeplacement, cheval_Struct* cheval, cheval_Struct chevaux[4][4]) {
  int depRestantTour = nbDeplacement - (TOUR_MAX - cheval->deplacement) + 1;
  cheval->deplacement += nbDeplacement - depRestantTour;

  int retour = avancerChevalFin(depRestantTour, cheval, chevaux);

  if (retour)
    cheval->deplacement -= nbDeplacement - depRestantTour;

  return retour;
}

int arriveFinTour(int nbDeplacement, cheval_Struct cheval) {
  return cheval.deplacement + nbDeplacement > TOUR_MAX;
}

int chevalSurRoute(int nbDeplacement, cheval_Struct cheval, cheval_Struct chevaux[4][4]) {
  int retour = 0;

  int depDepart = depRelatifToAbsolu(cheval);
  int depFin = depDepart + nbDeplacement;

  for (int nbJoueur = 0; nbJoueur < 4 && retour != -1; nbJoueur++) {
    for (int posCheval = 0; posCheval < 4 && retour != -1; posCheval++) {
      if (chevaux[nbJoueur][posCheval].couleur == cheval.couleur && chevaux[nbJoueur][posCheval].numero == cheval.numero)
        continue;

      if (arriveFinTour(0, chevaux[nbJoueur][posCheval]))
        continue;

      int depEnnemi = depRelatifToAbsolu(chevaux[nbJoueur][posCheval]);

      if (depEnnemi > depDepart && depEnnemi <= depFin) {
        if (depEnnemi == depFin) {
          if (chevaux[nbJoueur][posCheval].couleur != cheval.couleur)
            retour = 1;
        } else
          retour = -1;
      }
    }
  }

  return retour;
}

int avancerCheval(int nbDeplacement, cheval_Struct* cheval, cheval_Struct chevaux[4][4], char* couleursS[]) {
  int retour = 0;

  if (!arriveFinTour(0, *cheval)) {
    retour = chevalSurRoute(nbDeplacement, *cheval, chevaux);

    if (retour == 0 || retour == 1) {
      if (arriveFinTour(nbDeplacement, *cheval))
        retour = gestionTransition(nbDeplacement, cheval, chevaux);
      else {
        cheval->deplacement += nbDeplacement;

        if (retour == 1)
          mangerCheval(cheval, chevaux, couleursS);
      }
    }
  } else
    retour = avancerChevalFin(nbDeplacement, cheval, chevaux);

  return retour >= 0;
}

void mangerCheval(cheval_Struct* cheval, cheval_Struct chevaux[4][4], char* couleursS[]) {
  int depCheval = depRelatifToAbsolu(*cheval) % (TOUR_MAX + 1);

  for (int nbJoueur = 0; nbJoueur < 4; nbJoueur++) {
    if (chevaux[nbJoueur][0].couleur == cheval->couleur)
      continue;

    for (int posCheval = 0; posCheval < 4; posCheval++) {
      cheval_Struct* ennemi = &(chevaux[nbJoueur][posCheval]);

      if (depCheval == (depRelatifToAbsolu(*ennemi) % (TOUR_MAX + 1)))
        rentrerEcurie(ennemi, couleursS);
    }
  }
}

void rentrerEcurie(cheval_Struct* cheval, char* couleursS[]) {
  affRentrerEcurie(*cheval, couleursS);
  cheval->deplacement = -1;
}

void sortirEcurie(cheval_Struct* cheval, cheval_Struct chevaux[4][4], char* couleurS[]) {
  cheval->deplacement = 0;
  mangerCheval(cheval, chevaux, couleurS);
}

int depRelatifToAbsolu(cheval_Struct cheval) {
  if (cheval.deplacement < 0)
    return cheval.deplacement;

  return (cheval.deplacement + TOUR_ECURIE * cheval.couleur) % (TOUR_MAX + 1);
}

int depAbsoluToRelatif(int depAbsolu, cheval_Struct cheval) {
  if (depAbsolu < 0)
    return depAbsolu;

  return depAbsolu - TOUR_ECURIE * cheval.couleur;
}