/**
 * \file sauvegarde.h
 * \brief Gestion des systèmes de sauvegarde
 **/
#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H
#include "cheval.h"
#include "joueur.h"

/**
 * \brief Nom du fichier de sauvegarde
 **/
#define FICHIER_SAV "sauvegarde.dat"

/**
 * \brief Nombre de slot de sauvegardes maximum
 **/
#define SLOT_MAX 5

/**
 * \brief Structure qui compose une sauvegarde complète
 **/
typedef struct {
  /** \brief Liste des joueurs */
  joueur_Struct joueurs[4];
  /** \brief Liste des chevaux des 4 joueurs */
  cheval_Struct chevaux[4][4];
  /** \brief Numéro de la couleur qui doit jouer */
  int couleurJoueur;
} sauvegarde;

/**
 * \brief Structure qui compose la liste des sauvegardes
 **/
typedef struct {
  /** \brief Liste des sauvegardes */
  sauvegarde sav[SLOT_MAX];
} sauvegardeList;

/**
 * \brief Affiche le menu de sélection d'un menu de sauvegardes
 * \param    *couleurJoueur    Adresse du numéro de la couleur qui doit jouer
 * \param    joueurs[]         Liste des joueurs
 * \param    chevaux[][]       Liste des chevaux des 4 joueurs
 * \return 0 (Pas de sauvegarde chargée) 1 (Dernière sauvegarde chargée) 2 (Sauvegarde pré-configurée chargée)
 **/
int choixSave(int* couleurJoueur, joueur_Struct joueurs[], cheval_Struct chevaux[4][4]);

/**
 * \brief Charge une sauvegarde pré-configurée
 * \param    save              Numéro de la sauvegarde pré-configurée à charger
 * \param    chevaux[][]       Liste des chevaux des 4 joueurs
 **/
void chargePreSav(int save, cheval_Struct chevaux[4][4]);

/**
 * \brief Demande au joueurs de choisir un emplacement de sauvegarde
 * \param   saveType           Type de la sauvegarde (1 = sauvegarde 0 = chargement)
 * \return 1 - SLOT_MAX
 **/
int choixSlot(int saveType);

/**
 * \brief Affiche les emplacements disponibles/indisponibles avec une couleur différente
 * \param   saveType           Type de la sauvegarde (1 = sauvegarde 0 = chargement)
 **/
void affSlotDispo(int saveType);

/**
 * \brief Permet de savoir si le slot demandé peut être chargé (si elle existe)
 * \param    slot              Numéro de la sauvegarde que le joueur souhaite charger
 * \return 1 (Slot chargeable) 0 (Slot pas chargeable)
 **/
int slotChargeable(int slot);

/**
 * \brief Sauvegarde une partie dans un fichier
 * \param    slot              Numéro de la sauvegarde que le joueur souhaite charger
 * \param    *couleurJoueur    Adresse du numéro de la couleur qui doit jouer
 * \param    joueurs[]         Liste des joueurs
 * \param    chevaux[][]       Liste des chevaux des 4 joueurs
 **/
void saveNormal(int slot, int couleurJoueur, joueur_Struct joueurs[], cheval_Struct chevaux[4][4]);

/**
 * \brief Récupère les sauvegardes depuis le fichier
 * \param    sav[]             Tableau contenant les différentes sauvegardes
 **/
void getNormalSav(sauvegarde sav[]);

/**
 * \brief Charge une sauvegarde par fichier
 * \param    slot              Numéro de la sauvegarde que le joueur souhaite charger
 * \param    *couleurJoueur    Adresse du numéro de la couleur qui doit jouer
 * \param    joueurs[]         Liste des joueurs
 * \param    chevaux[][]       Liste des chevaux des 4 joueurs
 **/
void chargeNormalSav(int slot, int* couleurJoueur, joueur_Struct joueurs[], cheval_Struct chevaux[4][4]);

/**
 * \brief Permet de connaître si il existe un fichier de sauvegarde
 * \return 0 (N'existe pas)  1 (Existe)
 **/
int fichierExiste();

#endif