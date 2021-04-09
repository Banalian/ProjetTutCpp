#pragma once
#pragma warning(disable : 4996)

#include <iostream>
#include <fstream>
#include <cstring>
#include "Cmatrice.h"
#include "Cexception.h"
#define BUFFSIZE 2048


#define ERRHorsFomatMat 101
#define ERRBadSizeMat 102
#define ERRBadTypeFile 201
#define ERRBadColNb 202
#define ERRBadLineNb 203
#define ERRWrongSizeAdd 251
#define ERRWrongSizeMinus 252


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
			case ERRHorsFomatMat:
				std::cout << "Erreur : Emplacement donné non valide (ligne ou colonne trop grand ou inférieur à 0" << std::endl;
				break;
			case ERRBadSizeMat:
				std::cout << "Erreur : Taille de Matrice invalide  :  Ligne ou Colonne < 0 " << std::endl;
				break;
			case ERRBadTypeFile:
				std::cout << "Erreur : Type demandé différent de double" << std::endl;
				break;
			case ERRBadColNb:
				std::cout << "Erreur : Taille incorrecte : nbColonne plus petit que le nombre de valeur trouvées dans le fichier sur la ligne" << std::endl;
				break;
			case ERRBadLineNb:
				std::cout << "Erreur : Taille incorrecte : nbLignes plus petit que le nombre de valeur/lignes trouvées dans le fichier" << std::endl;
				break;
			case ERRWrongSizeAdd:
				std::cout << "Erreur : Taille des matrices différentes, addition impossible" << std::endl;
				break;
			case ERRWrongSizeMinus:
				std::cout << "Erreur : Taille des matrices différentes, soustraction impossible" << std::endl;
				break;
			default:
				std::cout << "Erreur non repertoriée" << std::endl;
				break;
			}
			return nullptr;
		}

	}
	else {
		std::cout << "Unable to open file." << std::endl;
	}
}