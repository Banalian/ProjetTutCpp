#pragma once
#pragma warning(disable : 4996)

#include <iostream>
#include <fstream>
#include <cstring>
#include "Cmatrice.h"
#include "Cexception.h"
#define BUFFSIZE 2048


template <class MType> Cmatrice<MType>*createLfMatFromFile(std::fstream *myFile) {

	

	if (myFile->is_open()) {
		

		try {
			char *line = new char[BUFFSIZE];

			myFile->getline(line, 2048);

			//std::cout << line << "<end" << std::endl;
			if (strcmp(line, "TypeMatrice=double")) {
				delete line;
				myFile->close();
				throw Cexception(201);
			}


			

			char *buf;
			int iLigne = 0, iColonne = 0;

			//RECUPERATION LIGNE
			myFile->getline(line, 2048);
			strtok(line, "=");
			buf = strtok(NULL, "=");
			//std::cout << "Ligne : buf->" << buf << " <-and line->" << line << std::endl;
			iLigne = atoi(buf);

			//RECUPERATION COLONNE
			myFile->getline(line, 2048);
			strtok(line, "=");
			buf = strtok(NULL, "=");
			//std::cout << "Colonne : buf->" << buf << " <-and line->" << line << std::endl;
			iColonne = atoi(buf);

			std::cout << "Nouvelle matrice de " << iLigne << " Ligne(s) et " << iColonne << " Colonne(s)" << std::endl;
			
			Cmatrice<double>* pMATTemp = new Cmatrice<double>(iLigne, iColonne);


			//RECUPERATION MATRICE
			myFile->getline(line, 2048);

			//pour chaque ligne du fichier, qui represente les "lignes" d'une matice
			for (int iBoucle = 0; iBoucle < iLigne; iBoucle++) {
				myFile->getline(line, 2048);

				//pour chaque element de la ligne, qui seront donc placé dans les colonnes correspondantes
				buf = strtok(line, " ");
				//std::cout << "startbuf=>" << buf << std::endl;
				for (int jBoucle = 0; jBoucle < iColonne; jBoucle++) {
					double temp = atof(buf);
					pMATTemp->MATsetTabCase(iBoucle, jBoucle, temp);
					//std::cout << "buf=>" << buf << std::endl;
					buf = strtok(NULL, " ");
				}
				if (buf != nullptr) {
					//std::cout << "endbuf=>" << buf << std::endl;
					delete line;
					myFile->close();
					delete pMATTemp;
					throw Cexception(202);

				}
				
				

			}
			myFile->getline(line, 2048);
			if (strcmp(line, "]")) {
				//std::cout << "endbuf=>" << buf << std::endl;
				delete line;
				myFile->close();
				delete pMATTemp;
				throw Cexception(203);

			}

			delete line;

			myFile->close();

			return pMATTemp;


		}catch(Cexception e){

			int codeErr = e.EXCLire_Code();
			switch (codeErr)
			{
			case 201: 
				std::cout << "Erreur :  type demandé différent de double" << std::endl;
				break;
			case 202:
				std::cout << "Erreur : taille incorrecte : nbColonne plus petit que le nombre de valeur trouvées dans le fichier sur la ligne" << std::endl;
				break;
			case 203:
				std::cout << "Erreur : taille incorrecte : nbLignes plus petit que le nombre de valeur/lignes trouvées dans le fichier" << std::endl;
				break;
			default:
				break;
			}
			return nullptr;
		}

	}
	else {
		std::cout << "Unable to open file." << std::endl;
	}
}