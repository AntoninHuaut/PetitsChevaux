/**
 * \file affichage.h
 * \brief Gestion de l'affichage
 **/
#ifndef AFFICHAGE_H
#define AFFICHAGE_H

/** \defgroup ColText Couleur du texte 
 * Permet de changer la couleur du texte en tappant seulement le nom de la couleur
 * \{
 */
/** \brief Couleur grise */
#define GREY "\033[37m"

/** \brief Couleur blanche */
#define WHITE "\033[37m"

/** \brief Couleur rouge */
#define RED "\033[31m"

/** \brief Couleur verte */
#define GREEN "\033[32m"

/** \brief Couleur jaune */
#define YELLOW "\033[33m"

/** \brief Couleur bleu */
#define BLUE "\033[36m"
/** \} */

#include "cheval.h"
#include "joueur.h"
#include "plateau.h"

/**
 * \brief Affiche les choix d'un joueur
 * \param   tirage           Nombre tiré au dée
 * \param   couleurJouer     Numéro désignant la couleur du joueur qui joue
 * \param   chevaux[][]      Liste des chevaux des 4 joueurs
 **/
void affActions(int tirage, int couleurJouer, cheval_Struct chevaux[4][4]);

/**
 * \brief Affiche les choix d'un joueur
 * \param   couleurJouer     Numéro désignant la couleur du joueur qui joue
 * \param   chevaux[][]      Liste des chevaux des 4 joueurs
 * \param   horsEcurie       0 : chevaux dans l'écurie   1 : chevaux hors écurie
 **/
void affChevaux(int couleurJouer, cheval_Struct chevaux[4][4], int horsEcurie);

/**
 * \brief Message: Le cheval a été renvoyé dans son écurie
 * \param     cheval         Structure du cheval qui veut se déplacer
 * \param     *couleursS[]   Tableau contenant le nom de la couleur pour son numéro
 **/
void affRentrerEcurie(cheval_Struct cheval, char* couleursS[]);

/**
 * \brief Affiche le plateau de jeu
 * \param   couleurJouer     Numéro désignant la couleur du joueur qui joue
 * \param   plateau[][]      Tableau contenant les types de case du jeu
 * \param   chevaux[][]      Liste des chevaux des 4 joueurs
 * \param   unDimTo2DM[][]   Tableau contenant la relation entre 1Dimension et 2Dimensions
 **/
void affPlateau(int couleurJouer,
                int plateau[TPLATEAU][TPLATEAU],
                cheval_Struct chevaux[4][4],
                int unDimTo2DM[TOUR_MAX + 1][2]);

/**
 * \brief Affiche une couleur suivant l'endroit du plateau
 * \param   lig              Numéro de la ligne (x)
 * \param   col              Numéro de la colonne (y)
 **/
void setCouleur(int lig, int col);

/**
 * \brief Affiche une couleur suivant son numéro
 * \param   couleur          Numéro de la couleur
 **/
void affCouleur(int couleur);

/**
 * \brief Permet de lire un entier d'un utilisateur sans avoir de bug s'il entre un caractère autre qu'un chiffre
 * \param   *entier          Adresse de l'entier à modifier
 **/
void scanfD(int* entier);

#endif