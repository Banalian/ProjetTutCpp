#include "Cexception.h"

Cexception::Cexception()
{
	iEXCCode = 0;
}

Cexception::Cexception(int iCode)
{
	iEXCCode = iCode;
}

Cexception::~Cexception()
{
}

int Cexception::EXCLire_Code()
{
	return iEXCCode;
}

void Cexception::EXCModifier_Code(int iCode)
{
	iEXCCode = iCode;
}
