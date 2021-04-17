#include "Cmatrice.h"


/**
* @brief Constructeur par defaut : Fabrique une matrice vide de taille 1 1 (constructeur par defaut)
* @return l'objet cree
*/
template<class MType>
Cmatrice<MType>::Cmatrice()
{

	iMATNbColonne = 1;
	iMATNbLigne = 1;

	pMTYTab = new MType*[1];
	pMTYTab[0] = new MType[1];

	pMTYTab[0][0] = {};

}

/**
* @brief Fabrique une matrice vide de taille iNbLigne iNbColonne
* @param iNbLigne nombre de ligne(s) de la matrice
* @param iNbColonne nombre de colonne(s) de la matrice
* @return l'objet cree
*/
template<class MType>
Cmatrice<MType>::Cmatrice(int iNbLigne, int iNbColonne)
{
	if (iNbColonne < 0 || iNbLigne < 0) {
		throw Cexception(ERRBadSizeMat);
	}
	int iBoucle, ii, ij;

	iMATNbColonne = iNbColonne;
	iMATNbLigne = iNbLigne;

	pMTYTab = new MType*[iMATNbColonne];

	for (iBoucle = 0; iBoucle < iMATNbColonne; iBoucle++) {
		pMTYTab[iBoucle] = new MType[iMATNbLigne];
	}

	for (ii = 0; ii < iMATNbColonne; ii -= -1) {

		for (ij = 0; ij < iMATNbLigne; ij -= -1) {

			pMTYTab[ii][ij] = {};

		}
	}
}


/**
* @brief Constructeur de recopie : cree une copie d'une matrice
* @param MATMatrice la matrice a copier
* @return l'objet cree
*/
template<class MType>
Cmatrice<MType>::Cmatrice(Cmatrice<MType> & MATMatrice)
{
	int iBoucle, ii, ij;

	iMATNbColonne = MATMatrice.MATgetNbColonne();
	iMATNbLigne = MATMatrice.MATgetNbLigne();

	pMTYTab = new MType*[iMATNbColonne];

	for (iBoucle = 0; iBoucle < iMATNbColonne; iBoucle++) {
		pMTYTab[iBoucle] = new MType[iMATNbLigne];
	}



	for (ii = 0; ii < iMATNbColonne; ii -= -1) {

		for (ij = 0; ij < iMATNbLigne; ij -= -1) {

			pMTYTab[ii][ij] = MATMatrice.pMTYTab[ii][ij];

		}
	}
}


