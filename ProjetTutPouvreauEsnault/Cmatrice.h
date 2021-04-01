#pragma once

template <class MType> class Cmatrice
{
private:
	int iMATNbLigne;
	int iMATNbColonne;
	MType ** pMATTab;

public:
	Cmatrice(int iNbLigne, int iNbColonne);
	Cmatrice(Cmatrice &cMATMatrice);
	~Cmatrice();

	int  MATgetNbLigne();
	int  MATgetNbColonne();

	void MATsetNbLigne(int iLigne);
	void MATsetNbColonne(int iColonne);

	MType** MATgetTabCopy();
	Cmatrice* MATgetMatCopy();

	MType* MATgetTabCase(int iLigne, int iColonne);
	void MATsetTabCase(int iLigne, int iColonne, MType *elem);

	void MATAfficherMatrice();


	/*-------A MODIFIER :  ils nous faut des operator, et non ces fonctions-----------*/
	Cmatrice<MType>* MATMultVal(MType elem);
	Cmatrice<MType>* MATDivVal(MType elem);

	Cmatrice<MType>* MATAddMat(Cmatrice* cMATelem);
	Cmatrice<MType>* MATSubMat(Cmatrice* cMATelem);
	Cmatrice<MType>* MATMultMat(Cmatrice* cMATelem);
	/*--------------------------------------------------------------------------------*/

	Cmatrice* MATTranspMat();

};


/**
* @brief creer une matrice vide de taille iNbLigne iNbColonne
* @param iNbLigne nombre de ligne(s) de la matrice
* @param iNbColonne nombre de colonne(s) de la matrice
* @return l'objet créé
*/
template<class MType>
Cmatrice<MType>::Cmatrice(int iNbLigne, int iNbColonne)
{
}


/**
* @brief creer une copie d'une matrice
* @param cMATMatrice la matrice a copier
* @return l'objet créé
*/
template<class MType>
Cmatrice<MType>::Cmatrice(Cmatrice & cMATMatrice)
{
}


/**
* @brief Destructeur de l'objet matrice
*/
template<class MType>
Cmatrice<MType>::~Cmatrice()
{
}


/**
* @brief recupere le nombre de ligne(s) de la matrice
* @return le nombre de ligne(s)
*/
template<class MType>
int Cmatrice<MType>::MATgetNbLigne()
{
	return 0;
}


/**
* @brief recupere le nombre de colonne(s) de la matrice
* @return le nombre de colonne(s)
*/
template<class MType>
int Cmatrice<MType>::MATgetNbColonne()
{
	return 0;
}


/**
* @brief change le nombre de ligne du tableau. ATTENTION :  toute donnée hors format sera perdu (mais non détruite) et les nouvelles cases seront vide
* @param le nouveau nombre de ligne
*/
template<class MType>
void Cmatrice<MType>::MATsetNbLigne(int iLigne)
{
}


/**
* @brief change le nombre de colonne du tableau. ATTENTION :  toute donnée hors format sera perdu (mais non détruite) et les nouvelles cases seront vide
* @param le nouveau nombre de colonne
*/
template<class MType>
void Cmatrice<MType>::MATsetNbColonne(int iColonne)
{
}


/**
* @brief recupere une COPIE du tableau de la matrice
* @return un pointeur vers une COPIE du tableau de la matrice
*/
template<class MType>
MType ** Cmatrice<MType>::MATgetTabCopy()
{
	return NULL;
}


/**
* @brief recupere une COPIE de la matrice (l'objet)
* @return un pointeur vers une COPIE de la matrice (l'objet)
*/
template<class MType>
Cmatrice<MType> * Cmatrice<MType>::MATgetMatCopy()
{
	return NULL;
}


/**
* @brief recupere une case de la matrice précise
* @param iLigne la ligne où est la case souhaitée
* @param iColonne la colonne où est la case souhaitée
* @return un pointeur vers la variable contenu dans la case
*/
template<class MType>
MType * Cmatrice<MType>::MATgetTabCase(int iLigne, int iColonne)
{
	return NULL;
}


/**
* @brief remplit une case de la matrice avec une variable
* @param iLigne la ligne où est la case que l'on veut remplir
* @param iColonne la colonne où est la case que l'on veut remplir
*/
template<class MType>
void Cmatrice<MType>::MATsetTabCase(int iLigne, int iColonne, MType * elem)
{
}


/**
* @brief Affiche la Matrice dans la sortie standard. ATTENTION : Prévoir l'opération si elle n'est pas déjà définie (opérateur <<)
*/
template<class MType>
void Cmatrice<MType>::MATAfficherMatrice()
{
}




/**
* @brief Multiplie la matrice par un element elem  (M*elem)
* @param 
* @return
*/
template<class MType>
Cmatrice<MType> * Cmatrice<MType>::MATMultVal(MType elem)
{
	return NULL;
}


/**
* @brief
* @param
* @return
*/
template<class MType>
Cmatrice<MType> * Cmatrice<MType>::MATDivVal(MType elem)
{
	return NULL;
}


/**
* @brief
* @param
* @return
*/
template<class MType>
Cmatrice<MType> * Cmatrice<MType>::MATAddMat(Cmatrice * cMATelem)
{
	return NULL;
}


/**
* @brief
* @param
* @return
*/
template<class MType>
Cmatrice<MType> * Cmatrice<MType>::MATSubMat(Cmatrice * cMATelem)
{
	return NULL;
}


/**
* @brief
* @param
* @return
*/
template<class MType>
Cmatrice<MType> * Cmatrice<MType>::MATMultMat(Cmatrice * cMATelem)
{
	return NULL;
}


/**
* @brief donne la transposée d'une matrice
* @return un pointeur vers une nouvelle matrice qui est la transposée de celle actuelle
*/
template<class MType>
Cmatrice<MType> * Cmatrice<MType>::MATTranspMat()
{
	return NULL;
}

