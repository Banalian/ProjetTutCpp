#pragma once
#include "Cexception.h"


template <class MType> class Cmatrice
{
private:
	int iMATNbLigne;
	int iMATNbColonne;
	MType ** pMATTab = {};

public:
	Cmatrice(int iNbLigne, int iNbColonne); //DONE
	Cmatrice(Cmatrice<MType> &cMATMatrice); //DONE
	~Cmatrice(); //DONE /TO TEST

	int  MATgetNbLigne(); //DONE
	int  MATgetNbColonne(); //DONE

	void MATsetNbLigne(int iLigne); //DONE
	void MATsetNbColonne(int iColonne); //DONE

	MType** MATgetTabCopy(); //DONE
	Cmatrice* MATgetMatCopy(); //DONE

	MType MATgetTabCase(int iLigne, int iColonne); //DONE
	void MATsetTabCase(int iLigne, int iColonne, MType elem); //DONE

	void MATAfficherMatrice(); //DONE


	Cmatrice<MType>& operator*(MType elem); //DONE
	Cmatrice<MType>& operator/(MType elem); //DONE

	Cmatrice<MType>& operator+(Cmatrice<MType>* cMATelem); //DONE
	Cmatrice<MType>& operator-(Cmatrice<MType>* cMATelem); //DONE
	Cmatrice<MType>& operator*(Cmatrice<MType> cMATelem); //JE M'EN OCCUPE LILIAN

	/*-------A MODIFIER :  ils nous faut des operator, et non ces fonctions-----------*/
	Cmatrice<MType>* MATMultVal(MType elem); //remplacée par operator* (MType elem)
	Cmatrice<MType>* MATDivVal(MType elem); //remplacée par operator/ (MType elem)

	Cmatrice<MType>* MATAddMat(Cmatrice<MType>* cMATelem); //remplacé par operator+(Cmatrice<MType>* cMATelem)
	Cmatrice<MType>* MATSubMat(Cmatrice<MType>* cMATelem); //remplacé par operator-(Cmatrice<MType>* cMATelem)
	Cmatrice<MType>* MATMultMat(Cmatrice<MType>* cMATelem); //remplacé par operator*(Cmatrice<MType>* cMATelem)
	/*--------------------------------------------------------------------------------*/

	Cmatrice<MType>* MATTranspMat(); //DONE

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
	if (iNbColonne < 0 || iNbLigne < 0) {
		throw Cexception(102);
	}
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

		for (int ij = 0; ij < iMATNbLigne; ij -= -1) {

			pMATTab[ii][ij] = cMATMatrice.pMATTab[ii][ij];
			
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
	if (iLigne < 0) {
		throw Cexception(103);
	}

	int ligne = 0;

	if (iLigne < iMATNbLigne) {
		ligne = iLigne;
	}
	else {
		ligne = iMATNbLigne;
	}

	//on crée un nouveau tableau de la bonne taille
	MType** pMATTemp = new MType*[iMATNbColonne];
	for (int iBoucle = 0; iBoucle < iMATNbColonne; iBoucle++) {
		pMATTemp[iBoucle] = new MType[iLigne];
	}

	//on recopie les valeurs du tableau actuel dans le tableau qui le remplacera
	for (int ii = 0; ii < iMATNbColonne; ii -= -1) {

		for (int ij = 0; ij < ligne; ij -= -1) {

			pMATTemp[ii][ij] = pMATTab[ii][ij];

		}
	}


	//on supprime l'ancien tableau
	for (int i = 0; i < iMATNbColonne; i++) {
		delete pMATTab[i];
	}
	delete pMATTab;


	iMATNbLigne = iLigne;
	pMATTab = pMATTemp;
}


/**
* @brief change le nombre de colonne du tableau. ATTENTION :  toute donnée hors format sera perdue et détruite et les nouvelles cases seront vide
* @param le nouveau nombre de colonne
*/
template<class MType>
void Cmatrice<MType>::MATsetNbColonne(int iColonne)
{
	if (iColonne < 0) {
		throw Cexception(103);
	}
	int colonne = 0;
	if (iColonne < iMATNbColonne) {
		colonne = iColonne;
	}
	else {
		colonne = iMATNbColonne;
	}



	//on crée un nouveau tableau de la bonne taille
	MType** pMATTemp = new MType*[iColonne];
	for (int iBoucle = 0; iBoucle < iColonne; iBoucle++) {
		pMATTemp[iBoucle] = new MType[iMATNbLigne];
	}

	//on recopie les valeurs du tableau actuel dans le tableau qui le remplacera
	for (int ii = 0; ii < colonne; ii -= -1) {

		for (int ij = 0; ij < iMATNbLigne; ij -= -1) {

			pMATTemp[ii][ij] = pMATTab[ii][ij];

		}
	}



	//on supprime l'ancien tableau
	for (int i = 0; i < iMATNbColonne; i++) {
		delete pMATTab[i];
	}
	delete pMATTab;


	iMATNbColonne = iColonne;
	pMATTab = pMATTemp;
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
	Cmatrice<MType> *matCopy = new Cmatrice(*this);
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
	if (iColonne >= iMATNbColonne || iLigne >= iMATNbLigne || iColonne < 0 || iLigne < 0) {
		throw Cexception(101);
	}
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


	if (iColonne > iMATNbColonne || iLigne > iMATNbLigne || iColonne < 0 || iLigne < 0) {
		throw Cexception(101);
	}

	pMATTab[iColonne][iLigne] = elem;

	
}






/**
* @brief Affiche la Matrice dans la sortie standard. ATTENTION : Prévoir l'opération si elle n'est pas déjà définie (opérateur <<)
*/
template<class MType>
void Cmatrice<MType>::MATAfficherMatrice()
{
	for (int iBoucle = 0; iBoucle < iMATNbLigne; iBoucle++) {
		for (int jBoucle = 0; jBoucle < iMATNbColonne; jBoucle++) {
			std::cout << pMATTab[jBoucle][iBoucle] << "\t";
		}
		std::cout << std::endl;
	}
}

template<class MType>
Cmatrice<MType>& Cmatrice<MType>::operator*(MType elem)
{
	// TODO: insérer une instruction return ici
	for (int iBoucle = 0; iBoucle < iMATNbLigne; iBoucle++) {
		for (int jBoucle = 0; jBoucle < iMATNbColonne; jBoucle++) {
			pMATTab[jBoucle][iBoucle] = pMATTab[jBoucle][iBoucle] * elem;
		}
	}

}

template<class MType>
Cmatrice<MType>& Cmatrice<MType>::operator/(MType elem)
{
	// TODO: insérer une instruction return ici
	for (int iBoucle = 0; iBoucle < iMATNbLigne; iBoucle++) {
		for (int jBoucle = 0; jBoucle < iMATNbColonne; jBoucle++) {
			pMATTab[jBoucle][iBoucle] = pMATTab[jBoucle][iBoucle] / elem;
		}
	}
}

template<class MType>
Cmatrice<MType>& Cmatrice<MType>::operator+(Cmatrice<MType>* cMATelem)
{

	//si les matrices ne sont pas de la meme taille
	if ((iMATNbColonne != cMATelem->MATgetNbColonne()) || (iMATNbLigne != cMATelem->MATgetNbLigne())) {
		throw Cexception(251);
	}
	
	Cmatrice<MType>* pMATTemp = new Cmatrice(iMATNbLigne, iMATNbColonne);


	for (int iBoucle = 0; iBoucle < iMATNbLigne; iBoucle++) {
		for (int jBoucle = 0; jBoucle < iMATNbColonne; jBoucle++) {
			//simple C = A + B pour chaque cases
			pMATTemp[jBoucle][iBoucle] = pMATTab[jBoucle][iBoucle] + cMATelem->MATgetTabCase(iBoucle, jBoucle);
		}
	}


	return *pMATTemp;


	
}

template<class MType>
Cmatrice<MType>& Cmatrice<MType>::operator-(Cmatrice<MType>* cMATelem)
{


	//si les matrices ne sont pas de la meme taille
	if ((iMATNbColonne != cMATelem->MATgetNbColonne()) || (iMATNbLigne != cMATelem->MATgetNbLigne())) {
		throw Cexception(252);
	}

	Cmatrice<MType>* pMATTemp = new Cmatrice(iMATNbLigne, iMATNbColonne);


	for (int iBoucle = 0; iBoucle < iMATNbLigne; iBoucle++) {
		for (int jBoucle = 0; jBoucle < iMATNbColonne; jBoucle++) {
			//simple C = A - B pour chaque cases
			pMATTemp[jBoucle][iBoucle] = pMATTab[jBoucle][iBoucle] - cMATelem->MATgetTabCase(iBoucle, jBoucle);
		}
	}


	return *pMATTemp;
	

}

template<class MType>
Cmatrice<MType>& Cmatrice<MType>::operator*(Cmatrice<MType> cMATelem)
{
	// TODO: insérer une instruction return ici
	/*Produit_matriciel(a: Matrice carr¶ee, b : Matrice carr¶ee, n :
	entier) : Matrice carr¶ee
	VAR c : Matrice carr¶ee n*n
	i : entier
	Debut
		Pour i < -1 a n Faire
			Pour j de 1 a n Faire
				c[i][j] < -0
				Pour k de 1 a n Faire
					c[i][j] < -c[i][j] + a[i][k] * b[k][j]
				Fpour
			Fpour
		Fpour
	retourner c*/

	if (cMATelem.MATgetNbLigne() != this->iMATNbColonne) {
		throw Cexception(253);
	}


	Cmatrice<MType>*pMATTemp = new Cmatrice<MType>(this->iMATNbLigne, cMATelem.MATgetNbColonne());
	MType temp;
	int iLigne, iColonne, iMult;

	for (iLigne = 0; iLigne < iMATNbLigne; iLigne++) {

		for (iColonne = 0; iColonne < cMATelem.MATgetNbColonne(); iColonne++) {

			temp = {};

			for (iMult = 0; iMult < iMATNbColonne; iMult++) {
				
				temp += pMATTab[iMult][iLigne] * cMATelem.MATgetTabCase(iMult, iColonne);

			}

			pMATTemp->MATsetTabCase(iLigne, iColonne, temp);
		}
	}


	return *pMATTemp;
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

	Cmatrice<MType>* pMATTemp = new Cmatrice(iMATNbColonne, iMATNbLigne);


	for (int iBoucleColonne = 0; iBoucleColonne < iMATNbColonne; iBoucleColonne++) {

		for (int jBoucleLigne = 0; jBoucleLigne < iMATNbLigne; jBoucleLigne++) {

			pMATTemp->MATsetTabCase(iBoucleColonne, jBoucleLigne, pMATTab[iBoucleColonne][jBoucleLigne]);
		
		}
	}


	return pMATTemp;
}

