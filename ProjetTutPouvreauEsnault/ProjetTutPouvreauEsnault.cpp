// ProjetTutPouvreauEsnault.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

//template comm méthode
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
		std::fstream myFile(argv[i]);
		matTab[i] = createLfMatFromFile<double>(&myFile);
	}
	
	//on demande un entier à l'utilisateur
	int c;
    std::cout << "Entrez un entier\n";
	std::cin >> c;

	

	//on multiplie chaque matrice par c
	//on divise chaque matrice par c
	//on fait la somme des matrices
	//somme des matrices avec alternance des signes
	//produit des matrices

	for (int i = 1; i < argc - 1; i++) {
		delete matTab[i];
	}
	delete matTab;


	/*Cmatrice<int> testMat(3,3);
	Cmatrice<float> testMatf(4, 4);

	testMat.MATsetTabCase(2, 2, 3);
	testMatf.MATsetTabCase(2, 2, 5.978);


	Cmatrice<int> testMatCopy(testMat);
	testMat.MATsetTabCase(2, 2, 5);



	std::cout << "case int 2 2 : " << testMatCopy.MATgetTabCase(2, 2) << std::endl;*/

	std::fstream myFile("testFile.txt");

	Cmatrice<double>* matDouble = createLfMatFromFile<double>(&myFile);

	

	

	if (matDouble != nullptr) {

		Cmatrice<double>* copyMat = new Cmatrice(*matDouble);

		Cmatrice<double>* copyMatTransp = copyMat->MATTranspMat();

		Cmatrice<double>* testMult = &(*matDouble * *copyMatTransp);


		testMult->MATAfficherMatrice();
		std::cout << std::endl << "fintest mult" << std::endl;

		delete copyMat;
		delete copyMatTransp;
		delete testMult;




		matDouble->MATAfficherMatrice();
		Cmatrice<double>*matDoubleT = matDouble->MATTranspMat();
		matDoubleT->MATAfficherMatrice();
		delete matDouble;
		delete matDoubleT;
	}
	


	return 0;
	
}

