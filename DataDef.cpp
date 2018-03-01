#include "DataDef.h"
#include <string.h>
#define UNINIT -10010

Member::Member()
{
	this->id = UNINIT;
	strcpy_s(this->name, " ");
	strcpy_s(this->description, " ");
}

Member::Member(int id, char *name, char *des)
{
	this->id = id;
	strcpy(this->name, name);
	strcpy(this->description, des);
}

