#include "operators.h"

int opr::getImp()
{
	if(name=="#" || name==")" || name==":" || name=="(")
		return -1;
	if(name=="IF" || name=="WHILE" || name=="PRINT")
		return 0;
	if(name=="=" || name=="+=")
		return 1;
	if(name=="==" || name=="!=")
		return 2;
	if(name=="<" || name==">")
		return 3;
	if(name=="+" || name=="-")
		return 4;
	if(name=="*" || name=="/")
		return 5;
	if(name=="**")
		return 6;
	if(name=="--")
		return 7;
	return 10;
}

bool opr::getLeft()
{
	if(name=="+" || name=="-" || name=="*" || name=="/")
		return true;
	return false;
}

