// ProjetTutPouvreauEsnault.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

//template comme méthode
/**
* @brief
* @param
* @return
*/

#include <iostream>
#include <fstream>
#include "Cmatrice.h"
#include "FileReader.h"

int main(int argc, char *argv[])
{	
	
	//crée une matrice pour chaque argv
	Cmatrice<double>** matTab = new Cmatrice<double>*[argc - 1];
	for (int i = 1; i < argc; i++) {
		matTab[i] = createLfMatFromFile<double>(argv[i]);
	}
	
	//on demande un entier à l'utilisateur
	int c;
    std::cout << "Entrez un entier\n";
	std::cin >> c;

	int nbColonnes = matTab[1]->MATgetNbColonne();
	int nbLignes = matTab[1]->MATgetNbLigne();

	Cmatrice<double> sumMat(nbLignes,nbColonnes);
	Cmatrice<double> altSumMat(nbLignes,nbColonnes);
	Cmatrice<double> multMat(nbLignes,nbColonnes);

	for (int m = 1; m < argc; m++) {


		Cmatrice<double> copyMatMult(*matTab[m]);				//on multiplie chaque matrice par c
		copyMatMult*c;
		copyMatMult.MATAfficherMatrice();

		Cmatrice<double> copyMatDiv(*matTab[m]);					//on divise chaque matrice par c
		copyMatDiv/c;
		copyMatDiv.MATAfficherMatrice();

		sumMat = sumMat + matTab[m];							//on fait la somme des matrices
		if (m % 2 != 0) { altSumMat = altSumMat + matTab[m]; }	//somme des matrices avec alternance des signes
		else { altSumMat = altSumMat - matTab[m]; }
		multMat = multMat * *matTab[m];							//produit des matrices
	}

	sumMat.MATAfficherMatrice();
	altSumMat.MATAfficherMatrice();
	multMat.MATAfficherMatrice();

	for (int i = 1; i < argc - 1; i++) {
		delete matTab[i];
	}
	delete matTab;

}

