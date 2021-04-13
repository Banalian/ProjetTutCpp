#pragma once
#include "Cexception.h"

#define ERRHorsFomatMat 101
#define ERRBadSizeMat 102
#define ERRDivByZero 150
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
	Cmatrice();
	Cmatrice(int iNbLigne, int iNbColonne);
	Cmatrice(Cmatrice<MType> &MATMatrice);
	~Cmatrice();

	int  MATgetNbLigne();
	int  MATgetNbColonne();

	void MATsetNbLigne(int iLigne);
	void MATsetNbColonne(int iColonne);

	MType** MATgetTabCopy();
	Cmatrice* MATgetMatCopy();

	MType MATgetTabCase(int iLigne, int iColonne);
	void MATsetTabCase(int iLigne, int iColonne, MType elem);

	void MATAfficherMatrice();


	Cmatrice<MType>& operator*(MType elem);
	Cmatrice<MType>& operator/(MType elem);

	Cmatrice<MType>& operator+(Cmatrice<MType> MATelem);
	Cmatrice<MType>& operator-(Cmatrice<MType> MATelem);
	Cmatrice<MType>& operator*(Cmatrice<MType> MATelem);

	Cmatrice<MType>& operator=(Cmatrice<MType> MATelem);


	Cmatrice<MType>* MATTranspMat();

};

#include "Cmatrice.cpp"