/**
 * \file jeu.h
 * \brief Gestion du déroulement du jeu
 **/
#ifndef JEU_H
#define JEU_H
#include "cheval.h"
#include "joueur.h"

/**
 * \brief Lance le jeu
 **/
void startJeu();

/**
 * \brief Lance le jeu
 * \param   saveChargee      Permet de savoir quel type de sauvegarde est chargée (0 si aucune)
 * \param   *couleursS[]     Tableau des couleurs en chaîne de caractères
 * \param   joueurs[]        Tableau de la liste des joueurs
 * \param   chevaux[][]      Tableau 2D de la liste des joueurs avec leur liste de chevaux
 * \param   *couleurJoueur   Adresse du numéro de la couleur
 **/
void initJeu(int saveChargee, char* couleursS[], joueur_Struct joueurs[4], cheval_Struct chevaux[4][4], int* couleurJoueur);

/**
 * \brief Tire un numéro correspondant à la couleur entre 0 et 3
 * \return 0 - 3
 **/
int tirageCouleur();

#endif