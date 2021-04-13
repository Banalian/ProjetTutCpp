// ProjetTutPouvreauEsnault.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

//template comme méthode
/**
* @brief
* @param
* @return
*/


#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include <fstream>
#include "Cmatrice.h"
#include "FileReader.h"




int main(int argc, char *argv[])
{	
	
	//crée une matrice pour chaque argv
	Cmatrice<double>** matTab = new Cmatrice<double>*[argc - 1];

	try {
		for (int i = 1; i < argc; i++) {
			matTab[i-1] = createLfMatFromFile<double>(argv[i]);
		}
	}
	catch (Cexception e) {
		if (e.EXCLire_Code() == ERRFileNotOpen) {
			std::cout << "Erreur : incapable d'ouvrir le fichier (mauvais chemin ou mauvais nom.)" << std::endl;	
		}
		else {
			std::cout << "Erreur non definie du main" << std::endl;
		}

		return -1;
	}

	
	
	//on demande un entier à l'utilisateur
	int c;
    std::cout << "Entrez un entier\n";
	std::cin >> c;

	while(!std::cin) {
		// Si on est là, ce qu'a rentré l'utilisateur n'est pas un chiffre, on redemande donc
		std::cout << "NaN : Entrez un entier à nouveau" << std::endl;

		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		std::cin >> c;
	}

	int nbColonnes = matTab[0]->MATgetNbColonne();
	int nbLignes = matTab[0]->MATgetNbLigne();

	//Cmatrice<double> *MATsumMat = new Cmatrice<double>(nbLignes,nbColonnes);
	//Cmatrice<double> *MATaltSumMat = new Cmatrice<double>(nbLignes,nbColonnes);
	//Cmatrice<double> *MATmultMat = new Cmatrice<double>(nbLignes,nbColonnes);

	Cmatrice<double> *MATsumMat = nullptr;
	Cmatrice<double> *MATaltSumMat = nullptr;
	Cmatrice<double> *MATmultMat = nullptr;

	Cmatrice<double> **MATmultMatTab = new Cmatrice<double>*[argc - 1];
	Cmatrice<double> **MATdivMatTab = new Cmatrice<double>*[argc - 1];

	for (int iBoucle = 0; iBoucle < argc - 1; iBoucle++) {
		MATmultMatTab[iBoucle] = nullptr;
		MATdivMatTab[iBoucle] = nullptr;
	}

	Cmatrice<double> *MATtempMat = nullptr;


	for(int m = 0; m < argc-1; m++) {

		try {

			std::cout << "----------------MATRICE " << m << " -------------------------" << std::endl;

			std::cout << "Matrice * " << c << " = " << std::endl;
			//Cmatrice<double> copyMatMult(*matTab[m]);				//on multiplie chaque matrice par c
			MATmultMatTab[m] = &(*matTab[m] * c);
			//copyMatMult = copyMatMult*c;
			//copyMatMult.MATAfficherMatrice();
			MATmultMatTab[m]->MATAfficherMatrice();


			if (c == 0) {
				throw Cexception(ERRDivByZero);
			}
			std::cout << "Matrice / " << c << " = " << std::endl;
			//Cmatrice<double> copyMatDiv(*matTab[m]);					//on divise chaque matrice par c
			MATdivMatTab[m] = &(*matTab[m] / c);
			//copyMatDiv = copyMatDiv / c;
			//copyMatDiv.MATAfficherMatrice();
			MATdivMatTab[m]->MATAfficherMatrice();
			//std::cout << "^ mult and div, sum below" << std::endl;
		}
		catch (Cexception e) {

			int iCode = e.EXCLire_Code();
			switch (iCode)
			{
			case ERRDivByZero:
				std::cout << "Erreur : Division par 0 impossible, operation non effectuee sur la matrice numéro " << m << std::endl;
				break;
			default:
				break;
			}



		}

		try {

			if (m == 0) {
				MATsumMat = new Cmatrice<double>(*matTab[m]);

				MATaltSumMat = new Cmatrice<double>(*matTab[m]);

				MATmultMat = new Cmatrice<double>(*matTab[m]);
			}
			else {

				//sumMat = sumMat + *matTab[m];							//on fait la somme des matrices
				MATtempMat = &(*MATsumMat + *matTab[m]);
				delete MATsumMat;

				MATsumMat = new Cmatrice<double>(*MATtempMat);
				delete MATtempMat;
				MATtempMat = nullptr;


				//somme des matrices avec alternance des signes
				if (m % 2 != 0) {
					MATtempMat = &(*MATaltSumMat - *matTab[m]);
					delete MATaltSumMat;

					MATaltSumMat = new Cmatrice<double>(*MATtempMat);
					delete MATtempMat;
					MATtempMat = nullptr;
					//altSumMat = altSumMat - *matTab[m];
				}
				else {
					MATtempMat = &(*MATaltSumMat + *matTab[m]);
					delete MATaltSumMat;

					MATaltSumMat = new Cmatrice<double>(*MATtempMat);
					delete MATtempMat;
					MATtempMat = nullptr;
					//altSumMat = altSumMat + *matTab[m];
				}


				//produit des matrices
				MATtempMat = &(*MATmultMat * *matTab[m]);
				delete MATmultMat;
				MATmultMat = new Cmatrice<double>(*MATtempMat);
				delete MATtempMat;
				MATtempMat = nullptr;
				
				//multMat = multMat * *matTab[m];
			}


			

			

			//produit des matrices
			/*if (m == 0) { 
				multMat = *matTab[m]; 
			}
			else { 
				multMat = multMat * *matTab[m];
			}							
			*/

			//std::cout << "end of current mat" << std::endl;
		
		}
		catch (Cexception e) {
			
			int iCode = e.EXCLire_Code();
			switch (iCode)
			{
			case ERRWrongSizeAdd:
				std::cout << "Erreur : Taille des matrices differentes, addition impossible" << std::endl;
				break;
			case ERRWrongSizeMinus:
				std::cout << "Erreur : Taille des matrices differentes, soustraction impossible" << std::endl;
				break;
			case ERRWrongSizeMult:
				std::cout << "Erreur : Taille des matrices differentes, multiplication impossible" << std::endl;
				break;
			default:
				break;
			}
	


		}
		
	}

							      
	std::cout << "--------------------------------------------------" << std::endl;
	if (MATsumMat) {
		std::cout << "resultat des additions realisable des matrices : " << std::endl;
		MATsumMat->MATAfficherMatrice();

		delete MATsumMat;
	}
	
	if (MATaltSumMat) {
		std::cout << "resultat des additions puis soustractions etc  realisable des matrices : " << std::endl;
		MATaltSumMat->MATAfficherMatrice();

		delete MATaltSumMat;
	}

	if (MATmultMat) {
		std::cout << "resultat des multiplications realisable des matrices : " << std::endl;
		MATmultMat->MATAfficherMatrice();
		delete MATmultMat;
	}
	


	for (int iBoucle = 0; iBoucle < argc - 1; iBoucle++) {
		if (MATmultMatTab[iBoucle]) {
			delete MATmultMatTab[iBoucle];
		}
		if (MATdivMatTab[iBoucle]) {
			delete MATdivMatTab[iBoucle];
		}
	}

	if (MATtempMat) {
		delete MATtempMat;
	}




	for (int i = 0; i < argc - 1; i++) {
		delete matTab[i];
	}
	delete matTab;


	_CrtDumpMemoryLeaks();
	return 0;
}

