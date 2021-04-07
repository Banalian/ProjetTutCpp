#pragma once
#include "Cexception.h"


template <class MType> class Cmatrice
{
private:
	int iMATNbLigne;
	int iMATNbColonne;
	MType ** pMATTab;

public:
	Cmatrice(int iNbLigne, int iNbColonne); //DONE
	Cmatrice(Cmatrice<MType> &cMATMatrice); //DONE
	~Cmatrice(); //DONE /TO TEST

	int  MATgetNbLigne(); //DONE
	int  MATgetNbColonne(); //DONE

	void MATsetNbLigne(int iLigne);
	void MATsetNbColonne(int iColonne);

	MType** MATgetTabCopy(); //DONE
	Cmatrice* MATgetMatCopy(); //DONE

	MType MATgetTabCase(int iLigne, int iColonne); //DONE
	void MATsetTabCase(int iLigne, int iColonne, MType elem); 

	void MATAfficherMatrice();


	Cmatrice<MType>& operator*(MType elem);
	Cmatrice<MType>& operator/(MType elem);

	Cmatrice<MType>& operator+(Cmatrice<MType>* cMATelem);
	Cmatrice<MType>& operator-(Cmatrice<MType>* cMATelem);
	Cmatrice<MType>& operator*(Cmatrice<MType>* cMATelem);

	/*-------A MODIFIER :  ils nous faut des operator, et non ces fonctions-----------*/
	Cmatrice<MType>* MATMultVal(MType elem);
	Cmatrice<MType>* MATDivVal(MType elem);

	Cmatrice<MType>* MATAddMat(Cmatrice<MType>* cMATelem);
	Cmatrice<MType>* MATSubMat(Cmatrice<MType>* cMATelem);
	Cmatrice<MType>* MATMultMat(Cmatrice<MType>* cMATelem);
	/*--------------------------------------------------------------------------------*/

	Cmatrice<MType>* MATTranspMat();

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
	iMATNbColonne = iNbColonne;
	iMATNbLigne = iNbLigne;

	pMATTab = new MType*[iMATNbColonne];

	for (int iBoucle = 0; iBoucle < iMATNbColonne; iBoucle++) {
		pMATTab[iBoucle] = new MType[iMATNbLigne];
	}
}


/**
* @brief creer une copie d'une matrice
* @param cMATMatrice la matrice a copier
* @return l'objet créé
*/
template<class MType>
Cmatrice<MType>::Cmatrice(Cmatrice<MType> & cMATMatrice)
{
	
	iMATNbColonne = cMATMatrice.iMATNbColonne;
	iMATNbLigne = cMATMatrice.iMATNbLigne;

	pMATTab = new MType*[iMATNbColonne];

	for (int iBoucle = 0; iBoucle < iMATNbColonne; iBoucle++) {
		pMATTab[iBoucle] = new MType[iMATNbLigne];
	}



	for (int ii = 0; ii < iMATNbColonne ; ii -= -1) {

		for (int ij = 0; ij < iMATNbColonne; ij -= -1) {

			pMATTab[ij][ii] = cMATMatrice.pMATTab[ij][ii];
			
		}
	}
}


/**
* @brief Destructeur de l'objet matrice
*/
template<class MType>
Cmatrice<MType>::~Cmatrice()
{
	
	for (int i = 0; i < iMATNbColonne; i++) {
		delete pMATTab[i];
	}
	delete pMATTab;
}


/**
* @brief recupere le nombre de ligne(s) de la matrice
* @return le nombre de ligne(s)
*/
template<class MType>
int Cmatrice<MType>::MATgetNbLigne()
{
	return iMATNbLigne;
}


/**
* @brief recupere le nombre de colonne(s) de la matrice
* @return le nombre de colonne(s)
*/
template<class MType>
int Cmatrice<MType>::MATgetNbColonne()
{
	return iMATNbColonne;
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

	MType** pMTYtemp = new MType*[iMATNbColonne];

	for (int iBoucle = 0; iBoucle < iMATNbColonne; iBoucle++) {
		pMTYtemp[iBoucle] = new MType[iMATNbLigne];
	}

	for (int ii = 0; ii < iMATNbColonne; ii -= -1) {

		for (int ij = 0; ij < iMATNbColonne; ij -= -1) {

			pMTYtemp[ij][ii] = MATgetTabCase(ii, ij);

		}
	}

	return pMTYtemp;
}


