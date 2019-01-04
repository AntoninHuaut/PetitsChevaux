/**
 * \file joueur.h
 * \brief Gestion des joueurs
 **/
#ifndef JOUEUR_H
#define JOUEUR_H
#include "cheval.h"
#include "plateau.h"

/**
 * \brief Structure qui compose un joueur
 **/
typedef struct {
  /** \brief Pseudo correspondant au joueur */
  char pseudo[32];
  /** \brief Couleur (= équipe) auquelle le joueur appartient */
  couleurEnum couleur;
} joueur_Struct;

/**
 * \brief Permet de connaître si le choix du joueur est possible
 * \param    action            Numéro de l'action choisi par le joueur
 * \param    tirage            Nombre tiré au dée
 * \param    couleurJouer      Numéro désignant la couleur du joueur qui joue
 * \param    chevaux[][]       Liste des chevaux des 4 joueurs
 * \return 0 (Impossible) 1 (Possible)
 **/
int actionEstDispo(int action, int tirage, int couleurJouer, cheval_Struct chevaux[4][4]);

/**
 * \brief Permet de connaître si le cheval choisi par le joueur est disponible
 * \param    chevalPosition    Position du cheval (entre 0 et 3)
 * \param    couleurJouer      Numéro désignant la couleur du joueur qui joue
 * \param    chevaux[][]       Liste des chevaux des 4 joueurs
 * \param    horsEcurie        0 : chevaux dans l'écurie   1 : chevaux hors écurie
 * \return 0 (Indisponible) 1 (Disponible)
 **/
int chevalEstDispo(int chevalPosition, int couleurJouer, cheval_Struct chevaux[4][4], int horsEcurie);

/**
 * \brief Gestion du choix du joueur
 * \param   *couleurJouer      Adresse du numéro désignant la couleur du joueur qui joue
 * \param   joueurs[]          Tableau de la liste des joueurs
 * \param   chevaux[][]        Liste des chevaux des 4 joueurs
 * \param   *couleursS[]       Tableau contenant le nom de la couleur pour son numéro
 * \return Numéro tiré lors du lancé de dée
 **/
int choixAction(int* couleurJouer, joueur_Struct joueurs[4], cheval_Struct chevaux[4][4], char* couleursS[]);

/**
 * \brief Execute l'action choisi par le joueur
 * \param    tirage            Nombre tiré au dée
 * \param    chevalPosition    Position du cheval (entre 0 et 3)
 * \param    couleurJouer      Adresse du numéro désignant la couleur du joueur qui joue
 * \param    chevaux[][]       Liste des chevaux des 4 joueurs
 * \param    horsEcurie        0 : chevaux dans l'écurie   1 : chevaux hors écurie
 * \param   *couleursS[]       Tableau contenant le nom de la couleur pour son numéro
 **/
void executeAction(int tirage,
                   int chevalPosition,
                   int couleurJouer,
                   cheval_Struct chevaux[4][4],
                   int horsEcurie,
                   char* couleursS[]);

/**
 * \brief Permet de connaître si un joueur a gagné la partie
 * \param    couleur           Numero de la couleur
 * \param    chevaux[][]       Liste des chevaux des 4 joueurs
 * \return 0 (Le joueur n'a pas gagné) 1 (Le joueur a gagné)
 **/
int aJoueurGagnant(int couleur, cheval_Struct chevaux[4][4]);

/**
 * \brief Renvoie le nombre de chevaux dans l'écurie d'un joueur
 * \param    couleurJouer      Numéro désignant la couleur du joueur qui joue
 * \param    chevaux[][]       Liste des chevaux des 4 joueurs
 * \return 0 - 4 : Nombre de chevaux dans l'écurie du joueur
 **/
int nbChevalEcurie(int couleurJouer, cheval_Struct chevaux[4][4]);

/**
 * \brief Simule un lancé de dé entre 1 et 6
 * \return 1 - 6
 **/
int tirageDe();

#endif