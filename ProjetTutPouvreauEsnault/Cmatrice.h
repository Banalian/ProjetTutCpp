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
* Classe Cmatrice :  permet d'avoir des matrices et de realiser des operations comme la multiplication, ou avoir la transposee.
*/
template <class MType> class Cmatrice
{
private:
	int iMATNbLigne;
	int iMATNbColonne;
	MType ** pMTYTab = {}; //{} => https://en.cppreference.com/w/cpp/language/value_initialization

public:

	/**
	* @brief Constructeur par défaut : Fabrique une matrice vide de taille 1 1 (constructeur par défaut)
	* @return l'objet cree
	*/
	explicit Cmatrice(); //explicit => ne peut pas etre utilise pour les conversion

	/**
	* @brief Fabrique une matrice vide de taille iNbLigne iNbColonne
	* @param iNbLigne nombre de ligne(s) de la matrice
	* @param iNbColonne nombre de colonne(s) de la matrice
	* @return l'objet cree
	*/
	Cmatrice(int iNbLigne, int iNbColonne);

	/**
	* @brief Constructeur de recopie : cree une copie d'une matrice
	* @param MATMatrice la matrice a copier
	* @return l'objet cree
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
	* @brief change le nombre de ligne du tableau. ATTENTION :  toute donnee hors format sera perdue (mais non detruite) et les nouvelles cases seront zero initialised( check {} )
	* @param le nouveau nombre de ligne
	*/
	void MATsetNbLigne(int iLigne);
	/**
	* @brief change le nombre de colonne du tableau. ATTENTION :  toute donnee hors format sera perdue (mais non detruite) et les nouvelles cases seront zero initialised( check {} )
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
	* @brief recupere une case de la matrice précise
	* @param iLigne la ligne ou est la case souhaitée
	* @param iColonne la colonne ou est la case souhaitée
	* @return un pointeur vers la variable contenu dans la case
	*/
	MType MATgetTabCase(int iLigne, int iColonne);
	/**
	* @brief remplit une case de la matrice avec une variable
	* @param iLigne la ligne ou est la case que l'on veut remplir
	* @param iColonne la colonne ou est la case que l'on veut remplir
	* @param elem l'element a mettre dans la case (on utilise =, donc opérateur a surcharger selon vos besoins)
	*/
	void MATsetTabCase(int iLigne, int iColonne, MType elem);

	/**
	* @brief Affiche la Matrice dans la sortie standard. ATTENTION : Prevoir l'operation si elle n'est pas deja definie (operator <<)
	*/
	void MATAfficherMatrice();


	/**
	* @brief multiplie une matrice par un element elem (chaque case * elem)
	* @param elem l'elem par lequel tt les cases seront multipliees
	* @return une nouvelle matrice qui est le resultat de matrice * elem
	*/
	Cmatrice<MType>& operator*(MType elem);
	/**
	* @brief divise une matrice par un element elem (chaque case / elem)
	* @param elem l'elem par lequel tt les cases seront divisees
	* @return une nouvelle matrice qui est le resultat de matrice / elem
	*/
	Cmatrice<MType>& operator/(MType elem);

	/**
	* @brief additionne deux matrices
	* @param MATelem la matrice a additionner
	* @return une nouvelle matrice qui est le resultat de matrice + matrice
	*/
	Cmatrice<MType>& operator+(Cmatrice<MType> MATelem);
	/**
	* @brief soustrait deux matrices
	* @param MATelem la matrice que l'on va soustraire
	* @return une nouvelle matrice qui est le resultat de matrice - matrice
	*/
	Cmatrice<MType>& operator-(Cmatrice<MType> MATelem);
	/**
	* @brief multiplie deux matrices
	* @param MATelem la matrice a multiplier
	* @return une nouvelle matrice qui est le resultat de matrice * matrice
	*/
	Cmatrice<MType>& operator*(Cmatrice<MType> MATelem);

	/**
	* @brief Surcharge du = => equivalent au constructeur de recopie
	* @param MATelem la matrice a copier
	* @return la matrice copiee
	*/
	Cmatrice<MType>& operator=(Cmatrice<MType> MATelem);


	/**
	* @brief donne la transposee d'une matrice
	* @return un pointeur vers une nouvelle matrice qui est la transposee de celle actuelle
	*/
	Cmatrice<MType>* MATTranspMat();

};

/**
* @brief Surcharge de << => sert a output plus facilement une matrice
* ATTENTION : Prevoir l'operation si elle n'est pas deja definie (operator <<)
* exemple : std::cout << matrice;
* @param out le flux probablement std::cout la plupart du temps
* @param MATelem la Matrice a afficher
*/
template <class MType>
std::ostream& operator<<(std::ostream& out, Cmatrice<MType> & MATelem);



#include "Cmatrice.cpp"