/**
* @brief recupere une COPIE de la matrice (l'objet)
* @return un pointeur vers une COPIE de la matrice (l'objet)
*/
template<class MType>
Cmatrice<MType> * Cmatrice<MType>::MATgetMatCopy()
{
	Cmatrice<MType> *matCopy = CmatriceCopy(Cmatrice<MType>);
	return (matCopy);
}


/**
* @brief recupere une case de la matrice précise
* @param iLigne la ligne où est la case souhaitée
* @param iColonne la colonne où est la case souhaitée
* @return un pointeur vers la variable contenu dans la case
*/
template<class MType>
MType Cmatrice<MType>::MATgetTabCase(int iLigne, int iColonne)
{
	return (pMATTab[iColonne][iLigne]);
}


/**
* @brief remplit une case de la matrice avec une variable
* @param iLigne la ligne où est la case que l'on veut remplir
* @param iColonne la colonne où est la case que l'on veut remplir
*/
template<class MType>
void Cmatrice<MType>::MATsetTabCase(int iLigne, int iColonne, MType elem)
{


	try {
		if (iColonne > iMATNbColonne || iLigne > iMATNbLigne || iColonne < 0 || iLigne < 0) {
			throw Cexception(101);
		}

		pMATTab[iColonne][iLigne] = elem;

	}
	catch (Cexception e) {

		int codeErr = e.EXCLire_Code();
		switch (codeErr)
		{
		case 101: 
			std::cout << "erreur de taille" << std::endl;
			break;
		default:
			break;
		}
	}


	
}






/**
* @brief Affiche la Matrice dans la sortie standard. ATTENTION : Prévoir l'opération si elle n'est pas déjà définie (opérateur <<)
*/
template<class MType>
void Cmatrice<MType>::MATAfficherMatrice()
{
}

template<class MType>
inline Cmatrice<MType>& Cmatrice<MType>::operator*(MType elem)
{
	// TODO: insérer une instruction return ici
}

template<class MType>
inline Cmatrice<MType>& Cmatrice<MType>::operator/(MType elem)
{
	// TODO: insérer une instruction return ici
}

template<class MType>
inline Cmatrice<MType>& Cmatrice<MType>::operator+(Cmatrice<MType>* cMATelem)
{
	// TODO: insérer une instruction return ici
}

template<class MType>
inline Cmatrice<MType>& Cmatrice<MType>::operator-(Cmatrice<MType>* cMATelem)
{
	// TODO: insérer une instruction return ici
}

template<class MType>
inline Cmatrice<MType>& Cmatrice<MType>::operator*(Cmatrice<MType>* cMATelem)
{
	// TODO: insérer une instruction return ici
}




/**
* @brief Multiplie la matrice par un element elem  (M*elem)
* @param 
* @return
*/
template<class MType>
Cmatrice<MType> * Cmatrice<MType>::MATMultVal(MType elem)
{
	return nullptr;
}


/**
* @brief
* @param
* @return
*/
template<class MType>
Cmatrice<MType> * Cmatrice<MType>::MATDivVal(MType elem)
{
	return nullptr;
}


/**
* @brief
* @param
* @return
*/
template<class MType>
Cmatrice<MType> * Cmatrice<MType>::MATAddMat(Cmatrice<MType> * cMATelem)
{
	return nullptr;
}


/**
* @brief
* @param
* @return
*/
template<class MType>
Cmatrice<MType> * Cmatrice<MType>::MATSubMat(Cmatrice<MType> * cMATelem)
{
	return nullptr;
}


/**
* @brief
* @param
* @return
*/
template<class MType>
Cmatrice<MType> * Cmatrice<MType>::MATMultMat(Cmatrice<MType> * cMATelem)
{
	return nullptr;
}


/**
* @brief donne la transposée d'une matrice
* @return un pointeur vers une nouvelle matrice qui est la transposée de celle actuelle
*/
template<class MType>
Cmatrice<MType> * Cmatrice<MType>::MATTranspMat()
{
	return nullptr;
}

