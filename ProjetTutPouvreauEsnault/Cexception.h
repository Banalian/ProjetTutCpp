#pragma once
#include "Cmatrice.h"

class Cexception
{
private : 
	int iEXCCode;

public :

	Cexception();
	Cexception(int iCode);
	~Cexception();

	int EXCLire_Code();
	void EXCModifier_Code(int iCode);
};

