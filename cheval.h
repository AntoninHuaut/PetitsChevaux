/**
 * \file cheval.h
 * \brief Gestion des chevaux
 **/
#ifndef CHEVAL_H
#define CHEVAL_H

/**
 * \brief Nombre de cases sur le plateau SANS les cases de fin
 **/
#define TOUR_MAX 55
/**
 * \brief Nombre de cases entre deux sorties d'écuries
 **/
#define TOUR_ECURIE 14
/**
 * \brief Nombre de cases sur le plateau AVEC les cases de fin
 **/
#define CASE_MAX 61

/**
 * \brief Liste des couleurs
 **/
typedef enum { JAUNE, BLEU, ROUGE, VERT } couleurEnum;

/**
 * \brief Structure qui compose un cheval
 **/
typedef struct {
  /** \brief Nombre de déplacement effectué par un cheval hors de l'écurie */
  int deplacement;
  /** \brief Numéro du cheval relatif à son joueur */
  int numero;
  /** \brief Couleur (= équipe) auquelle le cheval appartient */
  couleurEnum couleur;

} cheval_Struct;

#include "plateau.h"

/**
 * \brief Fait déplacer le cheval dans les cases de fun & indique un entier indiquant si le cheval a pu se déplacer
 * \param   nbDeplacement    Nombre de déplacements que le cheval doit effectuer sur les cases de fin
 * \param   cheval           Adresse de la structure du cheval qui veut se déplacer
 * \param   chevaux[][]      Liste des chevaux des 4 joueurs
 * \return 0 (Aucun cheval d'une autre couleur sur la route) -1 (Cheval bloquant sur la route, déplacement annulé)
 **/
int avancerChevalFin(int nbDeplacement, cheval_Struct* cheval, cheval_Struct chevaux[4][4]);

/**
 * \brief Effectue la transition entre les cases 'normales' et les cases de fin
 * \param   nbDeplacement    Nombre de déplacements que le cheval doit effectuer
 * \param   cheval           Adresse de la structure du cheval qui veut se déplacer
 * \param   chevaux[][]      Liste des chevaux des 4 joueurs
 * \return valeur de avancerChevalFin()
 **/
int gestionTransition(int nbDeplacement, cheval_Struct* cheval, cheval_Struct chevaux[4][4]);

/**
 * \brief Permet de connaître si le cheval est/sera dans les cases de fins
 * \param   nbDeplacement    Nombre de déplacements que le cheval doit effectuer
 * \param   cheval           Adresse de la structure du cheval qui veut se déplacer
 * \return 1 (Le cheval se trouve[ra] dans une case de fin) 0 (Le cheval ne s'y trouve[ra] pas)
 **/
int arriveFinTour(int nbDeplacement, cheval_Struct cheval);

/**
 * \brief Retourne un entier indiquant si des chevaux se trouvent sur la route
 * \param   nbDeplacement    Nombre de déplacements que le cheval doit effectuer
 * \param   cheval           Structure du cheval qui veut se déplacer
 * \param   chevaux[][]      Liste des chevaux des 4 joueurs
 * \return 0 (Déplacement possible) -1 (Cheval bloquant sur la route) 1 (Déplacement possible mais cheval à manger)
 **/
int chevalSurRoute(int nbDeplacement, cheval_Struct cheval, cheval_Struct chevaux[4][4]);

/**
 * \brief Fait avancer (ou non) le cheval d'un nombre de case demandé
 * \param   nbDeplacement    Nombre de déplacements que le cheval doit effectuer
 * \param   cheval           Adresse de la structure du cheval qui veut se déplacer
 * \param   chevaux[][]      Liste des chevaux des 4 joueurs
 * \param   *couleursS[]     Tableau contenant le nom de la couleur pour son numéro
 * \return 1 (Si le cheval a pu se déplacer) 0 (Si le cheval n'a pu se déplacer)
 **/
int avancerCheval(int nbDeplacement, cheval_Struct* cheval, cheval_Struct chevaux[4][4], char* couleursS[]);

/**
 * \brief Mange tous les chevaux qui ne sont pas de la même couleur du cheval ciblé, ayant le même nombre de déplacements
 * \param   cheval           Adresse de la structure du cheval qui se fait manger
 * \param   chevaux[][]      Liste des chevaux des 4 joueurs
 * \param   *couleursS[]     Tableau contenant le nom de la couleur pour son numéro
 **/
void mangerCheval(cheval_Struct* cheval, cheval_Struct chevaux[4][4], char* couleursS[]);

/**
 * \brief Renvoie un cheval dans son écurie
 * \param   cheval           Adresse de la structure du cheval renvoyé à son écurie
 * \param   *couleursS[]     Tableau contenant le nom de la couleur pour son numéro
 **/
void rentrerEcurie(cheval_Struct* cheval, char* couleursS[]);

/**
 * \brief Fait sortir un cheval de son écurie et mange les chevaux ennemis sur la case de sortie d'écurie
 * \param   cheval           Adresse de la structure du cheval sortant de son écurie
 * \param   chevaux[][]      Liste des chevaux des 4 joueurs
 * \param   *couleursS[]     Tableau contenant le nom de la couleur pour son numéro
 **/
void sortirEcurie(cheval_Struct* cheval, cheval_Struct chevaux[4][4], char* couleursS[]);

/**
 * \brief Converti le nbDeplacement d'un cheval (relatif à son écurie) au nbDeplacement suivant l'écurie du cheval Jaune
 * \param   cheval           Structure d'un cheval
 **/
int depRelatifToAbsolu(cheval_Struct cheval);

/**
 * \brief Converti le nbDeplacement d'un cheval suivant l'écurie du cheval Jaune au nbDeplacement d l'écurie de ce cheval
 * \param   depAbsolu        Nombre de déplacements absolu (suivant l'écurie du chevalJaune)
 * \param   cheval           Structure d'un cheval
 **/
int depAbsoluToRelatif(int depAbsolu, cheval_Struct cheval);

#endif