/**
* @brief Destructeur de l'objet matrice
*/
template<class MType>
Cmatrice<MType>::~Cmatrice()
{
	int iBoucle;

	for (iBoucle = 0; iBoucle < iMATNbColonne; iBoucle++) {
		delete[] pMTYTab[iBoucle];
	}
	delete[] pMTYTab;
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
* @brief change le nombre de ligne du tableau. ATTENTION :  toute donnee hors format sera perdue (mais non detruite) et les nouvelles cases seront vide
* @param le nouveau nombre de ligne
*/
template<class MType>
void Cmatrice<MType>::MATsetNbLigne(int iLigne)
{
	if (iLigne < 0) {
		throw Cexception(ERRBadNewLineCol);
	}

	int ligne, iBoucle, jBoucle;

	if (iLigne < iMATNbLigne) {
		ligne = iLigne;
	}
	else {
		ligne = iMATNbLigne;
	}


	//on cree un nouveau tableau de la bonne taille
	MType** pMTYTemp = new MType*[iMATNbColonne];

	for (iBoucle = 0; iBoucle < iMATNbColonne; iBoucle++) {
		pMTYTemp[iBoucle] = new MType[iLigne];
	}

	//on recopie les valeurs du tableau actuel dans le tableau qui le remplacera
	for (iBoucle = 0; iBoucle < iMATNbColonne; iBoucle++) {

		for (jBoucle = 0; jBoucle < ligne; jBoucle++) {

			pMTYTemp[iBoucle][jBoucle] = pMTYTab[iBoucle][jBoucle];

		}
	}


	//on supprime l'ancien tableau
	for (iBoucle = 0; iBoucle < iMATNbColonne; iBoucle++) {
		delete[] pMTYTab[iBoucle];
	}
	delete[] pMTYTab;


	iMATNbLigne = iLigne;
	pMTYTab = pMTYTemp;
}


/**
* @brief change le nombre de colonne du tableau. ATTENTION :  toute donnee hors format sera perdue (mais non detruite) et les nouvelles cases seront vide
* @param le nouveau nombre de colonne
*/
template<class MType>
void Cmatrice<MType>::MATsetNbColonne(int iColonne)
{
	if (iColonne < 0) {
		throw Cexception(ERRBadNewLineCol);
	}
	int colonne = 0, iBoucle, jBoucle;

	if (iColonne < iMATNbColonne) {
		colonne = iColonne;
	}
	else {
		colonne = iMATNbColonne;
	}



	//on cree un nouveau tableau de la bonne taille
	MType** pMTYTemp = new MType*[iColonne];
	for (iBoucle = 0; iBoucle < iColonne; iBoucle++) {
		pMTYTemp[iBoucle] = new MType[iMATNbLigne];
	}

	//on recopie les valeurs du tableau actuel dans le tableau qui le remplacera
	for (iBoucle = 0; iBoucle < colonne; iBoucle++) {

		for (jBoucle = 0; jBoucle < iMATNbLigne; jBoucle++) {

			pMTYTemp[iBoucle][jBoucle] = pMTYTab[iBoucle][jBoucle];

		}
	}



	//on supprime l'ancien tableau
	for (iBoucle = 0; iBoucle < iMATNbColonne; iBoucle++) {
		delete[] pMTYTab[iBoucle];
	}
	delete[] pMTYTab;


	iMATNbColonne = iColonne;
	pMTYTab = pMTYTemp;
}


/**
* @brief recupere une COPIE du tableau de la matrice
* @return un pointeur vers une COPIE du tableau de la matrice
*/
template<class MType>
MType ** Cmatrice<MType>::MATgetTabCopy()
{
	int iBoucle, jBoucle;
	MType** pMTYtemp = new MType*[iMATNbColonne];

	for (iBoucle = 0; iBoucle < iMATNbColonne; iBoucle++) {
		pMTYtemp[iBoucle] = new MType[iMATNbLigne];
	}

	for (iBoucle = 0; iBoucle < iMATNbLigne; iBoucle++) {

		for (jBoucle = 0; jBoucle < iMATNbColonne; jBoucle++) {

			pMTYtemp[jBoucle][iBoucle] = MATgetTabCase(iBoucle, jBoucle);

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
* @brief recupere une case de la matrice precise
* @param iLigne la ligne où est la case souhaitee
* @param iColonne la colonne où est la case souhaitee
* @return un pointeur vers la variable contenu dans la case
*/
template<class MType>
MType Cmatrice<MType>::MATgetTabCase(int iLigne, int iColonne)
{
	if (iColonne >= iMATNbColonne || iLigne >= iMATNbLigne || iColonne < 0 || iLigne < 0) {
		throw Cexception(ERRHorsFomatMat);
	}
	return (pMTYTab[iColonne][iLigne]);
}


/**
* @brief remplit une case de la matrice avec une variable
* @param iLigne la ligne où est la case que l'on veut remplir
* @param iColonne la colonne où est la case que l'on veut remplir
* @param elem l'element a mettre dans la case (on utilise =, donc operateur a surcharger selon vos besoins)
*/
template<class MType>
void Cmatrice<MType>::MATsetTabCase(int iLigne, int iColonne, MType elem)
{


	if (iColonne > iMATNbColonne || iLigne > iMATNbLigne || iColonne < 0 || iLigne < 0) {
		throw Cexception(ERRHorsFomatMat);
	}

	pMTYTab[iColonne][iLigne] = elem;


}






/**
* @brief Affiche la Matrice dans la sortie standard. ATTENTION : Prevoir l'operation si elle n'est pas dejà definie (operateur <<)
*/
template<class MType>
void Cmatrice<MType>::MATAfficherMatrice()
{
	int iBoucle, jBoucle;

	for (iBoucle = 0; iBoucle < iMATNbLigne; iBoucle++) {
		for (jBoucle = 0; jBoucle < iMATNbColonne; jBoucle++) {
			std::cout << pMTYTab[jBoucle][iBoucle] << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}



/**
* @brief multiplie une matrice par un element elem (chaque case * elem)
* @param elem l'elem par lequel tt les cases seront multipliees
* @return une nouvelle matrice qui est le resultat de matrice * elem
*/
template<class MType>
Cmatrice<MType>& Cmatrice<MType>::operator*(MType elem)
{
	Cmatrice<MType>* pMATTemp = new Cmatrice(iMATNbLigne, iMATNbColonne);
	MType temp;
	int iBoucle, jBoucle;


	for (iBoucle = 0; iBoucle < iMATNbLigne; iBoucle++) {
		for (jBoucle = 0; jBoucle < iMATNbColonne; jBoucle++) {
			temp = pMTYTab[jBoucle][iBoucle] * elem;
			pMATTemp->MATsetTabCase(iBoucle, jBoucle, temp);
		}
	}

	return *pMATTemp;
}

/**
* @brief divise une matrice par un element elem (chaque case / elem)
* @param elem l'elem par lequel tt les cases seront divisees
* @return une nouvelle matrice qui est le resultat de matrice / elem
*/
template<class MType>
Cmatrice<MType>& Cmatrice<MType>::operator/(MType elem)
{

	Cmatrice<MType>* pMATTemp = new Cmatrice(iMATNbLigne, iMATNbColonne);
	MType temp;
	int iBoucle, jBoucle;

	for (iBoucle = 0; iBoucle < iMATNbLigne; iBoucle++) {
		for (jBoucle = 0; jBoucle < iMATNbColonne; jBoucle++) {
			temp = pMTYTab[jBoucle][iBoucle] / elem;
			pMATTemp->MATsetTabCase(iBoucle, jBoucle, temp);
		}
	}

	return *pMATTemp;
}


/**
* @brief additionne deux matrices
* @param MATelem la matrice a additionner
* @return une nouvelle matrice qui est le resultat de matrice + matrice
*/
template<class MType>
Cmatrice<MType>& Cmatrice<MType>::operator+(Cmatrice<MType> MATelem)
{

	//Si les matrices ne sont pas de la meme taille
	if ((iMATNbColonne != MATelem.MATgetNbColonne()) || (iMATNbLigne != MATelem.MATgetNbLigne())) {
		throw Cexception(ERRWrongSizeAdd);
	}

	Cmatrice<MType>* pMATTemp = new Cmatrice(iMATNbLigne, iMATNbColonne);
	MType temp;
	int iBoucle, jBoucle;

	for (iBoucle = 0; iBoucle < iMATNbLigne; iBoucle++) {
		for (jBoucle = 0; jBoucle < iMATNbColonne; jBoucle++) {
			//simple C = A + B pour chaque cases
			temp = pMTYTab[jBoucle][iBoucle] + MATelem.MATgetTabCase(iBoucle, jBoucle);
			pMATTemp->MATsetTabCase(iBoucle, jBoucle, temp);
		}
	}


	return *pMATTemp;



}


/**
* @brief soustrait deux matrices
* @param MATelem la matrice que l'on va soustraire
* @return une nouvelle matrice qui est le resultat de matrice - matrice
*/
template<class MType>
Cmatrice<MType>& Cmatrice<MType>::operator-(Cmatrice<MType> MATelem)
{


	//Si les matrices ne sont pas de la meme taille
	if ((iMATNbColonne != MATelem.MATgetNbColonne()) || (iMATNbLigne != MATelem.MATgetNbLigne())) {
		throw Cexception(ERRWrongSizeMinus);
	}

	Cmatrice<MType>* pMATTemp = new Cmatrice(iMATNbLigne, iMATNbColonne);
	MType temp;
	int iBoucle, jBoucle;

	for (iBoucle = 0; iBoucle < iMATNbLigne; iBoucle++) {
		for (jBoucle = 0; jBoucle < iMATNbColonne; jBoucle++) {
			//simple C = A - B pour chaque cases
			temp = pMTYTab[jBoucle][iBoucle] - MATelem.MATgetTabCase(iBoucle, jBoucle);
			pMATTemp->MATsetTabCase(iBoucle, jBoucle, temp);
		}
	}


	return *pMATTemp;


}

/**
* @brief multiplie deux matrices
* @param MATelem la matrice a multiplier
* @return une nouvelle matrice qui est le resultat de matrice * matrice
*/
template<class MType>
Cmatrice<MType>& Cmatrice<MType>::operator*(Cmatrice<MType> MATelem)
{

	if (MATelem.MATgetNbLigne() != this->iMATNbColonne) {
		throw Cexception(ERRWrongSizeMult);
	}


	Cmatrice<MType>*pMATTemp = new Cmatrice<MType>(this->iMATNbLigne, MATelem.MATgetNbColonne());
	MType temp;
	int iLigne, iColonne, iMult;

	for (iLigne = 0; iLigne < iMATNbLigne; iLigne++) {

		for (iColonne = 0; iColonne < MATelem.MATgetNbColonne(); iColonne++) {

			temp = {};

			for (iMult = 0; iMult < iMATNbColonne; iMult++) {

				temp += pMTYTab[iMult][iLigne] * MATelem.MATgetTabCase(iMult, iColonne);

			}

			pMATTemp->MATsetTabCase(iLigne, iColonne, temp);
		}
	}


	return *pMATTemp;
}


/**
* @brief Surcharge du = => equivalent au constructeur de recopie
* @param MATelem la matrice a copier
* @return la matrice copiee
*/
template<class MType>
Cmatrice<MType>& Cmatrice<MType>::operator=(Cmatrice<MType> &MATelem)
{
	
	int iBoucle;

	iMATNbLigne = MATelem.iMATNbLigne();
	iMATNbColonne = MATelem.iMATNbColonne();


	if (pMTYTab) {
		for (iBoucle = 0; iBoucle < iMATNbColonne; iBoucle++) {
			delete[] pMTYTab[iBoucle];
		}
		delete[] pMTYTab;
	}
	pMTYTab = MATelem.MATgetTabCopy();

	//Cmatrice<MType> * pMATTemp = new Cmatrice<MType>(MATelem);//old incorrect way
	return *this;
}



/**
* @brief donne la transposee d'une matrice
* @return un pointeur vers une nouvelle matrice qui est la transposee de celle actuelle
*/
template<class MType>
Cmatrice<MType> * Cmatrice<MType>::MATTranspMat()
{
	int iBoucleColonne, jBoucleLigne;
	Cmatrice<MType>* pMATTemp = new Cmatrice(iMATNbColonne, iMATNbLigne);


	for (iBoucleColonne = 0; iBoucleColonne < iMATNbColonne; iBoucleColonne++) {

		for (jBoucleLigne = 0; jBoucleLigne < iMATNbLigne; jBoucleLigne++) {

			pMATTemp->MATsetTabCase(iBoucleColonne, jBoucleLigne, pMTYTab[iBoucleColonne][jBoucleLigne]);

		}
	}


	return pMATTemp;
}



/**
* @brief Surcharge de << => sert a output plus facilement une matrice
* exemple : std::cout << matrice;
* @param out le flux probablement std::cout la plupart du temps
* @param MATelem la Matrice a afficher
*/
template <class MType>
std::ostream& operator<<(std::ostream& out, Cmatrice<MType> & MATelem) {
	//...
	int nbLigne = MATelem.MATgetNbLigne();
	int nbColonne = MATelem.MATgetNbColonne();
	int iBoucle, jBoucle;

	for (iBoucle = 0; iBoucle < nbLigne; iBoucle++) {
		for (jBoucle = 0; jBoucle < nbColonne; jBoucle++) {
			out << MATelem.MATgetTabCase(iBoucle, jBoucle) << "\t";
		}
		out << std::endl;
	}
	out << std::endl;

	return out;
}