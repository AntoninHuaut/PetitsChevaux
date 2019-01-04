/**
 * \file plateau.h
 * \brief Gestion du plateau
 **/
#ifndef PLATEAU_H
#define PLATEAU_H

/**
 * \brief Nombre de cases du plateau (définit un carré)
 **/
#define TPLATEAU 15

/**
 * \brief Liste des types de cases existantes sur le plateau
 **/
typedef enum {
  NORMAL,
  CASE_1,
  CASE_2,
  CASE_3,
  CASE_4,
  CASE_5,
  CASE_6,
  CASE_SORTIE_ECURIE,
  CASE_ECURIE,
  CASE_CENTRE
} caseTypeEnum;

#include "cheval.h"

/**
 * \brief Méthode qui génère le tableau (ligne/colonne) avec les chevaux placés
 * \param    placement[][]     Tableau vide qui va être le tableau avec les chevaux
 * \param    chevaux[][]       Liste des chevaux des 4 joueurs
 * \param    unDimTo2DM[][]    Tableau contenant la relation entre 1Dimension et 2Dimensions
 **/
void chevauxTo2D(cheval_Struct placement[TPLATEAU][TPLATEAU], cheval_Struct chevaux[4][4], int unDimTo2DM[TOUR_MAX + 1][2]);

/**
 * \brief Place un cheval dans le tableau de placement
 * \param    depRelatif        Position relative du cheval
 * \param    depAbsolu         Position absolue du cheval
 * \param    unDimTo2DM[][]    Tableau contenant la relation entre 1Dimension et 2Dimensions
 * \param    placement[][]     Tableau vide qui va être le tableau avec les chevaux
 * \param    cheval            Structure du cheval qui se fait placer
 **/
void setCordonnee(int depRelatif,
                  int depAbsolu,
                  int unDimTo2DM[TOUR_MAX + 1][2],
                  cheval_Struct placement[TPLATEAU][TPLATEAU],
                  cheval_Struct cheval);

/**
 * \brief Initialisation du tableau unDimTo2DM
 * \param    unDimTo2DM[][]    Tableau contenant la relation entre 1Dimension et 2Dimensions
 **/
void initTab1DTo2D(int unDimTo2DM[TOUR_MAX + 1][2]);

/**
 * \brief Initialisation du tableau de jeu et du tableau unDimTo2DM
 * \param    plateau[][]       Tableau contenant le type des cases pour chaque (x, y)
 * \param    unDimTo2DM[][]    Tableau contenant la relation entre 1Dimension et 2Dimensions
 **/
void initPlateau(int plateau[TPLATEAU][TPLATEAU], int unDimTo2DM[TOUR_MAX + 1][2]);

#endif