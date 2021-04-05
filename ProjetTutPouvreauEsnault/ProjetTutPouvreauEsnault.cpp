// ProjetTutPouvreauEsnault.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

//template comm méthode
/**
* @brief
* @param
* @return
*/

#include <iostream>
#include "Cmatrice.h"

int main()
{
    std::cout << "Hello World!\n"; 

	Cmatrice<int> testMat(3,3);
	Cmatrice<float> testMatf(4, 4);

	testMat.MATsetTabCase(2, 2, 3);
	testMatf.MATsetTabCase(2, 2, 5.978);


	Cmatrice<int> testMatCopy(testMat);
	testMat.MATsetTabCase(2, 2, 5);


	std::cout << "case int 2 2 : " << testMatCopy.MATgetTabCase(2, 2) << std::endl;


	
}

