#pragma once

//cette ligne sert a désactivé les erreurs pour les commandes comme strtok()
//car elles sont dépréciées car non thread safe, mais ici étant donné que l'on est en mono-thread pas de soucis
#pragma warning(disable : 4996)

#include <iostream>
#include <fstream>
#include <cstring>
#include "Cmatrice.h"
#include "Cexception.h"
#define BUFFSIZE 2048


#define ERRFileNotOpen 200
#define ERRBadTypeFile 201
#define ERRBadColNb 202
#define ERRBadLineNb 203
#define ERRBadFormatFileMat 204
#define ERRBadFormatLineColFile 205



/**
* @brief Cree une matrice a partir d'un nom de fichier/chemin vers un fichier
* @param cPath le chemin menant a ce fichier (exemple :  Matrice/M1.txt)
* @return une matrice respectant les specification du fichier
*
* Précondition :  Le fichier doit respecter un format tres specifique, comme dit dans le sujet de ce projet.
* Si le fichier est sous un format different, le programme est susceptible de planter ou d'avoir un comportement non defini.
* Il est cependant capable de detecter les erreurs de type format de la matrice differente des informations specifiee pour nbLigne et nbColonne.
*/
template <class MType=double> Cmatrice<MType>*createLfMatFromFile(char *pcPath) {
	
	int iBoucle, jBoucle;
	char *buf;
	int iLigne = 0, iColonne = 0;

	std::fstream myFile(pcPath);
	
	

	if (myFile.is_open()) {
		

		try {
			char *line = new char[BUFFSIZE];

			myFile.getline(line, 2048);
			strtok(line, "=");
			buf = strtok(NULL, "=");
			//Test du type
			if (strcmp(buf, "double")) {
				delete line;
				myFile.close();
				throw Cexception(ERRBadTypeFile);
			}


			

			

			//RECUPERATION LIGNE
			myFile.getline(line, 2048);
			strtok(line, "=");
			buf = strtok(NULL, "=");
			//std::cout << "Ligne : buf->" << buf << " <-and line->" << line << std::endl; //debug
			if (buf == nullptr) {
				delete line;
				myFile.close();
				throw Cexception(ERRBadFormatLineColFile);
			}

			iLigne = atoi(buf);

			//RECUPERATION COLONNE
			myFile.getline(line, 2048);
			strtok(line, "=");
			buf = strtok(NULL, "=");
			//std::cout << "Colonne : buf->" << buf << " <-and line->" << line << std::endl;//debug
			if (buf == nullptr) {
				delete line;
				myFile.close();
				throw Cexception(ERRBadFormatLineColFile);
			}
			iColonne = atoi(buf);
			
			Cmatrice<double>* pMATTemp = new Cmatrice<double>(iLigne, iColonne);


			//RECUPERATION MATRICE
			myFile.getline(line, 2048);

			//pour chaque ligne du fichier, qui represente les "lignes" d'une matice
			for (iBoucle = 0; iBoucle < iLigne; iBoucle++) {
				myFile.getline(line, 2048);
				if (!strcmp(line, "]")) {
					//std::cout << "endbuf=>" << buf << std::endl;
					delete line;
					myFile.close();
					delete pMATTemp;
					throw Cexception(ERRBadLineNb);

				}

				//pour chaque element de la ligne, qui seront donc placé dans les colonnes correspondantes
				buf = strtok(line, " ");
				//std::cout << "startbuf=>" << buf << std::endl;
				for (jBoucle = 0; jBoucle < iColonne; jBoucle++) {
					if (buf == nullptr) {
						throw Cexception(ERRBadFormatFileMat);
					}
					double temp = atof(buf);
					pMATTemp->MATsetTabCase(iBoucle, jBoucle, temp);
					//std::cout << "buf=>" << buf << std::endl;
					buf = strtok(NULL, " ");
				}
				if (buf != nullptr) {
					//std::cout << "endbuf=>" << buf << std::endl;
					delete line;
					myFile.close();
					delete pMATTemp;
					throw Cexception(ERRBadColNb);

				}
				
				

			}
			myFile.getline(line, 2048);
			if (strcmp(line, "]")) {
				//std::cout << "endbuf=>" << buf << std::endl;
				delete line;
				myFile.close();
				delete pMATTemp;
				throw Cexception(ERRBadLineNb);

			}

			delete line;

			myFile.close();
			std::cout << "Nouvelle matrice de " << iLigne << " ligne(s) et " << iColonne << " colonne(s) : succes" << std::endl;
			return pMATTemp;


		}catch(Cexception e){

			int iCodeErr = e.EXCLire_Code();
			switch (iCodeErr)
			{
			case ERRHorsFomatMat:
				std::cout << "Erreur : Emplacement donne non valide (ligne ou colonne trop grand ou inferieur à 0" << std::endl;
				break;
			case ERRBadSizeMat:
				std::cout << "Erreur : Taille de Matrice invalide  :  Ligne ou Colonne < 0 " << std::endl;
				break;
			case ERRBadTypeFile:
				std::cout << "Erreur : Type demande different de double" << std::endl;
				break;
			case ERRBadColNb:
				std::cout << "Erreur : Taille incorrecte : nbColonne plus petit que le nombre de valeur trouvees dans le fichier sur la ligne" << std::endl;
				break;
			case ERRBadLineNb:
				std::cout << "Erreur : Taille incorrecte : nbLignes plus petit ou grand que le nombre de valeur/lignes trouvees dans le fichier" << std::endl;
				break;
			case ERRBadFormatFileMat:
				std::cout << "Erreur : ligne ou colonne non trouvee" << std::endl;
				break;
			case ERRBadFormatLineColFile:
				std::cout << "Erreur : nombre de ligne(s) ou de colonne(s) non trouvee" << std::endl;
				break;
			default:
				std::cout << "Erreur non repertoriee" << std::endl;
				break;
			}

			throw Cexception(ERRBadFormatFileMat);
		}

	}
	else {
		
		throw Cexception(ERRFileNotOpen);
	}
}