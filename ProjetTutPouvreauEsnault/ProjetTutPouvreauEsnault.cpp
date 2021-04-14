// ProjetTutPouvreauEsnault.cpp : Réalisé par Corentin Esnault et Pouvreau Lilian
//

//template comme méthode
/**
* @brief
* @param
* @return
*/


/*DECOMMENTER POUR CHECK LES MEM LEAK (+ _CrtDumpMemoryLeaks(); juste avant le return*/
/**/
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>




#include <iostream>
#include <fstream>
#include "Cmatrice.h"
#include "FileReader.h"




int main(int argc, char *argv[])
{	
	
	if (argc < 2) {
		std::cout << "Erreur :  aucune matrice fournie en paramètre, arrêt du programme" << std::endl;
		return -1;
	}


	//---------------------------------------Lecture du/des fichiers--------------------------------------------------//

	//On cree une matrice pour chaque argv
	Cmatrice<double>** pMATtab = new Cmatrice<double>*[argc - 1];

	//On essaye de lire chacun des fichiers en paramtre pour en sortir des matrices stockees dans le tableau
	try {
		for (int i = 1; i < argc; i++) {
			pMATtab[i-1] = createLfMatFromFile<double>(argv[i]);
		}
	}
	catch (Cexception e) {
		if (e.EXCLire_Code() == ERRFileNotOpen) {
			std::cout << "Erreur : incapable d'ouvrir le fichier (mauvais chemin ou mauvais nom.)" << std::endl;	
		}

		if (e.EXCLire_Code() == ERRBadFormatFileMat) {
			std::cout << "Erreur : Une matrice n'avait pas un format correct : arret du programme" << std::endl;
		}
		else {
			std::cout << "Erreur non definie du main" << std::endl;
		}

		return -1;
	}

	//----------------------------------------------------------------------------------------------------------------//

	
	//--------------------------------------------Recuperation de la variable-----------------------------------------//

	
	int iChiffreUser;
    std::cout << "Entrez un entier\n";
	std::cin >> iChiffreUser;

	//!std::cin => check si la valeur entrée est du format de celle attendu
	while(!std::cin) {
		// Si on est là, ce qu'a rentré l'utilisateur n'est pas un chiffre, on redemande donc
		std::cout << "NaN : Entrez un entier à nouveau" << std::endl;

		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		std::cin >> iChiffreUser;
	}



	//----------------------------------------------------------------------------------------------------------------//


	//--------------Initialisation de toutes les variables necessaires au calculs et a l'afficaghe--------------------//

	Cmatrice<double> *MATsumMat		= nullptr;
	Cmatrice<double> *MATaltSumMat	= nullptr;
	Cmatrice<double> *MATmultMat	= nullptr;

	Cmatrice<double> **MATmultMatTab = new Cmatrice<double>*[argc - 1];
	Cmatrice<double> **MATdivMatTab  = new Cmatrice<double>*[argc - 1];


	//Ces variables servent a verifier si une operation n'a pas ete realisee, ce qui sera afficher a la fin du programme avant l'affichage
	int *iSuccessMult = new int[argc - 1];
	int *iSuccessAdd  = new int[argc - 1];
	int iBadAdd = 0;
	int iBadMult = 0;



	for (int iBoucle = 0; iBoucle < argc - 1; iBoucle++) {
		MATmultMatTab[iBoucle] = nullptr;
		MATdivMatTab[iBoucle] = nullptr;
		iSuccessMult[iBoucle] = 1;
		iSuccessAdd[iBoucle] = 1;
	}

	Cmatrice<double> *MATtempMat = nullptr;


	//----------------------------------------------------------------------------------------------------------------//


	//--------------------------------------Calculs-------------------------------------------------------------------//


	for(int iCurrentMat = 0; iCurrentMat < argc-1; iCurrentMat++) {

		try {

			std::cout << "----------------MATRICE " << iCurrentMat << " -------------------------" << std::endl;

			//On multiplie chaque matrice par iChiffreUser
			std::cout << "Matrice * " << iChiffreUser << " = " << std::endl;
			MATmultMatTab[iCurrentMat] = &(*pMATtab[iCurrentMat] * iChiffreUser);

			MATmultMatTab[iCurrentMat]->MATAfficherMatrice();


			if (iChiffreUser == 0) {
				throw Cexception(ERRDivByZero);
			}


			//On divise chaque matrice par iChiffreUser
			std::cout << "Matrice / " << iChiffreUser << " = " << std::endl;
			MATdivMatTab[iCurrentMat] = &(*pMATtab[iCurrentMat] / iChiffreUser);

			MATdivMatTab[iCurrentMat]->MATAfficherMatrice();

		}
		catch (Cexception e) {

			int iCode = e.EXCLire_Code();
			switch (iCode)
			{
			case ERRDivByZero:
				std::cout << "Erreur : Division par 0 impossible, operation non effectuee sur la matrice numero " << iCurrentMat << std::endl;
				break;
			default:
				break;
			}

		}



		try {

			if (iCurrentMat == 0) {
				MATsumMat = new Cmatrice<double>(*pMATtab[iCurrentMat]);

				MATaltSumMat = new Cmatrice<double>(*pMATtab[iCurrentMat]);

			}
			else {

				//On fait la somme des matrices
				MATtempMat = &(*MATsumMat + *pMATtab[iCurrentMat]);
				delete MATsumMat;

				MATsumMat = new Cmatrice<double>(*MATtempMat);
				delete MATtempMat;
				MATtempMat = nullptr;


				//Somme des matrices avec alternance des signes
				if (iCurrentMat % 2 != 0) {
					MATtempMat = &(*MATaltSumMat - *pMATtab[iCurrentMat]);
					delete MATaltSumMat;

					MATaltSumMat = new Cmatrice<double>(*MATtempMat);
					delete MATtempMat;
					MATtempMat = nullptr;

					//Equivalent a MATaltSumMat = MATaltSumMat - pMATtab[iCurrentMat];
				}
				else {
					MATtempMat = &(*MATaltSumMat + *pMATtab[iCurrentMat]);
					delete MATaltSumMat;

					MATaltSumMat = new Cmatrice<double>(*MATtempMat);
					delete MATtempMat;
					MATtempMat = nullptr;

					//Equivalent a MATaltSumMat = MATaltSumMat + pMATtab[iCurrentMat];
				}
				
			}


		
		}
		catch (Cexception e) {
			
			int iCode = e.EXCLire_Code();
			switch (iCode)
			{
			case ERRWrongSizeAdd:
				std::cout << "Erreur : Taille des matrices differentes, addition impossible pour la matrice numero " << iCurrentMat << std::endl;
				break;
			case ERRWrongSizeMinus:
				std::cout << "Erreur : Taille des matrices differentes, soustraction impossible pour la matrice numero " << iCurrentMat << std::endl;
				break;
			default:
				break;
			}
			
			//une erreur est survenu, on garde en memoire quelle matrice n'a pas pu etre utilisee
			iSuccessAdd[iCurrentMat] = 0;
			iBadAdd = 1;
		}


		try {

			if (iCurrentMat == 0) {
				MATmultMat = new Cmatrice<double>(*pMATtab[iCurrentMat]);
			}
			else {
				//produit des matrices
				MATtempMat = &(*MATmultMat * *pMATtab[iCurrentMat]);
				delete MATmultMat;
				MATmultMat = new Cmatrice<double>(*MATtempMat);
				delete MATtempMat;
				MATtempMat = nullptr;

				//Equivalent a MATmultMat = MATmultMat * pMATtab[iCurrentMat];
			}
			
		}
		catch (Cexception e) {

			int iCode = e.EXCLire_Code();
			switch (iCode)
			{
			case ERRWrongSizeMult:
				std::cout << "Erreur : Taille des matrices incorrectes, multiplication impossible/non defini pour la matrice numero " << iCurrentMat << std::endl;
				break;
			default:
				break;
			}

			//une erreur est survenu, on garde en memoire quelle matrice n'a pas pu etre utilisee
			iSuccessMult[iCurrentMat] = 0;
			iBadMult = 1;


		}
		
	}
							      
	std::cout << "--------------------------------------------------" << std::endl;

	//----------------------------------------------------------------------------------------------------------------//


	//---------------------------------Affichage des erreurs s'il y en a eu lors des operations-----------------------//


	if (iBadAdd) {
		std::cout << "Une ou plusieurs matrice n'ont pas pu etre additionnee : ";
		for (int iBoucle = 0; iBoucle < argc - 1; iBoucle++) {
			if (iSuccessAdd[iBoucle] == 0) {
				std::cout << "Matrice numero " << iBoucle <<"; ";
			}
		}
		std::cout << std::endl;
	}

	if (iBadMult) {
		std::cout << "Une ou plusieurs matrice n'ont pas pu etre multipliee : ";
		for (int iBoucle = 0; iBoucle < argc - 1; iBoucle++) {
			if (iSuccessMult[iBoucle] == 0) {
				std::cout << "Matrice numero " << iBoucle << "; ";
			}
		}
		std::cout << std::endl;
	}


	//----------------------------------------------------------------------------------------------------------------//


	//---------------------------Affichage des matrices finales, puis suppression-------------------------------------//

	if (MATsumMat) {
		std::cout << std::endl << "Resultat des additions realisable des matrices : " << std::endl;
		MATsumMat->MATAfficherMatrice();

		delete MATsumMat;
	}
	
	if (MATaltSumMat) {
		std::cout << std::endl << "Resultat des additions puis soustractions etc  realisable des matrices : " << std::endl;
		MATaltSumMat->MATAfficherMatrice();

		delete MATaltSumMat;
	}

	if (MATmultMat) {
		std::cout << std::endl << "Resultat des multiplications realisable des matrices : " << std::endl;
		MATmultMat->MATAfficherMatrice();
		delete MATmultMat;
	}
	
	//----------------------------------------------------------------------------------------------------------------//




	//---------------------------Delete de tout les tableaux alloues dynamiquement------------------------------------//




	for (int iBoucle = 0; iBoucle < argc - 1; iBoucle++) {
		if (MATmultMatTab[iBoucle]) {
			delete MATmultMatTab[iBoucle];
		}
		if (MATdivMatTab[iBoucle]) {
			delete MATdivMatTab[iBoucle];
		}
	}


	delete[] MATmultMatTab;
	delete[] MATdivMatTab;


	delete[] iSuccessMult;
	delete[] iSuccessAdd;

	if (MATtempMat) {
		delete MATtempMat;
	}


	for (int i = 0; i < argc - 1; i++) {
		delete pMATtab[i];
	}
	delete[] pMATtab;

	//----------------------------------------------------------------------------------------------------------------//



	//commentez ou decommentez pur verifier les mem leaks
	//
	_CrtDumpMemoryLeaks();
	return 0;
}

