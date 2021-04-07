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

			std::cout << line << "<end" << std::endl;
			if (line != "TypeMatrice=double") {
				throw Cexception(201);
			}


			//myFile->getline(line, 2048);

			//char *buf;

			//buf = strtok(line, "=");

			//std::cout << "buf->" << buf << std::endl;

		}catch(Cexception e){

			int codeErr = e.EXCLire_Code();
			switch (codeErr)
			{
			case 201: 
				std::cout << "Erreur :  type demandé différent de double" << std::endl;
			default:
				break;
			}
		}

	}
	else {
		std::cout << "Unable to open file." << std::endl;
	}
}