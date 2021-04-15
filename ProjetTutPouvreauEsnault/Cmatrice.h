#pragma once
#include "Cexception.h"

#define ERRHorsFomatMat 101
#define ERRBadSizeMat 102
#define ERRBadNewLineCol 103
#define ERRDivByZero 150
#define ERRWrongSizeAdd 151
#define ERRWrongSizeMinus 152
#define ERRWrongSizeMult 153


/**
* Classe Cmatrice :  permet d'avoir des matrices et de r�aliser des operations comme la multiplication, ou avoir la transposee.
*/
template <class MType> class Cmatrice
{
private:
	int iMATNbLigne;
	int iMATNbColonne;
	MType ** pMATTab = {}; //{} => https://en.cppreference.com/w/cpp/language/value_initialization

public:

	/**
	* @brief Constructeur par d�faut : Fabrique une matrice vide de taille 1 1 (constructeur par d�faut)
	* @return l'objet cr��
	*/
	explicit Cmatrice(); //ne peut pas etre utilis� pour les conversion

	/**
	* @brief Fabrique une matrice vide de taille iNbLigne iNbColonne
	* @param iNbLigne nombre de ligne(s) de la matrice
	* @param iNbColonne nombre de colonne(s) de la matrice
	* @return l'objet cr��
	*/
	Cmatrice(int iNbLigne, int iNbColonne);

	/**
	* @brief Constructeur de recopie : cree une copie d'une matrice
	* @param MATMatrice la matrice a copier
	* @return l'objet cr��
	*/
	Cmatrice(Cmatrice<MType> &MATMatrice);

	/**
	* @brief Destructeur de l'objet matrice
	*/
	~Cmatrice();



	/**
	* @brief recupere le nombre de ligne(s) de la matrice
	* @return le nombre de ligne(s)
	*/
	int  MATgetNbLigne();
	/**
	* @brief recupere le nombre de colonne(s) de la matrice
	* @return le nombre de colonne(s)
	*/
	int  MATgetNbColonne();

	/**
	* @brief change le nombre de ligne du tableau. ATTENTION :  toute donn�e hors format sera perdu (mais non d�truite) et les nouvelles cases seront zero initialised( check {} )
	* @param le nouveau nombre de ligne
	*/
	void MATsetNbLigne(int iLigne);
	/**
	* @brief change le nombre de colonne du tableau. ATTENTION :  toute donn�e hors format sera perdue et d�truite et les nouvelles cases seront zero initialised( check {} )
	* @param le nouveau nombre de colonne
	*/
	void MATsetNbColonne(int iColonne);


	/**
	* @brief recupere une COPIE du tableau de la matrice
	* @return un pointeur vers une COPIE du tableau de la matrice
	*/
	MType** MATgetTabCopy();
	/**
	* @brief recupere une COPIE de la matrice (l'objet)
	* @return un pointeur vers une COPIE de la matrice (l'objet)
	*/
	Cmatrice* MATgetMatCopy();

	/**
	* @brief recupere une case de la matrice pr�cise
	* @param iLigne la ligne o� est la case souhait�e
	* @param iColonne la colonne o� est la case souhait�e
	* @return un pointeur vers la variable contenu dans la case
	*/
	MType MATgetTabCase(int iLigne, int iColonne);
	/**
	* @brief remplit une case de la matrice avec une variable
	* @param iLigne la ligne o� est la case que l'on veut remplir
	* @param iColonne la colonne o� est la case que l'on veut remplir
	* @param elem l'element a mettre dans la case (on utilise =, donc op�rateur a surcharger selon vos besoins)
	*/
	void MATsetTabCase(int iLigne, int iColonne, MType elem);

	/**
	* @brief Affiche la Matrice dans la sortie standard. ATTENTION : Pr�voir l'op�ration si elle n'est pas d�j� d�finie (op�rateur <<)
	*/
	void MATAfficherMatrice();


	/**
	* @brief multiplie une matrice par un element elem (chaque case * elem)
	* @param elem l'elem par lequel tt les cases seront multipli�es
	* @return une nouvelle matrice qui est le r�sultat de matrice * elem
	*/
	Cmatrice<MType>& operator*(MType elem);
	/**
	* @brief divise une matrice par un element elem (chaque case / elem)
	* @param elem l'elem par lequel tt les cases seront divis�es
	* @return une nouvelle matrice qui est le r�sultat de matrice / elem
	*/
	Cmatrice<MType>& operator/(MType elem);

	/**
	* @brief additionne deux matrices
	* @param MATelem la matrice a additionner
	* @return une nouvelle matrice qui est le r�sultat de matrice + matrice
	*/
	Cmatrice<MType>& operator+(Cmatrice<MType> MATelem);
	/**
	* @brief soustrait deux matrices
	* @param MATelem la matrice que l'on va soustraire
	* @return une nouvelle matrice qui est le r�sultat de matrice - matrice
	*/
	Cmatrice<MType>& operator-(Cmatrice<MType> MATelem);
	/**
	* @brief multiplie deux matrices
	* @param MATelem la matrice a multiplier
	* @return une nouvelle matrice qui est le r�sultat de matrice * matrice
	*/
	Cmatrice<MType>& operator*(Cmatrice<MType> MATelem);

	/**
	* @brief Surcharge du = => equivalent au constructeur de recopie
	* @param MATelem la matrice a copier
	* @return la matrice copiee
	*/
	Cmatrice<MType>& operator=(Cmatrice<MType> MATelem);

	/**
	* @brief donne la transpos�e d'une matrice
	* @return un pointeur vers une nouvelle matrice qui est la transpos�e de celle actuelle
	*/
	Cmatrice<MType>* MATTranspMat();

};

#include "Cmatrice.cpp"