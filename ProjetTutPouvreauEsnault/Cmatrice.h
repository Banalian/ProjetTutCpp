#pragma once
#include "Cexception.h"

#define ERRHorsFomatMat 101
#define ERRBadSizeMat 102
#define ERRWrongSizeAdd 151
#define ERRWrongSizeMinus 152
#define ERRWrongSizeMult 153

template <class MType> class Cmatrice
{
private:
	int iMATNbLigne;
	int iMATNbColonne;
	MType ** pMATTab = {};

public:
	Cmatrice(int iNbLigne, int iNbColonne); //DONE
	Cmatrice(Cmatrice<MType> &cMATMatrice); //DONE
	~Cmatrice(); //DONE /TO TEST

	int  MATgetNbLigne(); //DONE
	int  MATgetNbColonne(); //DONE

	void MATsetNbLigne(int iLigne); //DONE
	void MATsetNbColonne(int iColonne); //DONE

	MType** MATgetTabCopy(); //DONE
	Cmatrice* MATgetMatCopy(); //DONE

	MType MATgetTabCase(int iLigne, int iColonne); //DONE
	void MATsetTabCase(int iLigne, int iColonne, MType elem); //DONE

	void MATAfficherMatrice(); //DONE


	Cmatrice<MType>& operator*(MType elem); //DONE
	Cmatrice<MType>& operator/(MType elem); //DONE

	Cmatrice<MType>& operator+(Cmatrice<MType> cMATelem); //DONE
	Cmatrice<MType>& operator-(Cmatrice<MType> cMATelem); //DONE
	Cmatrice<MType>& operator*(Cmatrice<MType> cMATelem); //JE M'EN OCCUPE LILIAN


	Cmatrice<MType>* MATTranspMat(); //DONE

};

#include "Cmatrice.cpp"